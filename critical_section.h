//  Created by Taras Lushney on 7/12/15.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.

#ifndef CRITICAL_SECTION_H_
#define CRITICAL_SECTION_H_

#include <Windows.h>

#include "macros.h"

class CriticalSection {
 public:
    CCriticalSection() noexcept {
        ::InitializeCriticalSection(&cs_);
    }

    ~CCriticalSection() noexcept {
        ::DeleteCriticalSection(&cs_);
    }

    void Enter() noexcept {
        // This function can raise EXCEPTION_POSSIBLE_DEADLOCK if a wait
        // operation
        // on the critical section times out.
        // But Microsoft says to not handle the deadlock exception; instead,
        // debug
        // the application.
        ::EnterCriticalSection(&cs_);
    }

    void Leave() noexcept {
        ::LeaveCriticalSection(&cs_);
    }

    bool TryEnter() noexcept {
        return ::TryEnterCriticalSection(&cs_) != FALSE;
    }

 private:
    CRITICAL_SECTION cs_;

    DISALLOW_COPY_AND_ASSIGN(CriticalSection)
};

#endif  // CRITICAL_SECTION_H_