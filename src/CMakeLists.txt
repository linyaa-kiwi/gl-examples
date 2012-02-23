if(LOCAL_X11_LIB
   AND LOCAL_X11_xcb_LIB
   AND LOCAL_EGL_LIB)

    add_subdirectory(x11-egl)

endif(LOCAL_X11_LIB
     AND LOCAL_X11_xcb_LIB
     AND LOCAL_EGL_LIB)

if(APPLE AND UNIX)
    add_subdirectory(cocoa)
endif(APPLE AND UNIX)

