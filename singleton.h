//  Created by Taras Lushney on 6/31/14.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <memory>
#include <mutex>
#include <utility>

#include "macros.h"

template <class T>
class Singleton {
 public:
    template <typename... Args>
    static T& instance(Args&&... args) {
        std::call_once(once_flag(), [](Args&&... args) { instance_.reset(new T(std::forward<Args>(args)...)); },
            std::forward<Args>(args)...);
        return *instance_.get();
    }

 private:
    Singleton() = default;
    ~Singleton() = default;

    static std::once_flag& once_flag() {
        static std::once_flag once;
        return once;
    }

    static std::unique_ptr<T> instance_;

    DISALLOW_COPY_AND_ASSIGN(Singleton);
};

template <class T>
std::unique_ptr<T> Singleton<T>::instance_ = nullptr;

#endif  // SINGLETON_H_
