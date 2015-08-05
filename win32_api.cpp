//
//  win32_utils.cpp
//
//  Created by Taras Lushney on 6/8/14.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.
//

#include "./win32_api.h"
#include "./win32_exception.h"

namespace win32_api {

void CloseHandle(HANDLE handle) {
    auto result = ::CloseHandle(handle);
    ThrowLastErrorIf(result == FALSE, "Function ::CloseHandle() has been failed");
}

std::string GetErrorString(DWORD error) {
    if(error == 0)
        return "No error";

    char* buffer = nullptr;
    const size_t size = ::FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK,
            nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&buffer), 0, nullptr);
    ThrowLastErrorIf(size == 0, "Function ::FormatMessage() has been failed");
    std::string result(buffer, size);
    ThrowLastErrorIf(::LocalFree(buffer) != NULL, "Function ::LocalFree() has been failed");
    return result;
}

};  // namespace win32_api
