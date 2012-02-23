link_libraries(
    ${OPENGL_gl_LIBRARY}
    ${COCOA_FRAMEWORK}
    ${IOKIT_FRAMEWORK}
    ${CORE_FOUNDATION_FRAMEWORK}
    )

include_directories(.)

add_subdirectory(common)
add_subdirectory(create-cocoa-custom-nsopenglview-with-nsopenglcontext)
add_subdirectory(create-cocoa-custom-nsopenglview-with-cglcontext)
