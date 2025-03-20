#include "MaxDeviationFinder.h"

MaxDeviationFinder::MaxDeviationFinder(unsigned int stop_time)
        : stop_time_(stop_time),
          mean_value_(0.0),
          std_deviation_(0.0),
          max_std_deviation_(0.0),
          welford_filter_(15),
          welford_deviation_(2),
          start_time_(0) {
}

MaxDeviationFinder::~MaxDeviationFinder() {
}

void MaxDeviationFinder::MaxDeviationTimerStarter(unsigned int start_time) {
    start_time_ = start_time;
}

bool MaxDeviationFinder::AddData(double raw_input, unsigned int timestamp) {
    welford_filter_.AddSample(raw_input);
    mean_value_ = welford_filter_.GetMean();

    welford_deviation_.AddSample(mean_value_);
    std_deviation_ = welford_deviation_.GetDeviation();

    if (std_deviation_ > max_std_deviation_) {
        max_std_deviation_ = std_deviation_;
    }
    return CheckTimeout(timestamp);
}

bool MaxDeviationFinder::CheckTimeout(unsigned int timestamp) {
    return (timestamp - start_time_) > stop_time_;
}

double MaxDeviationFinder::TruncateToFirstDigit(double value) {
    if (value == 0.0) {
        return 0.0;
    }

    int exponent = static_cast<int>(std::floor(std::log10(std::fabs(value))));

    double scaled_value = value / std::pow(10, exponent);
    scaled_value = std::floor(scaled_value);

    double truncated_value = scaled_value * std::pow(10, exponent);

    return truncated_value;
}

double MaxDeviationFinder::GetMaxStdDeviation() {
    return max_std_deviation_;
}

double MaxDeviationFinder::GetMaxTruncatedStdDeviation() {
    return TruncateToFirstDigit(max_std_deviation_);
}

void MaxDeviationFinder::Clear() {
    mean_value_ = 0.0;
    max_std_deviation_ = 0.0;
    std_deviation_ = 0.0;
    start_time_ = 0;
    welford_filter_.Clear();
    welford_deviation_.Clear();
}
