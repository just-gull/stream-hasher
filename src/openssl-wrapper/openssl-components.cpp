#include "openssl-components.hpp"

#include "../hashing/hashing-exception.hpp"


// OpenSSLContext implementation
OpenSSLContext::OpenSSLContext() : ctx{ nullptr }
{
  ctx = OSSL_LIB_CTX_new();
  if (!ctx) {
    throw HashingException { "OSSL_LIB_CTX_new() returned nullptr" };
  }
}

OpenSSLContext::~OpenSSLContext()
{
  OSSL_LIB_CTX_free(ctx);
}

OSSL_LIB_CTX* OpenSSLContext::library_context()
{
  return ctx;
} 

// OpenSSLMessageDigest implementation
OpenSSLMessageDigest::OpenSSLMessageDigest() : md{ nullptr }
{
  // auto val = contextlibrary_context();
  md = EVP_MD_fetch(context.library_context(), "SHA1", nullptr);
  if (!md) {
    throw HashingException { "EVP_MD_fetch could not find SHA1" };
  }
}

OpenSSLMessageDigest::~OpenSSLMessageDigest()
{
  EVP_MD_free(md);
}

EVP_MD* OpenSSLMessageDigest::message_digest() const
{
  return md;
}

// OpenSSLDigestContext implementation
OpenSSLDigestContext::OpenSSLDigestContext() : ctx{ nullptr }
{
  ctx = EVP_MD_CTX_new();
  if (!ctx) {
    throw HashingException { "EVP_MD_CTX_new failed." };
  }
}

OpenSSLDigestContext::~OpenSSLDigestContext()
{
  EVP_MD_CTX_free(ctx);
}

EVP_MD_CTX* OpenSSLDigestContext::digest_context()
{
  return ctx;
}   

// OpenSSLMemoryBuffer implementation
OpenSSLMemoryBuffer::OpenSSLMemoryBuffer(size_t size) : size{ size }, mb{ nullptr }
{
  mb = static_cast<unsigned char*>(OPENSSL_malloc(size));
  if (mb == nullptr) {
    throw HashingException { "No memory." }; 
  }    
}

OpenSSLMemoryBuffer::~OpenSSLMemoryBuffer()
{
  OPENSSL_free(mb);
}

unsigned char* OpenSSLMemoryBuffer::memory_buffer()
{
  return mb;
}
