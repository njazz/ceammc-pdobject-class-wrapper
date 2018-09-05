include_directories(Catch/single_include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${CMAKE_BINARY_DIR}) # for config.h
add_definitions("-DTEST_DATA_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\"")

if(WITH_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    
    find_program(LCOV NAMES lcov PATHS /usr/bin /usr/local/bin)
    find_program (GCOV NAMES gcov gcov-7 gcov-6 gcov-5 PATHS /usr/bin /usr/local/bin)

    if(LCOV AND GCOV)
        message(STATUS "lcov found: ${LCOV}")
        message(STATUS "gcov found: ${GCOV}")
        add_custom_target(coverage_wrapper
            COMMAND ${LCOV}
                --gcov-tool=${GCOV}
                --directory ${PROJECT_BINARY_DIR} #"${CMAKE_BINARY_DIR}"
                --capture
#                --remove "${CMAKE_SOURCE_DIR}/../imgui/imgui/*"
#                --remove "${CMAKE_SOURCE_DIR}/src/Properties/json/*"
#                --remove "${CMAKE_SOURCE_DIR}/tests/Catch/*"
                --output-file coverage_wrapper.info
            COMMAND ${LCOV}
                --extract coverage_wrapper.info
                    "${CMAKE_SOURCE_DIR}/src/*" 
#                --remove "${CMAKE_SOURCE_DIR}/../imgui/imgui/*"
#                --remove "${CMAKE_SOURCE_DIR}/src/Properties/json/*"
#                --remove "${CMAKE_SOURCE_DIR}/tests/Catch/*"
                --output-file coverage_wrapper.info
            COMMAND ${LCOV}
                --list coverage_wrapper.info)
#            WORKING_DIRECTORY ${PROJECT_BINARY_DIR}

        add_custom_target(coverage_report_wrapper
            COMMAND genhtml --output-directory ${CMAKE_BINARY_DIR}/coverage_wrapper coverage_wrapper.info
            COMMAND open ${CMAKE_BINARY_DIR}/coverage_wrapper/index.html)
    endif()
endif()

set(TEST_CEAMMC_LIB
    ../ceammc_lib/ceammc_abstractdata.cpp
    ../ceammc_lib/ceammc_atom.cpp
    ../ceammc_lib/ceammc_atomlist.cpp
    ../ceammc_lib/ceammc_data.cpp
    ../ceammc_lib/ceammc_dataatom.cpp
    ../ceammc_lib/ceammc_dataatomlist.cpp
    ../ceammc_lib/ceammc_datastorage.cpp
    ../ceammc_lib/ceammc_factory.h
    ../ceammc_lib/ceammc_format.cpp
    ../ceammc_lib/ceammc_log.cpp
    ../ceammc_lib/ceammc_message.cpp
    ../ceammc_lib/ceammc_object.cpp
    ../ceammc_lib/ceammc_property.cpp

    ../ceammc_lib/ceammc_object.cpp

)

file (GLOB TEST_PD
    "../tests/pd_sources/*.c"
    )
macro(wrapper_add_test title name)
    add_executable("test_${name}" "test_${name}.cpp" ${TEST_CEAMMC_LIB} ${TEST_PD})
    add_definitions(-DUSEAPI_DUMMY=1 -DPD=1 -DPD_INTERNAL=1 -DTHREAD_LOCKING=0 -DHAVE_UNISTD_H=1)
    INCLUDE_DIRECTORIES("../src/")
    target_link_libraries("test_${name}" test_catch_main_lib_wrapper )
    if (LCOV AND GCOV)
        target_link_libraries("test_${name}" gcov )
    endif()
    set(_exec_cmd "test_${name}")

    add_test(NAME ${title} COMMAND ${_exec_cmd})
endmacro()

add_library(test_catch_main_lib_wrapper STATIC tests_catch_main.cpp)

wrapper_add_test(abstract_data_wrap abstract_data_wrap)

wrapper_add_test(atomlist_wrapper atomlist_wrapper)





