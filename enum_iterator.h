//
//  enum_iterator.h
//
//  Created by Taras Lushney on 6/11/14.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.
//

#ifndef ENUM_ITERATOR_H_
#define ENUM_ITERATOR_H_

#include <type_traits>
#include <iterator>

template<typename T>
class Enum {
 public:
    class Iterator : std::iterator<std::forward_iterator_tag, T> {
        using underlying_type_t = typename std::underlying_type<T>::type;
        underlying_type_t value_;
     public:
        explicit Iterator(value_type value)
            : value_(static_cast<underlying_type_t>(value)) {
        }

        value_type operator*() {
            return static_cast<value_type>(value_);
        }

        void operator++() {
            ++value_;
        }

        bool operator!=(const Iterator& rhs) {
            return value_ != rhs.value_;
        }
    };
};

template<typename T>
auto begin(Enum<T>) -> typename Enum<T>::Iterator {
    return typename Enum<T>::Iterator(T::First);
}

template<typename T>
auto end(Enum<T>) -> typename Enum<T>::Iterator {
    return typename Enum<T>::Iterator(T::Last);
}

#endif  // ENUM_ITERATOR_H_
