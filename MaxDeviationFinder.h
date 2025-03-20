#ifndef SRC_MAXDEVIATIONFINDER_H_
#define SRC_MAXDEVIATIONFINDER_H_

#include <cmath>
#include "filter/ModifiedWelford.h"

class MaxDeviationFinder {
 public:
    /**
     * @brief Creates an instance of the MaxDeviationFinder class with a specific stop time.
     * This class calculates and provides the maximum standard deviation of a dataset
     * over a defined time interval (from start time to stop time).
     * @param stop_time The time at which data collection should stop.
     */
    explicit MaxDeviationFinder(unsigned int stop_time);
    ~MaxDeviationFinder();

    /**
     * @brief Adds raw data to the standard deviation calculation.
     * This method allows for including new data values within a defined time interval
     * @param raw_input The data value to be added.
     * @param timestamp The time at which the data was recorded.
     * @return true if the time (stop_time) limit for data collection has been reached,
     * false otherwise.
     */
    bool AddData(double raw_input, unsigned int timestamp);

    /**
     * @brief Starts the timer for measuring maximum deviation from a specified start time.
     * This method defines the moment when the standard deviation calculation should begin.
     * @param start_time The time at which to start measuring deviation.
     */
    void MaxDeviationTimerStarter(unsigned int start_time);

    /**
     * @brief Returns the maximum standard deviation calculated during the data collection.
     * @return The maximum standard deviation value.
     */
    double GetMaxStdDeviation();
    double TruncateToFirstDigit(double value);
    double GetMaxTruncatedStdDeviation();
    void Clear();

 private:
    unsigned int stop_time_;
    double mean_value_;
    double std_deviation_;
    double max_std_deviation_;
    ModifiedWelford welford_filter_;
    ModifiedWelford welford_deviation_;
    unsigned int start_time_;
};

#endif  // SRC_MAXDEVIATIONFINDER_H_

