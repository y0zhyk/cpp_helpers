//
//  win32_exception.h
//
//  Created by Taras Lushney on 10/23/14.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.
//
#ifndef WIN32_EXCEPTION_H_
#define WIN32_EXCEPTION_H_

#include <windows.h>
#include <string>

#include "./runtime_exception.h"

class Win32Exception
    : public RuntimeException<Win32Exception, DWORD> {
 public:
    Win32Exception(const std::string& message, DWORD error)
        : RuntimeException(message, error) {
    }

    static std::string ErrorMessage(DWORD error) {
        std::stringstream error_message;
        error_message << error;
        return error_message.str();
    }
};

void ThrowLastError(const std::string& message) {
    throw Win32Exception(message, ::GetLastError());
}

void ThrowLastErrorIf(bool expression, const std::string& message) {
    ThrowRuntimeExceptionIf<Win32Exception>(expression, message, ::GetLastError());
}

#endif  // WIN32_EXCEPTION_H_
