cmake_minimum_required (VERSION 2.8)

#set (CMAKE_OSX_DEPLOYMENT_TARGET "10.10")

set (CMAKE_PREFIX_PATH ~/Qt/5.8/clang_64)
set (CMAKE_CXX_STANDARD 11)

if (APPLE)
	set(CMAKE_MACOSX_RPATH FALSE)
endif()

#fixes warning for app name
cmake_policy(SET CMP0037 OLD)

project(wrapper_library)

set(CEAMMC_LIB_SOURCES
#    ceammc_lib/ceammc_abstractdata.cpp
#    ceammc_lib/ceammc_atom.cpp
#    ceammc_lib/ceammc_atomlist.cpp
#    ceammc_lib/ceammc_data.cpp
#    ceammc_lib/ceammc_dataatom.cpp
#    ceammc_lib/ceammc_dataatomlist.cpp
#    ceammc_lib/ceammc_datastorage.cpp
#    ceammc_lib/ceammc_factory.h
#    ceammc_lib/ceammc_format.cpp
#    ceammc_lib/ceammc_log.cpp
#    ceammc_lib/ceammc_message.cpp
#    ceammc_lib/ceammc_object.cpp
#    ceammc_lib/ceammc_property.cpp

#    ceammc_lib/ceammc_object.cpp

)

set (SOURCES

    "src/_SequenceT.hpp"
    "src/_FunctionTraits.hpp"
    "src/_AbstractDataWrapT.hpp"
    "src/_AtomListWrapperT.hpp"
    "src/_Converters.hpp"
    "src/_Invocations.hpp"

    "src/ClassConstructor.hpp"
    "src/ClassMethod.hpp"
    "src/ClassStaticMethod.hpp"

    "src/Macros.hpp"

    "src/Wrapper.hpp"

    "to_wrap/_generated.cpp"
)

file (GLOB WRAP_SOURCES
    "${PROJECT_SOURCE_DIR}/to_wrap/*.cpp"
    )

set (HEADERS
    ceammc_lib/ceammc_object.h 
    ceammc_lib/ceammc_message.h 
    ceammc_lib/ceammc_format.h 
    ceammc_lib/ceammc_log.h 
    ceammc_lib/ceammc_property.h 
)

find_package(Boost 1.47.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
include_directories( ${CMAKE_BINARY_DIR} )

include_directories(.)
include_directories(./src/)
include_directories(./ceammc_lib/)
include_directories(./pd_headers/)

include_directories(./to_wrap/)
include_directories(./to_include/)

LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/to_link/)

add_library(wrapper_library SHARED
    ${CEAMMC_LIB_SOURCES}
    ${WRAP_SOURCES}
    ${SOURCES} )

file (GLOB WRAP_LINK_LIBS
    "${PROJECT_SOURCE_DIR}/to_link/*.a"
    "${PROJECT_SOURCE_DIR}/to_link/*.dylib"
    )

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
target_link_libraries(wrapper_library "-undefined dynamic_lookup" ${WRAP_LINK_LIBS})
set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -undefined dynamic_lookup")
endif()

SET_TARGET_PROPERTIES(wrapper_library PROPERTIES PREFIX "")
set_target_properties(wrapper_library PROPERTIES SUFFIX ".pd_darwin")

#include(FindPythonInterp)
#find_package(PythonInterp 3.6 REQUIRED)

add_custom_target(
        generator_script ALL
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/to_wrap/_generated.cpp
)

add_custom_command(
        OUTPUT
            ${CMAKE_CURRENT_SOURCE_DIR}/to_wrap/_generated.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/build/_generated.pd
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/to_wrap/
        COMMAND cd ${CMAKE_SOURCE_DIR}/gen/ && ./run_scripts.sh
        #/usr/local/bin/python3 ${CMAKE_CURRENT_SOURCE_DIR}/gen/convert.py
)

add_custom_command(
    TARGET wrapper_library
    POST_BUILD
    COMMAND cp ${CMAKE_BINARY_DIR}/wrapper_library.pd_darwin ${CMAKE_BINARY_DIR}/help/wrapper_library.pd_darwin
    )

###
enable_testing(true)
add_subdirectory(tests)


