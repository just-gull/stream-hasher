#include "hashing-exception.hpp"

#include <memory>

extern "C" {
  #include <openssl/err.h>
}

HashingException::HashingException(std::string message) 
  : message{ message } 
{
  ERR_print_errors_cb([](const char* error_str, size_t len, void* user_data) -> int {
    std::vector<std::string>* errors = static_cast<std::vector<std::string>*>(user_data);
    errors->push_back(std::string{ error_str });
    return 0;
  }, &(this->openssl_errors));
}

const char* HashingException::what() const noexcept
{
  return message.c_str();
}

const std::vector<std::string>& HashingException::get_openssl_errors() const noexcept
{
  return openssl_errors;
}
