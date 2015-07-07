//
//  singleton.h
//
//  Created by Taras Lushney on 6/31/14.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.
//

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <mutex>
#include <memory>
#include <utility>

template <class T>
class Singleton {
 public:
    template <typename... Args>
    static T& instance(Args&&... args) {
        std::call_once(once_flag(), [](Args&&... args) {
            instance_.reset(new T(std::forward<Args>(args)...));
        }, std::forward<Args>(args)...);
      return *instance_.get();
    }

private:
    Singleton() = default;
    ~Singleton() = default;

 private:
    Singleton<T>(const Singleton<T>&) = delete;
	
    const Singleton<T>& operator=(const Singleton<T>&) = delete;
 
    static std::once_flag& once_flag() {
        static std::once_flag once;
        return once;
    }

    static std::unique_ptr<T> instance_;
};
 
template<class T>
std::unique_ptr<T> Singleton<T>::instance_ = nullptr;
 
#endif
