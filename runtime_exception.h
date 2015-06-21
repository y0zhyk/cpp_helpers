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

template<typename Derived, typename T>
class RuntimeException
    : public std::runtime_error {
 public:
    typedef T ErrorType;

    RuntimeException(const std::string& message, ErrorType error)
        : std::runtime_error(FormatErrorMessage(message, error))
        , error_(error) {
    }

    ErrorType error() const {
        return error_;
    }

 private:
    static std::string FormatErrorMessage(const std::string& message, ErrorType error) {
        std::stringstream error_message;
        error_message << message << " (" << Derived::ErrorMessage(error) << ")";
        return error_message.str();
    }

    const ErrorType error_;
};


template<typename ExceptionType>
void ThrowRuntimeExceptionIf(bool expression, const std::string& message, typename ExceptionType::ErrorType error) {
    if (expression)
        throw ExceptionType(message, error);
}

#endif  // RUNTIME_EXCEPTION_H_
