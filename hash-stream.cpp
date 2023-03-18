#include "hash-stream.hpp"

std::ostream& operator<<(std::ostream& out, const HashStream& hs)
{
  if (hs.processed_bytes) {
    return out << "<has-data>";
  } else {
    return out << "<no-data>";
  }
}

HashStream::HashStream() 
{
  std::cout << "HashStream constructor called" << std::endl;
}

HashStream::~HashStream()
{
  std::cout << "HashStream destructor called" << std::endl;
}