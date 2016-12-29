//  Created by Taras Lushney on 12/29/16.
//  Copyright (c) 2015 Taras Lushney. All rights reserved.

#include "waitable_event.h"

#include <chrono>

WaitableEvent::WaitableEvent() = default;

void WaitableEvent::Signal() {
    std::unique_lock<std::mutex> lock(mutex_);
    signaled_ = true;
    cv_.notify_one();
}

void WaitableEvent::Reset() {
    std::unique_lock<std::mutex> lock(mutex_);
    signaled_ = false;
}

void WaitableEvent::Wait() {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this]() {
        return signaled_;
    });
}

bool WaitableEvent::WaitWithTimeout(unsigned int duration_ms) {
    std::unique_lock<std::mutex> lock(mutex_);
    return cv_.wait_for(lock, std::chrono::milliseconds(duration_ms), [this]() {
        return signaled_;
    });
}
