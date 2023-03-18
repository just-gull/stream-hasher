#include <iostream>
#include <stdexcept>

#include "hash-stream.hpp"

int main() {
  try {
    HashStream hash_stream;
    std::cout << hash_stream << std::endl;
  } catch (const std::exception& ex) {
    std::cerr << "Error: " << ex.what() << std::endl;
  }
}
