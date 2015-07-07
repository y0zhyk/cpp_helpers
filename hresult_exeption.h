//
//  hresult_exception.h
//
//  Created by Taras Lushney on 7/7/15.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.
//
#ifndef HRESULT_EXCEPTION_H_
#define HRESULT_EXCEPTION_H_

#include <comdef.h>
#include <string>

#include "runtime_exception.h"
#include "string_utils.h"

class HResultException
    : public RuntimeException<HResultException, HRESULT> {
 public:
    HResultException(const std::string& message, HRESULT error)
            : RuntimeException(message, error) {
    }

    static std::string ErrorMessage(HRESULT error) {
        #ifdef _UNICODE
            return utils_string::WStringToString(_com_error(error).ErrorMessage());
        #else
            return _com_error(error).ErrorMessage();
        #endif // _UNICODE 
    }
};


void ThrowIfHResultFailed(HRESULT hr, const std::string& message) {
    ThrowRuntimeExceptionIf<HResultException>(FAILED(hr), message, hr);
}

#endif  // HRESULT_EXCEPTION_H_

