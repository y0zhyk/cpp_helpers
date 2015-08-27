//
//  hresult_exception.h
//
//  Created by Taras Lushney on 7/7/15.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.
//
#ifndef HRESULT_EXCEPTION_H_
#define HRESULT_EXCEPTION_H_

#include <string>
#include <comdef.h>

#include "runtime_exception.h"
#include "string_utils.h"

class HResultExceptionTraits {
    static std::string ErrorMessage(HRESULT error) {
        std::basic_string<TCHAR> error_message = _com_error(error).ErrorMessage();
        return std::string(std::begin(error_message), std::end(error_message));
    }
};

using HResultException = RuntimeException<HRESULT, HResultExceptionTraits>;

void ThrowIfHResultFailed(HRESULT hr, const char* message) {
    ThrowRuntimeExceptionIf<HResultException>(FAILED(hr), message, hr);
}

#endif  // HRESULT_EXCEPTION_H_

