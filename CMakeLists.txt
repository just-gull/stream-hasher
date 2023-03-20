cmake_minimum_required(VERSION 3.10.0)
project(stream-hasher VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenSSL REQUIRED)

if (OPENSSL_FOUND)
  include_directories(${OPENSSL_INCLUDE_DIR})

  add_executable(stream-hasher
    main.cpp 
    hash-stream.cpp 
    openssl-wrapper.cpp 
    hashing-exception.cpp
  )
  target_link_libraries(stream-hasher OpenSSL::Crypto)
endif()