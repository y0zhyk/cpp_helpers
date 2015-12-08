//  Created by Taras Lushney on 8/12/15.
//  Copyright (c) 2015 Taras Lushney. All rights reserved.

#ifndef OPTIONAL_H_
#define OPTIONAL_H_

#include <boost/optional.hpp>

namespace core {

template <typename T>
using Optional = boost::optional<T>;

}  // namespace core

#endif  // OPTIONAL_H_