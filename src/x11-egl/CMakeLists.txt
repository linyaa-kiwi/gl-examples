link_libraries(
    stdc++
    ${LOCAL_X11_LIB}
    ${LOCAL_X11_xcb_LIB}
    ${LOCAL_xcb_LIB}
    ${LOCAL_EGL_LIB}
    )

if(LOCAL_GL_LIB)
    local_notify_build("create-x-egl-gl-surface")
    add_executable(create-x-egl-gl-surface create-x-egl-gl-surface.cpp)
    target_link_libraries(create-x-egl-gl-surface ${LOCAL_GL_LIB})
endif(LOCAL_GL_LIB)

if(LOCAL_GLES2_LIB)
    local_notify_build("create-x-egl-gles2-surface")
    add_executable(create-x-egl-gles2-surface create-x-egl-gles2-surface.cpp)
    target_link_libraries(create-x-egl-gles2-surface ${LOCAL_GLES2_LIB})
endif(LOCAL_GLES2_LIB)
