cmake_minimum_required (VERSION 3.5)

project (rubidum2018 CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin") 

list(APPEND ADD_CXX_FLAGS "/w14242" "/w14254" "/w14263" "/w14265" "/w14287" "/we4289" "/w14296" "/w14311")
list(APPEND ADD_CXX_FLAGS "/w14545" "/w14546" "/w14263" "/w14547" "/w14549" "/w14555" "/w14619" "/w14640")
list(APPEND ADD_CXX_FLAGS "/w14826" "/w14905" "/w14906" "/w14928" "/EHsc")


list(APPEND ADD_CXX_FLAGS "-Wall -Wextra" "-Wshadow" "-Wnon-virtual-dtor" "-pedantic" "-Wold-style-cast" "-Wcast-align" "-Wunused")
list(APPEND ADD_CXX_FLAGS "-Woverloaded-virtual" "-Wpedantic" "-Wsign-conversion" "-Wmisleading-indentation" "-Wduplicated-cond")
list(APPEND ADD_CXX_FLAGS "-Wduplicated-branches" "-Wlogical-op" "-Wnull-dereference" "-Wuseless-cast" "-Wdouble-promotion")
list(APPEND ADD_CXX_FLAGS "-Wlifetime")

include(CheckCXXCompilerFlag)
foreach(CXX_FLAG ${ADD_CXX_FLAGS})
    check_cxx_compiler_flag(${CXX_FLAG} HAS_CXX_FLAG_${CXX_FLAG})
    if (HAS_CXX_FLAG_${CXX_FLAG})
            message("Adding compiler flag ${CXX_FLAG}")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAG}")
    endif()
endforeach()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS)

add_executable(rubidium rubidium.cpp)
target_link_libraries(rubidium ${CONAN_LIBS})