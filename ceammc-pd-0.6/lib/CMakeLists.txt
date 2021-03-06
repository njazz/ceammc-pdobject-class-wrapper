include_directories(${CMAKE_BINARY_DIR}) # for config.h
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/utf8rewind)

set(LIBCEAMMC_COMPILE_FLAGS "${PD_EXTERNAL_CFLAGS}")
set(LIBCEAMMC_LINK_FLAGS ${PD_EXTERNAL_LDFLAGS})

if(WIN32)
    set(LIBCEAMMC_LINK_FLAGS "")
endif()

set(UTF8REWIND_SOURCES
    utf8rewind/utf8rewind.c
    utf8rewind/unicodedatabase.c
    utf8rewind/internal/casemapping.c
    utf8rewind/internal/codepoint.c
    utf8rewind/internal/composition.c
    utf8rewind/internal/database.c
    utf8rewind/internal/decomposition.c
    utf8rewind/internal/seeking.c
    utf8rewind/internal/streaming.c)

set(CEAMMC_LIB_SOURCES ceammc.h
    ceammc.hpp
    ceammc.c
    ceammc.cpp
    ceammc_abstractdata.cpp
    ceammc_array.cpp
    ceammc_atom.cpp
    ceammc_atomlist.cpp
    ceammc_canvas.cpp
    ceammc_control.cpp
    ceammc_convert.cpp
    ceammc_convert_pitch.cpp
    ceammc_data.cpp
    ceammc_datastorage.cpp
    ceammc_dataatom.cpp
    ceammc_dataatomlist.cpp
    ceammc_factory.h
    ceammc_faust.cpp
    ceammc_fn_list.cpp
    ceammc_fn_vector.cpp
    ceammc_format.cpp
    ceammc_impl.cpp
    ceammc_log.cpp
    ceammc_message.cpp
    ceammc_music_temperament.cpp
    ceammc_music_theory.cpp
    ceammc_music_theory_names.cpp
    ceammc_music_theory_pitch_class.cpp
    ceammc_object.cpp
    ceammc_pd.cpp
    ceammc_platform.cpp
    ceammc_preset.cpp
    ceammc_property.cpp
    ceammc_sound_external.cpp
    ceammc_string.cpp
    ceammc_thread.cpp
    ceammc_timeline.cpp
    ceammc_window.cpp

    ${UTF8REWIND_SOURCES})

if(UNIX)
    list(APPEND CEAMMC_LIB_SOURCES ceammc_platform_unix.cpp)
elseif(WIN32)
    list(APPEND CEAMMC_LIB_SOURCES ceammc_platform_win.cpp)
endif()

# main shared library
add_library(ceammc_core SHARED ${CEAMMC_LIB_SOURCES})
target_link_libraries(ceammc_core puredata-core)

set_target_properties(ceammc_core PROPERTIES
    COMPILE_FLAGS "${LIBCEAMMC_COMPILE_FLAGS}"
    LINK_FLAGS    "${LIBCEAMMC_LINK_FLAGS}")

if(WIN32)
    target_link_libraries(ceammc_core psapi shlwapi userenv puredata-core)

    # copy library to tests folder
    add_custom_command(TARGET ceammc_core POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:ceammc_core>"
            "${CMAKE_CURRENT_BINARY_DIR}/../tests")
endif()

#
# sound library
#
set(CEAMMC_LOAD_SRC
    ceammc_sound.h
    ceammc_sound.cpp
    array_load_pattern.h
    array_load_pattern.cpp)
set(CEAMMC_LOAD_LIBS "")
set(CEAMMC_LOAD_DEFS "")

if(LIBSNDFILE_FOUND)
    list(APPEND CEAMMC_LOAD_DEFS "-DWITH_LIBSOUNDFILE")
    list(APPEND CEAMMC_LOAD_LIBS ${LIBSNDFILE_LIBRARIES})
    list(APPEND CEAMMC_LOAD_SRC ceammc_loader_sndfile.cpp)

    include_directories(${LIBSNDFILE_INCLUDE_DIRS})
endif()

# coreaudio backend
if(APPLE AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    list(APPEND CEAMMC_LOAD_SRC
        ceammc_loader_coreaudio.cpp
        ceammc_loader_coreaudio_impl.m)
    find_library(FOUNDATION_LIBRARY Foundation)
    find_library(QUICKTIME_LIBRARY QuickTime)
    find_library(APP_SERVICES_LIBRARY ApplicationServices)

    list(APPEND CEAMMC_LOAD_LIBS ${FOUNDATION_LIBRARY})
endif()

add_library(ceammc_sound SHARED ${CEAMMC_LOAD_SRC})
set_target_properties(ceammc_sound PROPERTIES
    COMPILE_FLAGS "${LIBCEAMMC_COMPILE_FLAGS} ${CEAMMC_LOAD_DEFS}"
    LINK_FLAGS    "${LIBCEAMMC_LINK_FLAGS}")
target_link_libraries(ceammc_sound ${CEAMMC_LOAD_LIBS})

# install
if(WIN32)
    install(TARGETS ceammc_core  RUNTIME DESTINATION ${PD_INTERNAL_EXT_INSTALL_PATH}/ceammc)
    install(TARGETS ceammc_sound RUNTIME DESTINATION ${PD_INTERNAL_EXT_INSTALL_PATH}/ceammc)
else()
    install(TARGETS ceammc_core  LIBRARY DESTINATION ${PDCORE_LIB_INSTALL_PATH})
    install(TARGETS ceammc_sound LIBRARY DESTINATION ${PDCORE_LIB_INSTALL_PATH})
endif()

add_executable(ext_list ext_list.cpp ../mod_init.cpp)
target_link_libraries(ext_list puredata-core ${CEAMMC_EXT_LINK_LIBRARIES})
