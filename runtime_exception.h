//  Created by Taras Lushney on 10/30/14.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.

#ifndef RUNTIME_EXCEPTION_H_
#define RUNTIME_EXCEPTION_H_

#include <string>
#include <sstream>

template<typename Error, typename Traits>
class RuntimeException
    : public std::runtime_error {
 public:

    RuntimeException(const char* message, Error error)
        : std::runtime_error(FormatErrorMessage(message, error))
        , error_(error) {
    }

    Error error() const {
        return error_;
    }

 private:
    static std::string FormatErrorMessage(const char* message, Error error) {
        std::stringstream error_message;
        error_message << message << " (Error: " << error << ") : " << Traits::ErrorMessage(error);
        return error_message.str();
    }

    const Error error_;
};

#endif  // RUNTIME_EXCEPTION_H_
