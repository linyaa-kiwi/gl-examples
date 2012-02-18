project(GL_EXAMPLES)
cmake_minimum_required(VERSION 2.8)

# ------------------------------------------------------------------------------
# Compiler Flags
# ------------------------------------------------------------------------------

set(C_FLAGS_COMMON "-Wall -DGL_GLEXT_PROTOTYPES -DGLX_GLXEXT_PROTOTYPES -D_GNU_SOURCE -D_POSIX_C_SOURCE=199309L")

set(CMAKE_C_FLAGS "--std=c99 ${C_FLAGS_COMMON}")
set(CMAKE_C_FLAGS_DEBUG "-g3 -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS ${C_FLAGS_COMMON})
set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})

# ------------------------------------------------------------------------------
# Output Directories
# ------------------------------------------------------------------------------

# Put libraries and binaries that get built into the directories at
# top of the build tree rather than in hard-to-find leaf
# directoreis. This simplifies manual testing.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ------------------------------------------------------------------------------
# Find libraries
# ------------------------------------------------------------------------------

function(local_find_library VAR NAME)
    find_library("${VAR}" "${NAME}")

    if("${VAR}")
        message(STATUS "Library found: ${NAME}")
    else("${VAR}")
        message(STATUS "Library not found: ${NAME}")
    endif("${VAR}")
endfunction(local_find_library)

local_find_library(LOCAL_GL_LIB GL)
local_find_library(LOCAL_GLES2_LIB GLESv2)
local_find_library(LOCAL_EGL_LIB EGL)

local_find_library(LOCAL_X11_LIB X11)
local_find_library(LOCAL_X11_xcb_LIB X11-xcb)
local_find_library(LOCAL_xcb_LIB xcb)

# ------------------------------------------------------------------------------
# Add subdirectores
# ------------------------------------------------------------------------------

function(local_notify_build NAME)
    message(STATUS "Will build target: ${NAME}")
endfunction(local_notify_build)

add_subdirectory(src)

# vim: et sw=4 tw=80:
