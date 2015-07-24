//
//  memory_stream.h
//
//  Created by Taras Lushney on 2/7/15.
//  Copyright (c) 2015 Taras Lushney. All rights reserved.

#ifndef MEMORY_STREAM_H_
#define MEMORY_STREAM_H_

#include <vector>
#include <string>
#include <type_traits>

#include "blob.h"

namespace core {

class MemoryStream {
 public:
    // Initializes a new empty instance of the MemoryStream.
    MemoryStream() noexcept = default;
    // Initializes a new instance of the MemoryStream class based on the specified block of bytes.
    MemoryStream(const Byte* data, const size_t size);

    ~MemoryStream() noexcept = default;
    // Returns size of data in buffer in bytes.
    inline size_t size() const noexcept;
    // Returns a direct pointer to the buffer.
    inline const Byte* data() const noexcept;
    // Returns reference to a blob that owns the buffer.
    const Blob& blob() const noexcept;
    // Reads a block of bytes from the stream and writes the data to a buffer.
    void Read(Byte* data, const size_t size);
    // Writes a block of bytes to the stream.
    void Write(const Byte* data, const size_t size);

    void Clear() noexcept;

    // Returns a string that represents the stream.
    std::string ToString() const noexcept;

    MemoryStream& operator << (const MemoryStream& ms);
    MemoryStream& operator >> (MemoryStream& ms);

 private:
    Blob data_;
    size_t offset_ = 0;
};


template <class T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
MemoryStream& operator << (MemoryStream& ms, const T data) {
    ms.Write(reinterpret_cast<const Byte*>(&data), sizeof(T));
    return ms;
}

template <class T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
MemoryStream& operator >> (MemoryStream& ms, T& data) {
    ms.Read(reinterpret_cast<Byte*>(&data), sizeof(T));
    return ms;
}

MemoryStream& operator << (MemoryStream& ms, const Blob& blob);
MemoryStream& operator >> (MemoryStream& ms, Blob& blob);

template<class T>
MemoryStream& operator << (MemoryStream& ms, const std::basic_string<T>& str) {
    ms << str.length();
    ms.Write(reinterpret_cast<const Byte*>(str.data()), sizeof(T) * str.length());
    return ms;
}

template<class T>
MemoryStream& operator >> (MemoryStream& ms, std::basic_string<T>& str) {
    size_t length = 0;
    ms >> length;
    str.resize(length);
    ms.Read(reinterpret_cast<Byte*>(const_cast<T*>(str.data())), sizeof(T) * str.length());
    return ms;
}

}  // namespace core

#endif  // MEMORY_STREAM_H_
