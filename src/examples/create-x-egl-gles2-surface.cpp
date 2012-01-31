#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>

#include <EGL/egl.h>
#include <xcb/xcb.h>
#include <X11/Xlib-xcb.h>

using namespace std;

void
error_fatal(const char* format, ...) {
    printf("error: ");

    va_list va;
    va_start(va, format);
    vprintf(format, va);
    va_end(va);

    printf("\n");
    exit(1);
}

const uint32_t xcb_window_attrib_mask = XCB_CW_EVENT_MASK;
const uint32_t xcb_window_attrib_list[] = {
    XCB_EVENT_MASK_BUTTON_PRESS,
    XCB_EVENT_MASK_EXPOSURE,
    XCB_EVENT_MASK_KEY_PRESS,
};

void
setup_x(const char *display_name,
        int window_x,
        int window_y,
        int window_width,
        int window_height,
        Display** out_display,
        xcb_connection_t** out_connection,
        int* out_screen,
        xcb_window_t* out_window) {

    xcb_generic_error_t* error;

    Display* display = XOpenDisplay(display_name);
    if (!display)
        error_fatal("XOpenDisplay() failed");

    xcb_connection_t *connection = XGetXCBConnection(display);
    if (!connection)
        error_fatal("XGetXCBConnection() failed");
    if (xcb_connection_has_error(connection))
        error_fatal("errors occured in connecting to X server");

    const xcb_setup_t* setup = xcb_get_setup(connection);
    xcb_screen_t* screen = xcb_setup_roots_iterator(setup).data;
    assert(screen != 0);

    xcb_window_t window = xcb_generate_id(connection);
    if (window <= 0)
        error_fatal("failed to generate X window id");

    xcb_void_cookie_t create_cookie = xcb_create_window_checked(
        connection,
        XCB_COPY_FROM_PARENT, // depth
        window,
        screen->root, // parent window
        window_x,
        window_y,
        window_width,
        window_height,
        0, // border width
        XCB_WINDOW_CLASS_INPUT_OUTPUT, // class
        screen->root_visual, // visual
        xcb_window_attrib_mask,
        xcb_window_attrib_list);

    xcb_void_cookie_t map_cookie = xcb_map_window_checked(connection, window);

    // Check errors.
    error = xcb_request_check(connection, create_cookie);
    if (error)
        error_fatal("failed to create X window: %d", error->error_code);
    error = xcb_request_check(connection, map_cookie);
    if (error)
        error_fatal("failed to map X window: %d", error->error_code);

    *out_display = display;
    *out_connection = connection;
    *out_window = window;
}

const EGLint egl_config_attribs[] = {
    EGL_COLOR_BUFFER_TYPE,     EGL_RGB_BUFFER,
    EGL_BUFFER_SIZE,           32,
    EGL_RED_SIZE,              8,
    EGL_GREEN_SIZE,            8,
    EGL_BLUE_SIZE,             8,
    EGL_ALPHA_SIZE,            8,

    EGL_DEPTH_SIZE,            24,
    EGL_STENCIL_SIZE,          8,

    EGL_SAMPLE_BUFFERS,        0,
    EGL_SAMPLES,               0,

    EGL_SURFACE_TYPE,          EGL_WINDOW_BIT,
    EGL_RENDERABLE_TYPE,       EGL_OPENGL_ES2_BIT,

    EGL_NONE,
};

const EGLint egl_context_attribs[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE,
};

const EGLint egl_surface_attribs[] = {
    EGL_RENDER_BUFFER, EGL_BACK_BUFFER,
    EGL_NONE,
};

void
setup_egl(
        EGLint api,
        EGLNativeDisplayType native_display,
        EGLNativeWindowType native_window,
        EGLDisplay* out_display,
        EGLConfig* out_config,
        EGLContext* out_context,
        EGLSurface* out_window_surface) {

    EGLint ignore;
    EGLBoolean ok;

    ok = eglBindAPI(api);
    if (!ok)
        error_fatal("eglBindAPI(0x%x) failed", api);

    EGLDisplay display = eglGetDisplay(native_display);
    if (display == EGL_NO_DISPLAY)
        error_fatal("eglGetDisplay() failed");

    ok = eglInitialize(display, &ignore, &ignore);
    if (!ok)
        error_fatal("eglInitialize() failed");

    EGLint configs_size = 256;
    EGLConfig* configs = new EGLConfig[configs_size];
    EGLint num_configs;
    ok = eglChooseConfig(
        display,
        egl_config_attribs,
        configs,
        configs_size, // num requested configs
        &num_configs); // num returned configs
    if (!ok)
        error_fatal("eglChooseConfig() failed");
    if (num_configs == 0)
        error_fatal("failed to find suitable EGLConfig");
    EGLConfig config = configs[0];
    delete [] configs;

    EGLContext context = eglCreateContext(
        display,
        config,
        EGL_NO_CONTEXT,
        egl_context_attribs);
    if (!context)
        error_fatal("eglCreateContext() failed");

    EGLSurface surface = eglCreateWindowSurface(
        display,
        config,
        native_window,
        egl_surface_attribs);
    if (!surface)
        error_fatal("eglCreateWindowSurface() failed");

    ok = eglMakeCurrent(display, surface, surface, context);
    if (!ok)
    error_fatal("eglMakeCurrent() failed");

    // Check if surface is double buffered.
    EGLint render_buffer;
    ok = eglQueryContext(
        display,
        context,
        EGL_RENDER_BUFFER,
        &render_buffer);
    if (!ok)
        error_fatal("eglQueyContext(EGL_RENDER_BUFFER) failed");
    if (render_buffer == EGL_SINGLE_BUFFER)
        printf("warn: EGL surface is single buffered\n");

    *out_display = display;
    *out_config = config;
    *out_context = context;
    *out_window_surface = surface;
}

int
main() {
    const char *x_display_name = NULL;
    Display *x_display;
    xcb_connection_t* x_connection;
    int x_screen;
    xcb_window_t x_window;
    setup_x(x_display_name,
            0, 0, // x, y
            64, 64, // width, height
            &x_display,
            &x_connection,
            &x_screen,
            &x_window);

    EGLDisplay egl_display;
    EGLConfig egl_config;
    EGLContext egl_context;
    EGLSurface egl_surface;
    setup_egl(EGL_OPENGL_ES_API,
              x_display,
              x_window,
              &egl_display,
              &egl_config,
              &egl_context,
              &egl_surface);

    return 0;
}


