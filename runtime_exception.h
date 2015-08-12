//
//  runtime_exception.h
//
//  Created by Taras Lushney on 10/30/14.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.
//

#ifndef RUNTIME_EXCEPTION_H_
#define RUNTIME_EXCEPTION_H_

#include <string>
#include <sstream>

template<typename T, typename Traits>
class RuntimeException
    : public std::runtime_error {
 public:
    typedef T ErrorType;

    RuntimeException(const char* message, ErrorType error)
        : std::runtime_error(FormatErrorMessage(message, error))
        , error_(error) {
    }

    ErrorType error() const {
        return error_;
    }

 private:
    static std::string FormatErrorMessage(const char* message, ErrorType error) {
        std::stringstream error_message;
        error_message << message << " (Error: " << error << ") : " << Traits::ErrorMessage(error);
        return error_message.str();
    }

    const ErrorType error_;
};


template<typename ExceptionType>
void ThrowRuntimeExceptionIf(bool expression, const char* message, typename ExceptionType::ErrorType error) {
    if (expression)
        throw ExceptionType(message, error);
}

#endif  // RUNTIME_EXCEPTION_H_
