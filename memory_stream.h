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

#include "byte.h"

namespace core {

class MemoryStream {
 public:
    // Initializes a new empty instance of the MemoryStream.
    MemoryStream() noexcept = default;
    // Initializes a new instance of the MemoryStream class based on the specified block of bytes.
    MemoryStream(const Byte* data, const size_t size);

    MemoryStream(const MemoryStream& other) = default;

    MemoryStream& operator=(const MemoryStream& other) = default;

    MemoryStream(MemoryStream&& other) = default;

    MemoryStream& operator=(MemoryStream&& other) = default;

    ~MemoryStream() noexcept = default;
    // Returns size of data in buffer in bytes.
    size_t size() const noexcept;
    // Returns a direct pointer to the buffer.
    const Byte* data() const noexcept;
    // Returns reference to a blob that owns the buffer.
    const Bytes& bytes() const noexcept;
    // Reads a block of bytes from the stream and writes the data to a buffer.
    void Read(Byte* data, const size_t size);
    // Writes a block of bytes to the stream.
    void Write(const Byte* data, const size_t size);

    void Clear() noexcept;
    // Returns a string that represents the stream.
    std::string ToString() const noexcept;

    static MemoryStream FromBytes(const Bytes& bytes);
    static MemoryStream FromBytes(Bytes&& bytes);

    MemoryStream& operator << (const MemoryStream& ms);
    MemoryStream& operator >> (MemoryStream& ms);

 private:
    Bytes data_;
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

MemoryStream& operator << (MemoryStream& ms, const Bytes& bytes);
MemoryStream& operator >> (MemoryStream& ms, Bytes& bytes);

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

template<class T>
MemoryStream& operator << (MemoryStream& ms, const std::vector<T>& vec) {
    ms << vec.size();
    for (const T& element: vec)
        ms << element;
    return ms;
}

template<class T>
MemoryStream& operator >> (MemoryStream& ms, std::vector<T>& vec) {
    size_t size = 0;
    ms >> size;
    vec.resize(size);
    for (T& element: vec)
        ms >> element;
    return ms;
}

};  // namespace core

#endif  // MEMORY_STREAM_H_
