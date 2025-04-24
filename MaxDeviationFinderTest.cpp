#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <cmath>

#include "MaxDeviationFinder.h"

class MaxDeviationFinderTest : public MaxDeviationFinder {
public:
  explicit MaxDeviationFinderTest(unsigned int stop_time)
    : MaxDeviationFinder(stop_time) {}
  
  void ResetTimer(unsigned int start_time) {
    UpdateTimer(start_time);
  }
};

TEST(MaxDeviationFinderTest, ValidateInitialValues) {
  MaxDeviationFinderTest maxDeviationFinder(1000);
  
  EXPECT_EQ(maxDeviationFinder.GetMaxStdDeviation(), 0.0);
}

TEST(MaxDeviationFinderTest, ValidateAddData) {
  MaxDeviationFinderTest maxDeviationFinder(1000);
  maxDeviationFinder.ResetTimer(0);
  
  EXPECT_FALSE(maxDeviationFinder.AddData(10.0, 0));
  
  maxDeviationFinder.AddData(12.0, 100);
  maxDeviationFinder.AddData(14.0, 200);
  maxDeviationFinder.AddData(16.0, 300);
  maxDeviationFinder.AddData(18.0, 400);
  maxDeviationFinder.AddData(20.0, 500);
  
  EXPECT_GT(maxDeviationFinder.GetMaxStdDeviation(), 0.0);
}

TEST(MaxDeviationFinderTest, ValidateMaxStdDeviation) {
  MaxDeviationFinderTest maxDeviationFinder(1000);
  maxDeviationFinder.ResetTimer(0);
  
  maxDeviationFinder.AddData(10.0, 0);
  maxDeviationFinder.AddData(12.0, 100);
  maxDeviationFinder.AddData(14.0, 200);
  maxDeviationFinder.AddData(16.0, 300);
  maxDeviationFinder.AddData(18.0, 400);
  
  EXPECT_GT(maxDeviationFinder.GetMaxStdDeviation(), 0.0);
}

TEST(MaxDeviationFinderTest, ValidateTimeout) {
  MaxDeviationFinderTest maxDeviationFinder(50);
  maxDeviationFinder.ResetTimer(0);
  EXPECT_FALSE(maxDeviationFinder.AddData(10.0, 10));
  EXPECT_FALSE(maxDeviationFinder.AddData(12.0, 20));
  
  EXPECT_TRUE(maxDeviationFinder.AddData(14.0, 100));
}

TEST(MaxDeviationFinderTest, ValidateClear) {
  MaxDeviationFinder maxDeviationFinder(1000);
  maxDeviationFinder.UpdateTimer(0);
  
  for (int i = 0; i < 5; ++i) {  // Fill the Welford's window with 5 values
    maxDeviationFinder.AddData(10.0 + i, i * 100);
  }
  EXPECT_GT(maxDeviationFinder.GetMaxStdDeviation(), 0.0);
  
  maxDeviationFinder.Clear();
  EXPECT_EQ(maxDeviationFinder.GetMaxStdDeviation(), 0.0);
  
  for (int i = 0; i < 5; ++i) {
    maxDeviationFinder.AddData(100.0 + i, i * 10);
  }
  EXPECT_GT(maxDeviationFinder.GetMaxStdDeviation(), 0.0);
}

TEST(MaxDeviationFinderTest, TestPositiveValue) {
  MaxDeviationFinderTest maxDeviationFinder(1000);
  maxDeviationFinder.ResetTimer(0);
  
  EXPECT_EQ(maxDeviationFinder.TruncateToFirstDigit(1234.5678), 1000.0);
}
