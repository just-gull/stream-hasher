#include <iostream>
#include <stdexcept>

#include "hash-stream.hpp"
#include "hashing-exception.hpp"

int main() {
  try {
    HashStream hash_stream;
    std::cout << hash_stream << std::endl;
  } catch (const HashingException& ex) {
    std::cerr << "Error: " << ex.what() << std::endl;
  }
}
