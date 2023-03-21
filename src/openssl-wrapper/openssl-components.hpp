#ifndef OPENSSL_COMPONENTS_H
#define OPENSSL_COMPONENTS_H

extern "C" {
  #include <openssl/evp.h>
}

class OpenSSLContext {
  OSSL_LIB_CTX *ctx;

public:
  OpenSSLContext();
  ~OpenSSLContext();
  OSSL_LIB_CTX* library_context();
};

class OpenSSLMessageDigest {
  OpenSSLContext context;
  EVP_MD *md;

public:
  OpenSSLMessageDigest();
  ~OpenSSLMessageDigest();
  EVP_MD* message_digest() const;
};

class OpenSSLDigestContext {
  EVP_MD_CTX *ctx;

public:
  OpenSSLDigestContext();
  ~OpenSSLDigestContext();
  EVP_MD_CTX* digest_context();
};

class OpenSSLMemoryBuffer {
  size_t size;
  unsigned char *mb;

public:
  OpenSSLMemoryBuffer(size_t size);
  ~OpenSSLMemoryBuffer();
  unsigned char* memory_buffer();
};

#endif