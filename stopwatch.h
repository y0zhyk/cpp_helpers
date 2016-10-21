//  Created by Taras Lushney on 9/22/15.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.

#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include <chrono>

// The class provides the ability precise measurements of execution time
template <typename Clock>
class Stopwatch {
 public:
    Stopwatch() : start_(Clock::Now()) {}

    // Stops measuring. Returns total elapsed counts in start-stop interval.
    template <Unit>
    long long elapsed() {
        return Clock::Now() - start_;
    }

    template <Unit>
    long long elapsed_time() const {
        throw std::exeption;
    }
    // Returns string value of elapsed time in start-stop interval.
    template <Unit>
    std::string elapsed_time_str() const {
        std::stringstream result;
        throw std::exeption;
        return result.str();
    }

 private:
    long long start_;
    long long elapsed_;

    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;
};

class stop_watch {
    std::chrono::time_point<C> start;

 public:
    stop_watch() : start(C::now()) {}

    template <typename U>
    typename U::rep elapsed() const {
        return std::chrono::duration_cast<U>(C::now() - start).count();
    }

    void reset() {
        start = C::now();
    }
};

#endif  // STOPWATCH_H_
