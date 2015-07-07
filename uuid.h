//
//  uuid.h
//
//  Created by Taras Lushney on 7/01/15.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.
//

#ifndef UUID_H_
#define UUID_H_

class Uuid {
 public:
    explicit Uuid(bool is_short = false);

    explicit Uuid(std::uint32_t uuid);

    explicit Uuid(const std::string& uuid, bool is_short = false);

    explicit Uuid(const std::array<Byte, 16>& uuid);

    Uuid(const Uuid& uuid);

    Uuid(Uuid&& uuid) = default;

    ~Uuid() noexept = default;

   const Uuid& operator=(const Uuid& uuid);

   std::string ToString() const;

 private:
    class UuidImpl;
    std::unique_ptr<UuidImpl> impl_;
}

inline std::string Uuid::ToString() const {
    impl_->ToString();
}

#endif  // UUID_H_
