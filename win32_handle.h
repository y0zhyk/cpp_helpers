//  Created by Taras Lushney on 5/29/15.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.

#ifndef WIN32_HANDLE_H_
#define WIN32_HANDLE_H_

#include <Windows.h>

#include "handle.h"
#include "win32_api.h"

// The traits class for Win32 handles.
class Win32HandleTraits {
 public:
    typedef HANDLE Handle;

    // Returns NULL handle value.
    static HANDLE NullHandle() {
        return NULL;
    }

    // Closes the handle.
    static void CloseHandle(HANDLE handle) {
        win32_api::CloseHandle(handle);
    }

    // Returns true if the handle value is valid.
    static bool IsHandleValid(HANDLE handle) {
        return handle != NULL && handle != INVALID_HANDLE_VALUE;
    }

 private:
    DISALLOW_IMPLICIT_CONSTRUCTORS(Win32HandleTraits);
};

using Win32Handle = ScopedHandle<HANDLE, Win32HandleTraits>;

#endif  // WIN32_HANDLE_H_