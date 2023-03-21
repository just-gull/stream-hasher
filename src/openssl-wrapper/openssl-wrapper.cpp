#include "openssl-wrapper.hpp"

#include <sstream>
#include <iomanip>

#include "../hashing/hashing-exception.hpp"
#include "openssl-components.hpp"

extern "C" {
  #include <openssl/evp.h>
}

OpenSSLWrapper::OpenSSLWrapper() 
  : md{ std::make_unique<OpenSSLMessageDigest>() },
    digest_ctx{ std::make_unique<OpenSSLDigestContext>() }
{
}

OpenSSLWrapper::~OpenSSLWrapper()
{
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
