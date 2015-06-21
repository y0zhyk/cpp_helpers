//
//  timer.h
//
//  Created by Taras Lushney on 2/11/15.
//  Copyright (c) 2015 Taras Lushney. All rights reserved.

#ifndef TIMER_H_
#define TIMER_H_

#include <windows.h>
#include <string>
#include <sstream>
#include <memory>

// Wrapper class for the high-resolution performance counter.
class performance_counter {
 public:
    // Receives the current performance-counter value, in counts.
    static long long counter() {
        LARGE_INTEGER counts;
        ::QueryPerformanceCounter(&counts);
        return counts.QuadPart;
    }
    // Retrieves the frequency of the high-resolution performance counter, in counts per second.
    static long long frequency() {
        LARGE_INTEGER counts;
        ::QueryPerformanceFrequency(&counts);
        return counts.QuadPart;
    }
};

// The enumeration provides code values for units of time
namespace UnitsOfTime {
enum units_of_time : int {
    Microsecond = -6,
    Millisecond = -3,
    Second = 0,
};
};

using UnitsOfTime::units_of_time;

// The class provides the ability precise measurements of execution time
class stopwatch {
 public:
    stopwatch()
        : start_count_(0)
        , elapsed_counts_(0) {
    }
    // Starts measuring.
    void start() {
        start_count_ = performance_counter::counter();
    }
    // Stops measuring. Returns total elapsed counts in start-stop interval.
    long long stop() {
        return elapsed_counts_ = performance_counter::counter() - start_count_;
    }
    // Returns total elapsed time in start-stop interval.
    template<units_of_time unit>
    long long elapsed_time() const {
        return elapsed_counts_ * units_per_second<unit>::value / performance_counter::frequency();
    }
    // Returns string value of elapsed time in start-stop interval.
    template<units_of_time precision>
    std::string elapsed_time_str() const {
        std::stringstream result;
        const long long units = elapsed_time<precision>();
        result << units / units_per_second<precision>::value;
        if (precision < UnitsOfTime::Second) {
            result << ".";
            result.width(-precision);
            result.fill('0');
            result << units % units_per_second<precision>::value;
        }
        result << " sec";
        return result.str();
    }

 private:
    // Helper class for raising the specified base to the specified power.
    template<unsigned int base, unsigned int pow>
    struct pow {
        const static long long value = pow<base, pow/2>::value * pow<base, pow/2>::value * pow<base, pow%2>::value;
    };
    template<unsigned int base> 
    struct pow<base, 1> {
        const static long long value = base;
    };
    template<unsigned int base> 
    struct pow<base, 0> {
        const static long long value = 1;
    };
    // Helper class for calculating number of units per second
    template<units_of_time unit>
    struct units_per_second {
        const static long long value = pow<10, -unit>::value;
    };
    // The value of the counter on start ticking.
    long long start_count_;
    // Counts elapsed in start-stop interval.
    long long elapsed_counts_;
    //Ban copy
    explicit stopwatch(const Stopwatch&);
    stopwatch& operator=(const Stopwatch&);
};

class scoped_function {
 public:
    virtual void execute(const stopwatch& _stopwatch) = 0;
    virtual ~scoped_function() {}
};

template<units_of_time precision = UnitsOfTime::Microsecond>
class scoped_functions {
 public:
    template<class T>
    static scoped_function* create_stream_printer(const char* _block_name, const T& _stream) {
        class stream_printer : public scoped_function {
         public:
            explicit stream_printer(const char* _block_name, const T& _stream)
                : block_name_(_block_name)
                , stream_(_stream) {
            }
         private:
             void execute(const stopwatch& _stopwatch) {
	         stream_ << block_name_ <<" executed " << _stopwatch.elapsed_time_str<precision>() << "\n";
             }
            const char* block_name_;
            T& stream_;
        };
        return new stream_printer(_block_name, _stream);
    }    
};

class scoped_stopwatch {
 public:
    explicit scoped_stopwatch(scoped_function* _scoped_function)
        : scoped_function_(_scoped_function) {
        stopwatch_.start();
    }
    ~scoped_stopwatch() {
        stopwatch_.stop();
        if (scoped_function_.get())
            scoped_function_->execute(stopwatch_);
    }
 private:
    stopwatch stopwatch_;
    std::auto_ptr<scoped_function> scoped_function_;
};

#define auto_function_stopwatch(_stream) scoped_stopwatch dummy##__LINE__(scoped_functions<>::create_stream_printer("Function "__FUNCTION__, _stream));

#endif  // TIMER_H_
