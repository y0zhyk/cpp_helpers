//  Created by Taras Lushney on 7/12/15.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.

#ifndef CRITICAL_SECTION_H_
#define CRITICAL_SECTION_H_

class CriticalSection
{
 public:
    CCriticalSectionEx() noexcept {
        ::InitializeCriticalSection(&cs_);
    }
	
    ~CCriticalSectionEx() noexcept {
        ::DeleteCriticalSection(&cs_);
    }

    CriticalSection& operator=(const CriticalSection&) = delete;
    CriticalSection(const CriticalSection&) = delete;

    void Enter() noexcept {
        // This function can raise EXCEPTION_POSSIBLE_DEADLOCK if a wait operation on the critical section times out.
        // But Microsoft says to not handle the deadlock exception; instead, debug the application.
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
};

#endif  // CRITICAL_SECTION_H_