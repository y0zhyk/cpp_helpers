#ifndef STL_UTIL_H_
#define STL_UTIL_H_

#include <algorithm>

namespace base {

template <typename Collection, typename Value>
bool ContainsValue(const Collection &collection, const Value &value) {
    return std::find(collection.begin(), collection.end(), value) != collection.end();
}

} // namespace base

#endif // BASE_STL_UTIL_H_