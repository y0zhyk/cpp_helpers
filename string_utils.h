//
//  string_utils.h
//
//  Created by Taras Lushney on 9/26/14.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.
//

#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

#include <string>
#include <locale>

namespace utils_string {

using wstring_to_string_convert = std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>;

std::wstring StringToWString(const std::string& str) {
    return wstring_to_string_convert().from_bytes(str);
}

std::string WStringToString(const std::wstring& str) {
    return wstring_to_string_convert().to_bytes(str);
}

};  // namespace utils_string

#endif  // STRING_UTILS_H_
