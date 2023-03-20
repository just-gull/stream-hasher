#ifndef HASHING_EXCEPTION_H
#define HASHING_EXCEPTION_H

#include <stdexcept>
#include <string>

class HashingException : std::exception {
  std::string message;
public:
  HashingException(std::string message);
  const char* what() const noexcept;
};

#endif