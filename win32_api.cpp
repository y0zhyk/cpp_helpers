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
        ThrowLastErrorIf(result == FALSE, "Failed to close an object handle");
    }

};  // namespace win32_api
