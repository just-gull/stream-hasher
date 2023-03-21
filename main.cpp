#include <iostream>
#include <stdexcept>
#include <fstream>

#include "hash-stream.hpp"
#include "hashing-exception.hpp"

int main() {
  try {
    HashStream hash_stream;
    std::ifstream binary_stdin{ "/dev/stdin", std::ios::binary };
    binary_stdin >> hash_stream;
    std::cout << hash_stream << std::endl;
    binary_stdin.close();
  } catch (const HashingException& ex) {
    std::cerr << "Error: " << ex.what() << std::endl;
    // проверяем наличие ошибок OpenSSL и печатаем их если они есть
    const auto& openssl_errors = ex.get_openssl_errors();
    if (openssl_errors.size()) {
      std::cerr << "OpenSSL Errors: " << std::endl;
      for (const auto& error : openssl_errors) {
        std::cerr << error << std::endl;
      }
    }
  }
}
