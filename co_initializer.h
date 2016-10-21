//  Created by Taras Lushney on 10/12/16.
//  Copyright (c) 2016 Taras Lushney. All rights reserved.

#ifndef SCOPED_CO_INITIALIZER_H_
#define SCOPED_CO_INITIALIZER_H_

#include <ObjBase.h>

#include "hresult_exeption.h"
#include "macros.h"

class ScopedCoInitializer {
 public:
    explicit ScopedCoInitializer(DWORD coinit = COINIT_APARTMENTTHREADED) {
        hr_ = ::CoInitializeEx(nullptr, coinit);
        ThrowIfHResultFailed(hr, "Function ::CoInitializeEx() has been failed");
    }

    ~ScopedCoInitializer() noexcept {
        if (succeeded())
            ::CoUninitialize();
    }

    bool succeeded() const {
        return SUCCEEDED(hr_);
    }

 private:
    HRESULT hr_;

    DISALLOW_COPY_AND_ASSIGN(ScopedCOMInitializer);
};

#endif  // SCOPED_CO_INITIALIZER_H_