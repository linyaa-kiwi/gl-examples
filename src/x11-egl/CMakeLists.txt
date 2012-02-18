link_libraries(
    stdc++
    X11
    X11-xcb
    xcb
    EGL
    )

add_executable(create-x-egl-gl-surface create-x-egl-gl-surface.cpp)
add_executable(create-x-egl-gles2-surface create-x-egl-gles2-surface.cpp)
