#ifndef HASH_STREAM_H
#define HASH_STREAM_H

#include <cstddef>
#include <iostream>

#include "openssl-wrapper.hpp"

class HashStream {
  size_t processed_bytes{};
  OpenSSLWrapper wrapper;

  friend std::ostream& operator<<(std::ostream& out, HashStream& o);
  friend std::istream& operator>>(std::istream& input, HashStream& value);
  
public:
  HashStream();
  ~HashStream();
};


#endif