//  Created by Taras Lushney on 12/29/16.
//  Copyright (c) 2015 Taras Lushney. All rights reserved.

#ifndef WAITABLE_EVENT_H_
#define WAITABLE_EVENT_H_

#include <mutex>
#include <condition_variable>
#include <chrono>

#include "macros.h"

class Semaphore {
 public:
    inline Semaphore(unsigned int count): count_(count) {}

    inline void Wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this]() { return count_ > 0; });
        --count_;
    }

    bool WaitWithTimeout(unsigned int duration_ms) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!cv_.wait_for(lock, std::chrono::milliseconds(duration_ms), [this]() { return count_ > 0; })) {
            return false;
        }
        --count_;
        return true;
    }

    inline void Signal() {
        std::unique_lock<std::mutex> lock(mutex_);
        ++count_;
        cv_.notify_one();
    }
    
 private:
    unsigned int count_;
    std::mutex mutex_;
    std::condition_variable cv_;
    
    DISALLOW_COPY_AND_ASSIGN(Semaphore);
};
