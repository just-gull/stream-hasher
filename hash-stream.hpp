#ifndef HASH_STREAM_H
#define HASH_STREAM_H

#include <cstddef>
#include <iostream>

#include "openssl-wrapper.hpp"

class HashStream {
  size_t processed_bytes{};
  OpenSSLWrapper wrapper;

  friend std::ostream& operator<<(std::ostream& out, const HashStream& o);
  
public:
  HashStream();
  ~HashStream();
};

#endif