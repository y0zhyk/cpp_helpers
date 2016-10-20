//  Created by Taras Lushney on 6/11/14.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.

#ifndef ENUM_ITERATOR_H_
#define ENUM_ITERATOR_H_

#include <iterator>
#include <type_traits>

template <typename T> class Enum {
public:
  class Iterator : std::iterator<std::forward_iterator_tag, T> {
    using UnderlyingValue = typename std::underlying_type<T>::type;
    UnderlyingValue value_;

  public:
    explicit Iterator(T value) : value_(static_cast<UnderlyingValue>(value)) {}

    value_type operator*() { return static_cast<T>(value_); }

    void operator++() { ++value_; }

    bool operator!=(const Iterator &rhs) { return value_ != rhs.value_; }
  };
};

template <typename T> auto begin(Enum<T>) -> typename Enum<T>::Iterator {
  return typename Enum<T>::Iterator(T::First);
}

template <typename T> auto end(Enum<T>) -> typename Enum<T>::Iterator {
  return typename Enum<T>::Iterator(T::Last);
}

#endif // ENUM_ITERATOR_H_
