//
//  win32_handle.h
//
//  Created by Taras Lushney on 5/29/15.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.
//

#ifndef WIN32_HANDLE_H_
#define WIN32_HANDLE_H_

#include <Windows.h>

#include "./handle.h"
#include "./win32_api.h"

struct Win32HandleTraits {
    static HANDLE Invalid() noexcept {
        return NULL;
    }

    static void Close(HANDLE value) noexcept {
        win32_api::CloseHandle(value);
    }
};

using Win32Handle = Handle<HANDLE, Win32HandleTraits>;

#endif  // WIN32_HANDLE_H_
