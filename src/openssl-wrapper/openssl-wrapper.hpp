#ifndef OPENSSL_WRAPPER_H
#define OPENSSL_WRAPPER_H

#include <memory>
#include <string>

class OpenSSLMessageDigest;
class OpenSSLDigestContext;

class OpenSSLWrapper {
  std::unique_ptr<OpenSSLMessageDigest> md;
  std::unique_ptr<OpenSSLDigestContext> digest_ctx;
  bool initialized{ false };

public:
  OpenSSLWrapper();
  ~OpenSSLWrapper();
  void init();
  void updateDigest(char* buffer, size_t buffer_size);
  std::string digestValue();
};

#endif