#include "hashing-exception.hpp"

HashingException::HashingException(std::string message) 
  : message{ message } 
  {
  }

const char* HashingException::what() const noexcept
{
  return message.c_str();
}
