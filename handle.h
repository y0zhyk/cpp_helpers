//
//  handle.h
//
//  Created by Taras Lushney on 5/29/15.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.
//

#ifndef HANDLE_H_
#define HANDLE_H_

template<typename T, typename Traits>
class Handle {
 public:
    explicit Handle(T value = Traits::Invalid()) noexcept
            : value_(value) {
    }

    Handle(Handle&& other) noexcept
            : value_(other.Release()) {
    }

    Handle(const Handle& other) = delete;

    Handle& operator=(Handle&& other) noexcept {
        Reset(other.Release());
    }

    virtual ~Handle() noexcept {
        Close();
    }

    T Get() const noexcept {
        return value_;
    }

    explicit operator bool() const noexcept {
        return Traits::Invalid() != value_;
    }

    explicit operator T() const noexcept {
        return Get();
    }

    T Release() noexcept {
        auto value = value_;
        value_ = Traits::Invalid();
        return value_;
    }

    bool Reset(T value = Traits::Invalid()) noexcept {
        if (value_ != value) {
            Close();
            value_ = value;
        }
        return *this;
    }

 private:
    void Close() noexcept {
        if (*this) {
            Traits::Close(value_);
        }
    }

    T value_;
};

#endif  // HANDLE_H_
