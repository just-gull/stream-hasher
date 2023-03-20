#include "openssl-wrapper.hpp"

#include <iostream>
#include <stdexcept>

#include "hashing-exception.hpp"

OpenSSLWrapper::OpenSSLWrapper() : library_context{ nullptr }
{
  library_context = OSSL_LIB_CTX_new();
  if (!library_context) {
    throw HashingException { "OSSL_LIB_CTX_new() returned nullptr\n" };
  }
  std::cout << "OpenSSLWrapper constructor called" << std::endl;
}

OpenSSLWrapper::~OpenSSLWrapper()
{
  OSSL_LIB_CTX_free(library_context);
  std::cout << "OpenSSLWrapper destructor called" << std::endl;
}