//  Created by Taras Lushney on 11/09/15.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.

#ifndef LAZY_H_
#define LAZY_H_

#include <utility>
#include <type_traits>

#include "optional.hpp"

template<class Function>
class Lazy {
 public:
    typedef typename std::result_of<Function()>::type Result;

    explicit Lazy(Function&& function) : function_(std::move(function)) {}
    explicit Lazy(const Function& function) : function_(function) {}

    Lazy(Lazy&& other)
        : value_(std::move(other.value_))
        , function_(std::move(other.function_))
    {}

    Lazy(const Lazy&) = delete;
    Lazy& operator=(const Lazy&) = delete;
    Lazy& operator=(Lazy&&) = delete;

    const Result& operator()() const {
        return const_cast<Lazy&>(*this)();
    }

    Result& operator()() {
        if (!value_)
            value_ = function_();
        return *value_;
    }

 private:
    Optional<Result> value_;
    Function function_;
};

template<class Function>
Lazy<typename std::remove_reference<Function>::type> MakeLazy(Function&& function) {
    return Lazy<typename std::remove_reference<Function>::type>(std::forward<Function>(function));
}
 
#endif  // LAZY_H_
