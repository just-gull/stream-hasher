#ifndef HASHING_EXCEPTION_H
#define HASHING_EXCEPTION_H

#include <stdexcept>
#include <string>
#include <vector>

class HashingException : std::exception {
  std::string message;
  std::vector<std::string> openssl_errors;
public:
  HashingException(std::string message);
  const char* what() const noexcept;
  const std::vector<std::string>& get_openssl_errors() const noexcept;
};

#endif