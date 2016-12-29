//  Created by Taras Lushney on 12/29/16.
//  Copyright (c) 2015 Taras Lushney. All rights reserved.

#ifndef WAITABLE_EVENT_H_
#define WAITABLE_EVENT_H_

#include <mutex>
#include <condition_variable>

#include "macros.h"

// An event that can be signaled and waited on. 
// This is similar to Windows's manual-reset event.
class WaitableEvent {
 public:
    WaitableEvent();
    // Puts the event into the signaled state.
    void Signal();
    // Put the event into the unsignaled state.
    void Reset();
    // Blocks the calling thread until the event is signaled.
    void Wait();
    // Like Wait(), but with a timeout. Unblocks the calling thread either after event is signaled 
    // or timeout is exceeded. Returns true if event was signaled within given timeout.
    bool WaitWithTimeout(unsigned int duration_ms);
 private:
    bool signaled_ = false;
    std::mutex mutex_;
    std::condition_variable cv_;

    DISALLOW_COPY_AND_ASSIGN(WaitableEvent);
};

#endif  // WAITABLE_EVENT_H_