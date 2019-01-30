cmake_minimum_required (VERSION 3.5)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin) 

project (rubidum2018)

set(ADD_CXX_FLAGS "")
include(CheckCXXCompilerFlag)

set(CXX_FLAG "/w14242")
check_cxx_compiler_flag(CXX_FLAG HAS_CXX_FLAG)
if (HAS_CXX_FLAG)
   set(ADD_CXX_FLAGS "${ADD_CXX_FLAGS} ${CXX_FLAG}")
endif()
   
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADD_CXX_FLAGS}")

add_executable(rubidium rubidium.cpp)