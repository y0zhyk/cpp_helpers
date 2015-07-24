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
    if (size == 0) {
        return;
    }

    if (data == nullptr) {
        throw std::invalid_argument("MemoryStream::MemoryStream(): data == nullptr");
    }

    data_.assign(data, data + size);
}

size_t MemoryStream::size() const noexcept {
    return data_.size();
}

const Byte* MemoryStream::data() const noexcept {
    return data_.data();
}

const Blob& MemoryStream::blob() const noexcept {
    return data_;
}

void MemoryStream::Write(const Byte* data, const size_t size) {
    if (size == 0) {
        return;
    }

    if (data == nullptr) {
        throw std::invalid_argument("MemoryStream::Write(): data == nullptr");
    }

    const size_t current_size = data_.size();
    data_.resize(current_size + size);
    std::memcpy(data_.data() + current_size, data, size);
}

void MemoryStream::Read(Byte* data, const size_t size) {
    if (size == 0) {
        return;
    }

    if (data == nullptr) {
         throw std::invalid_argument("MemoryStream::Read(): data == nullptr");
    }

    if (size > this->size() - offset_) {
         throw std::out_of_range("MemoryStream::Read(): size > size_ - offset_");
    }

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
	for each (const Byte byte in data_) {
		ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(byte) << " ";
	}
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

MemoryStream& operator << (MemoryStream& ms, const Blob& blob) {
    ms << blob.size();
    ms.Write(blob.data(), blob.size());
    return ms;
}

MemoryStream& operator >> (MemoryStream& ms, Blob& blob) {
    size_t size = 0;
    ms >> size;
    blob.resize(size);
    ms.Read(blob.data(), blob.size());
    return ms;
}

}  // namespace core
