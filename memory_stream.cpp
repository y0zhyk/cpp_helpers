//
//  memory_stream.cpp
//
//  Created by Taras Lushney on 2/7/15.
//  Copyright (c) 2015 Taras Lushney. All rights reserved.
//

#include <sstream>
#include <iterator>
#include <iomanip>

#include "./memory_stream.h"

namespace core {

MemoryStream::MemoryStream(const Byte* data, const size_t size) {
    if (size == 0)
        return;

    if (data == nullptr)
        throw std::invalid_argument("MemoryStream::MemoryStream(): data == nullptr");

    data_.assign(data, data + size);
}

size_t MemoryStream::size() const noexcept {
    return data_.size();
}

const Byte* MemoryStream::data() const noexcept {
    return data_.data();
}

const Bytes& MemoryStream::bytes() const noexcept {
    return data_;
}

void MemoryStream::Write(const Byte* data, const size_t size) {
    if (size == 0)
        return;

    if (data == nullptr)
        throw std::invalid_argument("MemoryStream::Write(): data == nullptr");

    const size_t current_size = data_.size();
    data_.resize(current_size + size);
    std::memcpy(data_.data() + current_size, data, size);
}

void MemoryStream::Read(Byte* data, const size_t size) {
    if (size == 0)
        return;

    if (data == nullptr)
         throw std::invalid_argument("MemoryStream::Read(): data == nullptr");

    if (size > this->size() - offset_)
         throw std::out_of_range("MemoryStream::Read(): size > size_ - offset_");

    std::memcpy(data, data_.data() + offset_, size);
    offset_ += size;
}

void MemoryStream::Clear() noexcept {
    data_.clear();
    offset_ = 0;
}

std::string MemoryStream::ToString() const noexcept {
    std::stringstream ss;
    ss << "{ size=" << size() << " offset=" << offset_ <<" ";
    for (const Byte byte: data_)
        ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(byte) << " ";

    ss << "}";
    return ss.str();
}

MemoryStream& MemoryStream::operator << (const MemoryStream& ms) {
    Write(ms.data(), ms.size());
    return *this;
}

MemoryStream& MemoryStream::operator >> (MemoryStream& ms) {
    ms.Clear();
    const size_t size = data_.size() - offset_;
    ms.Write(data_.data() + offset_, size);
    offset_ += size;
    return *this;
}

MemoryStream& operator << (MemoryStream& ms, const Bytes& bytes) {
    ms << bytes.size();
    ms.Write(bytes.data(), bytes.size());
    return ms;
}

MemoryStream& operator >> (MemoryStream& ms, Bytes& bytes) {
    size_t size = 0;
    ms >> size;
    bytes.resize(size);
    ms.Read(bytes.data(), bytes.size());
    return ms;
}

}  // namespace core
