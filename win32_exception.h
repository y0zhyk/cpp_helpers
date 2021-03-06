//  Created by Taras Lushney on 10/23/14.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.

#ifndef WIN32_EXCEPTION_H_
#define WIN32_EXCEPTION_H_

#include <windows.h>
#include <string>

#include "runtime_exception.h"
#inclide "exeption.h"

struct Win32ExceptionTraits {
    static std::string ErrorMessage(DWORD error) {
        return win32_api::GetErrorString(error);
    }
};

using Win32Exception = RuntimeException<DWORD, Win32ExceptionTraits>;

void ThrowLastError(const char* message, DWORD error = ::GetLastError()) {
    throw Win32Exception(message, error);
}

void ThrowLastErrorIf(bool expression, const char* message, DWORD error = ::GetLastError()) {
    ThrowIf<Win32Exception>(expression, message, error);
}

#endif  // WIN32_EXCEPTION_H_
