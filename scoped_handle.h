//  Created by Taras Lushney on 5/29/15.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.
#ifndef SCOPED_HANDLE_H_
#define SCOPED_HANDLE_H_

#include "macros.h"

template <typename Traits>
class ScopedHandle {
 public:
    typedef typename Traits::Handle T;

    explicit ScopedHandle(T value = Traits::NullHandle()) : value_(value) {}
    ScopedHandle(ScopedHandle &&other) : value_(other.Release()) {}

    ScopedHandle &operator=(ScopedHandle &&other) noexcept {
        Reset(other.Release());
        return *this;
    }

    virtual ~ScopedHandle() noexcept {
        Close();
    }

    T get() const {
        return value_;
    }

    bool IsValid() const {
        return Traits::IsHandleValid(value_);
    }

    explicit operator bool() const {
        return Traits::IsHandleValid(value_);
    }

    explicit operator T() const {
        return get();
    }

    T Release() {
        auto value = value_;
        value_ = Traits::NullHandle();
        return value;
    }

    bool Reset(T value = Traits::NullHandle()) noexcept {
        if (value_ != value) {
            Close();
            value_ = value;
        }
        return *this;
    }

 private:
    void Close() {
        if (*this)
            Traits::CloseHandle(value_);
    }

    T value_;

    DISALLOW_COPY_AND_ASSIGN(ScopedHandle);
};

#endif  // SCOPED_HANDLE_H_
