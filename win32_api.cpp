//  Created by Taras Lushney on 6/8/14.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.

#include <functional>
#include <memory>

#include "./win32_api.h"
#include "./win32_exception.h"

namespace win32_api {

void CloseHandle(HANDLE handle) {
    auto result = ::CloseHandle(handle);
    ThrowLastErrorIf(FALSE == result, "::CloseHandle() == FALSE");
}

static void LocalFree(HLOCAL memory) {
    auto result = ::LocalFree(memory);
    ThrowLastErrorIf(NULL != result, "::LocalFree() != NULL");
}

std::string GetErrorString(DWORD error) {
    if (error == 0)
        return "No error";

    char *raw_buffer = nullptr;
    const size_t size = ::FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                                             FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK,
        nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&raw_buffer), 0, nullptr);
    ThrowLastErrorIf(size == 0, "::FormatMessage() == 0");
    std::unique_ptr<char, std::function<void(HLOCAL)>> buffer(raw_buffer, LocalFree);
    return std::string(buffer.get(), size);
}

}; // namespace win32_api
