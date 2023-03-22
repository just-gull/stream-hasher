cmake_minimum_required(VERSION 3.10.0)
project(stream-hasher VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenSSL 3 REQUIRED)

if (OPENSSL_FOUND)
  include_directories(${OPENSSL_INCLUDE_DIR})

  add_executable(stream-hasher
    src/main.cpp 
    src/hashing/hash-stream.cpp 
    src/hashing/hashing-exception.cpp
    src/openssl-wrapper/openssl-wrapper.cpp 
    src/openssl-wrapper/openssl-components.cpp 
  )
  target_link_libraries(stream-hasher OpenSSL::Crypto)
endif()