cmake_minimum_required(VERSION 3.0.0)
project(calculator VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(calculator 
    calculator.cpp
    token_stream.cpp
    token_stream.h
    token_utils.cpp
    token_utils.h
    token.h    
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
