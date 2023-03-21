#include "openssl-wrapper.hpp"

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "hashing-exception.hpp"

extern "C" {
  #include <openssl/evp.h>
}

// Private OpenSSL Wrapper classes
class OpenSSLContext {
  OSSL_LIB_CTX *ctx;

public:
  OpenSSLContext() : ctx{ nullptr }
  {
    ctx = OSSL_LIB_CTX_new();
    if (!ctx) {
      throw HashingException { "OSSL_LIB_CTX_new() returned nullptr" };
    }
    std::cout << "OpenSSLContext constructor finished" << std::endl;
  }
  ~OpenSSLContext()
  {
    OSSL_LIB_CTX_free(ctx);
    std::cout << "OpenSSLContext destructor finished" << std::endl;
  }

  OSSL_LIB_CTX* library_context()
  {
    return ctx;
  } 
};

class OpenSSLMessageDigest {
  OpenSSLContext context;
  EVP_MD *md;

public:
  OpenSSLMessageDigest() : md{ nullptr }
  {
    // auto val = contextlibrary_context();
    md = EVP_MD_fetch(context.library_context(), "SHA1", nullptr);
    if (!md) {
      throw HashingException { "EVP_MD_fetch could not find SHA1" };
    }
    std::cout << "OpenSSLMessageDigest constructor finished" << std::endl;
  }
  ~OpenSSLMessageDigest()
  {
    EVP_MD_free(md);
    std::cout << "OpenSSLMessageDigest destructor finished" << std::endl;
  }

  EVP_MD* message_digest() const
  {
    return md;
  }
};

class OpenSSLDigestContext {
  EVP_MD_CTX *ctx;

public:
  OpenSSLDigestContext() : ctx{ nullptr }
  {
    ctx = EVP_MD_CTX_new();
    if (!ctx) {
      throw HashingException { "EVP_MD_CTX_new failed." };
    }
    std::cout << "OpenSSLDigestContext constructor finished" << std::endl;
  }
  ~OpenSSLDigestContext()
  {
    EVP_MD_CTX_free(ctx);
    std::cout << "OpenSSLDigestContext destructor finished" << std::endl;
  }

  EVP_MD_CTX* digest_context()
  {
    return ctx;
  }   
};

class OpenSSLMemoryBuffer {
  size_t size;
  unsigned char *mb;

public:
  OpenSSLMemoryBuffer(size_t size) : size{ size }, mb{ nullptr }
  {
    mb = static_cast<unsigned char*>(OPENSSL_malloc(size));
    if (mb == nullptr) {
      throw HashingException { "No memory." }; 
    }    
    std::cout << "OpenSSLMemoryBuffer constructor finished" << std::endl;
  }

  ~OpenSSLMemoryBuffer()
  {
    OPENSSL_free(mb);
    std::cout << "OpenSSLMemoryBuffer destructor finished" << std::endl;
  }

  unsigned char* memory_buffer()
  {
    return mb;
  }

};

// OpenSSLWrapper implementation

OpenSSLWrapper::OpenSSLWrapper() 
  : md{ std::make_unique<OpenSSLMessageDigest>() },
    digest_ctx{ std::make_unique<OpenSSLDigestContext>() } //: library_context{ nullptr }
{
  std::cout << "OpenSSLWrapper constructor called" << std::endl;
}

OpenSSLWrapper::~OpenSSLWrapper()
{
  std::cout << "OpenSSLWrapper destructor called" << std::endl;
}

void OpenSSLWrapper::init() 
{
  if (EVP_DigestInit(digest_ctx->digest_context(), md->message_digest()) != 1) {
      throw HashingException { "EVP_DigestInit failed." };
  }
  initialized = true;
}

void OpenSSLWrapper::updateDigest(char* buffer, size_t buffer_size)
{
  if (!initialized) {
      throw HashingException { "OpenSSLWrapper must be initialized before updateDigest." };
  }
  if (EVP_DigestUpdate(digest_ctx->digest_context(), buffer, buffer_size) != 1) {
      throw HashingException { "EVP_DigestUpdate() failed." };
  }
}

std::string OpenSSLWrapper::digestValue()
{
  if (!initialized) {
      throw HashingException { "OpenSSLWrapper must be initialized before digestValue." };
  }
  // unsigned char *digest_value = nullptr;
  unsigned int digest_length = EVP_MD_get_size(md->message_digest());
  if (digest_length <= 0) {
    throw HashingException { "EVP_MD_get_size returned invalid size." };
  }
  OpenSSLMemoryBuffer digest_value{ digest_length };
  if (EVP_DigestFinal(digest_ctx->digest_context(), digest_value.memory_buffer(), &digest_length) != 1) {
    throw HashingException { "EVP_DigestFinal() failed." };
  }
  // converting buffer to hex string
  std::stringstream ss;
  for (size_t i{}; i < digest_length; i++) {
    std::stringstream hex_char_stream;
    hex_char_stream << std::setfill('0') << std::setw(2) << std::hex; 
    hex_char_stream << static_cast<int>(digest_value.memory_buffer()[i]);
    ss << hex_char_stream.str();
  }
  initialized = false;
  return ss.str();
}
