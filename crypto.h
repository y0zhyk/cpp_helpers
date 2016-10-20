//  Created by Taras Lushney on 9/15/15.
//  Copyright (c) 2015 Taras Lushney. All rights reserved.

#ifndef CRYPTO_H_
#define CRYPTO_H_

#include "byte.h"

// The SymmetricCipher interface represents the functionality of a cryptographic
// cipher used for encryption and decryption
class SymmetricCipher {
 public:
  // The chaining mode to use for encryption or decryption
  enum class Mode {
    ECB,  // Electronic Code Book (ECB)
    CBC,  // Cipher-Block Chaining (CBC)
    CFB,  // Cipher FeedBack (CFB)
    OFB,  // Output FeedBack (OFB)
    CTR,  // CounTer Mode (CTR)
  }
  // Encrypts data with the key and the parameters set
  virtual bool
  Encrypt(const Bytes& plain_text, Bytes& cipher_text) const = 0;
  virtual bool Encrypt(const Byte* plain_text, const size_t plain_text_size,
                       Bytes* cipher_text, size_t& cipher_text_size) const = 0;
  // Decrypts data with the key and the parameters set
  virtual bool Decrypt(const Bytes& cipher_text, Bytes& plain_text) const = 0;
  virtual bool Decrypt(const Byte* cipher_text, const size_t cipher_text_size,
                       Bytes* plain_text, size_t& plain_text_size) const = 0;
  // Sets a secret key to use in the symmetric cipher
  virtual void SetKey(const SymmetricKey* key) = 0;
  // Sets a chaining mode to use for encryption or decryption. Default is ECB
  virtual void SetMode(const Mode mode) = 0;
  // Sets initialization vector to use for encryption or decryption
  virtual void SetIV(const Bytes& iv);
  virtual void SetIV(const Byte* iv, const size_t size);
};

// The SymmetricKey interface represents the functionality of a cryptographic
// key used for encryption and decryption.
class SymmetricKey {
  // Returns size of key data in bytes
  virtual size_t size() const = 0;
  // Returns a direct pointer to the key buffer
  virtual Byte* data() const = 0;
};

//
class Hasher {
 public:
  class enum HashAlgorithm {
    SHA,     // SHA-1 cryptographic hash algorithm
    SHA256,  // SHA-256 cryptographic hash algorithm
    HMAC     // HMAC (Hash-based Message Authentication Code) algorithm
  }
  // Continues hashing of a message by consuming the next chunk of data
  virtual bool
  Update(const Bytes& message) = 0;
  virtual bool Update(const Byte* message, const size_t size) = 0;
  // Returns the hash of the message that has been hashed so far
  virtual bool GetHash(Bytes& hash) const = 0;
  virtual bool GetHash(Byte* hash_text, const size_t cipher_text_size,
                       Bytes* plain_text, size_t& hash_size) const = 0;
  // Resets
  virtual void Reset() = 0;
  // Compures hash
  virtual bool ComputeHash(const Bytes& message, Bytes& hash) const = 0;
  virtual bool ComputeHash(const Byte* message, const size_t message_size,
                           Bytes* hash, size_t& hash_size) const = 0;
  // Sets cryptographic hash algorithm
  virtual bool SetAlgorithm(const HashAlgorithm algorithm)
};

class SecurityFactory {
  // Creates a symmetric cipher key
  virtual SymmetricKey* CreateSymmetricKey(const Bytes& key) const = 0;
  virtual SymmetricKey* CreateSymmetricKey(const Byte* key_data,
                                           const size_t size) const = 0;
  // Creates a symmetric cipher with given parametrs
  virtual SymmetricCipher* CreateSymmetricCipher(
      const SymmetricKey* key = nullptr,
      const SymmetricCipher::Mode mode = SymmetricCipher::ECB,
      const Bytes& iv) const = 0;
  // Creates hasher with given parametrs
  virtual Hasher* CreateHasher(const Hasher::HashAlgorithm algorithm) = 0;
};

#endif  // CRYPTO_H_