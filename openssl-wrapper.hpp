#ifndef OPENSSL_WRAPPER_H
#define OPENSSL_WRAPPER_H

extern "C" {
  #include <openssl/evp.h>
}

class OpenSSLWrapper {
  OSSL_LIB_CTX *library_context;

public:
  OpenSSLWrapper();
  ~OpenSSLWrapper();
};

#endif