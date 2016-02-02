//  Created by Taras Lushney on 9/26/14.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.

#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

#include <string>
#include <locale>

namespace utils_string {

template<typename T>
std::string ToMultiByteString(const std::basic_string<T>& str) {
    using convert = std::wstring_convert<std::codecvt<T, char, std::mbstate_t>, T>;
    return convert().to_bytes(str);
}

std::wstring ToWideString(const std::string& str) {
    using convert = std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>;
    return convert().from_bytes(str);
}

std::wstring ToWideString(const std::wstring& str) {
    return str;
}

};  // namespace utils_string

#endif  // STRING_UTILS_H_
