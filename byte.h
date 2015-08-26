//
//  byte.h
//
//  Created by Taras Lushney on 8/05/15.
//  Copyright (c) 2015 Taras Lushney. All rights reserved.

#ifndef BYTE_H_
#define BYTE_H_

#include <cstdint>

namespace core {

typedef std::uint8_t Byte;

typedef std::vector<Byte> Bytes;

template <size_t size>
using Bytes = std::array<Byte, size>;

}  // namespace core

#endif  // BYTE_H_
