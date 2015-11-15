cmake_minimum_required (VERSION 3.0.0)
project (CFTAL)

set (CFTAL_VERSION_MAJ 0)
set (CFTAL_VERSION_MIN 1)
set (CFTAL_VERSION_PLV 0)
set (CFTAL_VERSION_STR "${CFTAL_VERSION_MAJ}.${CFTAL_VERSION_MIN}.${CFTAL_VERSION_PLV}")

option(CFTAL_USE_CXX17 "use C++17" ON)
if(CFTAL_USE_CXX17)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++-1z")
else(CFTAL_USE_CXX17)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++-14")
endif(CFTAL_USE_CXX17)


include_directories(.)

find_library(LIBM m)
if (LIBM)
	link_libraries(${LIBM})
endif(LIBM)
