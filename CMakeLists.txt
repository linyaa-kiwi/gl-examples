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

add_subdirectory(src)

# vim: et sw=4 tw=80:
