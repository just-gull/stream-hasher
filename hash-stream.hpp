#ifndef HASH_STREAM_H
#define HASH_STREAM_H

#include <cstddef>
#include <iostream>

class HashStream {
  size_t processed_bytes{};

  friend std::ostream& operator<<(std::ostream& out, const HashStream& o);
  
public:
  HashStream();
  ~HashStream();
};

#endif