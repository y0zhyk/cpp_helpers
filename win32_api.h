//
//  win32_utils.h
//
//  Created by Taras Lushney on 6/8/14.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.
//

#ifndef WIN32_API_H_
#define WIN32_API_H_

#include <windows.h>

namespace win32_api {
    // Closes an open object handle.
    void CloseHandle(HANDLE handle);

};  // namespace win32_api

#endif  // WIN32_API_H_
