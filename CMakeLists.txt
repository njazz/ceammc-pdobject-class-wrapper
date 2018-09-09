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

find_package(Boost 1.50.0 REQUIRED)

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

    "generated/generated.cpp"

    "src/_ConvertToPdType.cpp"
    "src/_ConvertFromPdType.cpp"

    "src/_ConvertToCEAMMCType.cpp"
    "src/_ConvertFromCEAMMCType.cpp"

    ###
#    "ceammc-pd-0.6/data/datatype_dict.cpp"
)

# exclude when it is submodule:
if (WRAPPER_SUBMODULE=="YES")
    set(WRAP_SOURCES_TEST)
else()
file (GLOB WRAP_SOURCES_TEST
    "${PROJECT_SOURCE_DIR}/to_build/*.c"
    "${PROJECT_SOURCE_DIR}/to_build/*.cpp"
    )
endif()

include_directories(./to_wrap/)
include_directories(./to_include/)
###

file (GLOB WRAP_SOURCES
    "${PROJECT_SOURCE_DIR}/../to_build/*.c"
    "${PROJECT_SOURCE_DIR}/../to_build/*.cpp"
    )
include_directories(./to_wrap/)
include_directories(./to_include/)

#cfg
file (GLOB WRAP_CFG
    "${PROJECT_SOURCE_DIR}/../library_info.cfg"
    )

set (HEADERS
    ceammc_lib/ceammc_object.h 
    ceammc_lib/ceammc_message.h 
    ceammc_lib/ceammc_format.h 
    ceammc_lib/ceammc_log.h 
    ceammc_lib/ceammc_property.h 
)

#
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fblocks")

#
find_package(Boost 1.47.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
include_directories( ${CMAKE_BINARY_DIR} )

include_directories(.)
include_directories(./src/)

include_directories(./ceammc-pd-0.6/lib)
include_directories(./ceammc-pd-0.6/data)
include_directories(./ceammc-pd-0.6/string)

include_directories(./pd_headers/)

LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/to_link/)

add_library(wrapper_library SHARED
    ${CEAMMC_LIB_SOURCES}
    ${WRAP_SOURCES}
    ${WRAP_SOURCES_TEST}
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
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/generated/generated.cpp
)

add_custom_command(
        OUTPUT
            ${CMAKE_CURRENT_SOURCE_DIR}/generated/generated.cpp
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/to_wrap/
        COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/scripts/ && ./run_scripts.sh ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${WRAP_CFG}

)

add_custom_command(
    TARGET wrapper_library
    POST_BUILD
    COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/scripts/ && ./post_build_script.sh ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
    )

###
enable_testing(true)
add_subdirectory(tests)


