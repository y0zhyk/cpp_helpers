//  Created by Taras Lushney on 10/12/16.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.

#ifndef CO_INITIALIZER_H_
#define CO_INITIALIZER_H_

#include <windows.h>

#include "hresult_exeption.h"
                                     
class CoInitializer {
 public:
    explicit CCoInitializer(DWORD coinit = COINIT_APARTMENTTHREADED) {
        HRESULT hr = ::CoInitializeEx(nullptr, coinit);
        ThrowIfHResultFailed(hr, "Function ::CoInitializeEx() has been failed");
        coinitialized_ = true;
   }

   ~CCoInitializer() noexcept {
      if (coinitialized_)
         ::CoUninitialize();
   }
 private:
   bool coinitialized_ = false;

   CoInitializer(const CoInitializer&) = delete;
   CoInitializer& operator=(const CoInitializer&) = delete;
};