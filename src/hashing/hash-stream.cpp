#include "hash-stream.hpp"

#include "hashing-exception.hpp"

std::ostream& operator<<(std::ostream& out, HashStream& hs)
{
  if (hs.processed_bytes) {
    return out << hs.wrapper.digestValue();
  } else {
    return out << "<no-data>";
  }
}

std::istream& operator>>(std::istream& input, HashStream& hs)
{
  if (input) {
    hs.wrapper.init();
    size_t buffer_size = 512;
    char buffer[buffer_size];
    while (!input.eof()) {
      input.read(buffer, buffer_size);
      if (input.bad()) break; // stopping if input is gone bad
      hs.wrapper.updateDigest(buffer, input.gcount());
      hs.processed_bytes += input.gcount();
    }
    if (input.bad() && !input.eof()) {
      throw HashingException{ "Input error!" };
    }
  }
  return input;
}

HashStream::HashStream() 
{
}

HashStream::~HashStream()
{
}