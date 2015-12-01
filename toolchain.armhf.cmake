set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR armv7l)

# specify the cross compiler
SET(CMAKE_C_COMPILER   "/usr/bin/arm-linux-gnueabihf-gcc")
SET(CMAKE_CXX_COMPILER "/usr/bin/arm-linux-gnueabihf-g++")

set(CMAKE_C_FLAGS "-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE
-D_FILE_OFFSET_BITS=64 -Os ${CMAKE_C_FLAGS}" CACHE STRING "Buildroot
CFLAGS")
set(CMAKE_CXX_FLAGS "-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE
-D_FILE_OFFSET_BITS=64 -Os ${CMAKE_CXX_FLAGS}" CACHE STRING "Buildroot
CXXFLAGS")
set(CMAKE_EXE_LINKER_FLAGS " ${CMAKE_EXE_LINKER_FLAGS}" CACHE STRING
"Buildroot LDFLAGS")
set(CMAKE_INSTALL_SO_NO_EXE 0)

set(CMAKE_PROGRAM_PATH "/usr/bin")
set(CMAKE_FIND_ROOT_PATH "/usr/lib/arm-linux-gnueabihf/cmake")
set(CMAKE_PREFIX_PATH "/usr/lib/arm-linux-gnueabihf/cmake")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(ENV{PKG_CONFIG_SYSROOT_DIR} "/usr/lib/arm-linux-gnueabihf/")
