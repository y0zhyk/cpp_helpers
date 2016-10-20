//  Created by Taras Lushney on 5/29/15.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.

#ifndef WIN32_HANDLE_H_
#define WIN32_HANDLE_H_

#include <Windows.h>

#include "handle.h"
#include "win32_api.h"

class Win32HandleTraits {
 public:
  static HANDLE Invalid() noexcept { return INVALID_HANDLE_VALUE; }

  static void Close(HANDLE value) noexcept { win32_api::CloseHandle(value); }

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(Win32HandleTraits);
};

using Win32Handle = Handle<HANDLE, Win32HandleTraits>;

#endif  // WIN32_HANDLE_H_