//  Created by Taras Lushney on 8/05/15.
//  Copyright (c) 2015 Taras Lushney. All rights reserved.

#ifndef BYTE_H_
#define BYTE_H_

#include <cstdint>
#include <vector>

namespace core {

typedef std::uint8_t Byte;
typedef std::vector<Byte> Bytes;

// Returns string representation of vector of bytes
std::string ToString(const Bytes& bytes);

}  // namespace core

#endif  // BYTE_H_
