cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
set(CMAKE_VERBOSE_MAKEFILE ON)

project(dnssaver)

# CMake Version control
set(CMAKE_PROJECT_VERSION 1.0.0)
set(CMAKE_PROJECT_VERSION_MAJOR 1)
set(CMAKE_PROJECT_VERSION_MINOR 0)
set(CMAKE_PROJECT_VERSION_PATCH 0)

option(BUILD_CLI "Build ${PROJECT_NAME} example programs" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# All source files in this project
set(DNS_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/bintotext.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/copyfile.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/data.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/filetype.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/texttobin.cc"
)
# All header files in this project
set(DNS_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/dnssaver/dnssaver.h"
)

set(DNS_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Prefer libc++ in conjunction with Clang, not on Windows
if (NOT MSVC)
  if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND NOT CMAKE_CXX_FLAGS MATCHES "-stdlib=libc\\+\\+")
    CHECK_CXX_COMPILER_AND_LINKER_FLAGS_BASE(HAS_LIBCPP "-stdlib=libc++" "-stdlib=libc++")
    if (HAS_LIBCPP)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -D_LIBCPP_VERSION")
      set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
      set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -stdlib=libc++")
      message(STATUS "${PROJECT_NAME}: using libc++.")
    else()
    CHECK_CXX_COMPILER_AND_LINKER_FLAGS_BASE(HAS_LIBCPP_AND_CPPABI "-stdlib=libc++" "-stdlib=libc++ -lc++abi")
      if (HAS_LIBCPP_AND_CPPABI)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -D_LIBCPP_VERSION")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
        message(STATUS "${PROJECT_NAME}: using libc++ and libc++abi.")
      else()
        message(FATAL_ERROR "When Clang is used to compile ${PROJECT_NAME}, libc++ must be available -- GCC's libstdc++ is not supported! (please insteall the libc++ development headers, provided e.g. by the packages 'libc++-dev' and 'libc++abi-dev' on Debian/Ubuntu).")
      endif()
    endif()
  endif()
endif()

add_library(${PROJECT_NAME} ${DNS_SOURCES} ${DNS_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${DNS_INCLUDE})

# Build examples
if (BUILD_CLI)
    set(DNS_CLI_INTERFACE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/main.cc")
    add_executable(dns_cli ${DNS_CLI_INTERFACE_SRC})
    target_include_directories(dns_cli PUBLIC ${DNS_INCLUDE})
    target_link_libraries(dns_cli PUBLIC ${PROJECT_NAME})
endif()