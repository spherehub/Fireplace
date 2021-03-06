// This file defines windows specific information for fireplace.
//
// Copyright (c) 2018 SoraKatadzuma
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#ifndef FIREPLACE_WIN32_PLATFORM_HEADER
#define FIREPLACE_WIN32_PLATFORM_HEADER

// Undefine these, because we don't need them once they are defined by windows.
#undef APIENTRY
#undef CALLBACK
#undef WINGDIAPI

#define UNICODE             // We use unicode so this is important.
#define NOMINMAX            // Fixes an issue with C++ std::min and std::max
#define STRICT              // Makes sure that types are strict.
#define VC_EXTRALEAN        // Helps get rid of unimportant includes.
#define WIN32_LEAN_AND_MEAN // Has similar effect to VC_EXTRALEAN.
#include <Windows.h>

// After including Windows.h we don't need those macros anymore.
#undef UNICODE
#undef NOMINMAX
#undef STRICT
#undef VC_EXTRALEAN
#undef WIN32_LEAN_AND_MEAN

// Windows 7 version number.
#define WIN7 0x0601

// We only allow windows 7 or earlier.
#if WINVER < WIN7
#undef WINVER
#define WINVER WIN7
#endif

// We only allow windows 7 or earlier.
#if _WIN32_WINNT < WIN7
#undef _WIN32_WINNT
#define _WIN32_WINNT WIN7
#endif

// Important inclusions.
#include <cwchar>
#include <Dbt.h>
#include <dinput.h>
#include <dwmapi.h>
#include <VersionHelpers.h>
#include <xinput.h>

#ifndef FIREPLACE_WIN32CLASSNAME
#define FIREPLACE_WIN32CLASSNAME L"FIREPLACE_CLASS"
#endif

#ifndef FIREPLACE_WIN32MENUNAME
#define FIREPLACE_WIN32MENUNAME L"FIREPLACE_MENU"
#endif

#define dll_open(name)                  ::LoadLibrary(name)
#define dll_close(handle)               ::FreeLibrary(handle)
#define get_dll_symbol(handle, name)    ::GetProcAddress(handle, name)

namespace fireplace {
    // Callback for the window.
    LRESULT CALLBACK _window_procedure(HWND, UINT, WPARAM, LPARAM);

    /*
     * This structure represents the windows specific library of fireplace. It
     * contains function pointers and important windows based information.
     */
    struct _win32_library final {
        // The window class for this library.
        WNDCLASSEX wndcls;

        // Constructs a new _win32_library.
        explicit _win32_library();

        // Disallow copy construction.
        _win32_library(const _win32_library& other) = delete;

        // Disallow move construction.
        _win32_library(_win32_library&& other) = delete;

        // Deconstructs this library.
        ~_win32_library();

        // Gets the recent error produced by Windows.
        static std::wstring last_error();
    };

    // Creates a window with a name.
    void _win32_create_window(handle& _window, const wchar_t* title, frame* _frame);

    // Destroys a given window.
    void _win32_destroy_window(handle& _window);

    // Disables a given window.
    void _win32_disable(handle& _window);

    // Enables a given window.
    void _win32_enable(handle& _window);

    // Focuses a given window.
    void _win32_focus(handle& _window);

    // Gets the position of a given window.
    void _win32_get_position(handle& _window, int& pos_x, int& pos_y);

    // Gets the size of a given window.
    void _win32_get_size(handle& _window, int& width, int& height);

    // Hides the given window.
    void _win32_hide(handle& _window);

    // Checks if the given window is enabled.
    bool _win32_is_enabled(handle& _window);

    // Checks if the given window is focused.
    bool _win32_is_focused(handle& _window);

    // Checks if the given window is maximized.
    bool _win32_is_maximized(handle& _window);

    // Checks if the given window is minimized.
    bool _win32_is_minimized(handle& _window);

    // Checks if the given window is open still.
    bool _win32_is_open(handle& _window);

    // Maximizes the given window.
    void _win32_maximize(handle& _window);

    // Minimizes the given window.
    void _win32_minimize(handle& _window);

    // Polls the events of the given window.
    void _win32_poll_events(handle& _window);

    // Positions the given window at the given coordinates.
    void _win32_position_at(handle& _window, int pos_x, int pos_y);

    // Resizes the given window to the given size.
    void _win32_resize_to(handle& _window, int width, int height);

    // Sets the title of the given window.
    void _win32_set_title(handle& _window, const wchar_t* title);

    // Shows the given window.
    void _win32_show(handle& _window);

    // Gets the title of the given window.
    std::wstring _win32_title(handle& _window);

    /* TODO: Windows specific monitor code. */
	monitor* _win32_get_primary_monitor();

    // WGL specific structures and code.
#ifdef _FIREPLACE_OPENGL
    // Mostly important WGL macros.
    #define WGL_ACCELERATION_ARB                        0x2003
    #define WGL_ACCUM_BITS_ARB                          0x201D
    #define WGL_ACCUM_RED_BITS_ARB                      0x201E
    #define WGL_ACCUM_GREEN_BITS_ARB                    0x201F
    #define WGL_ACCUM_BLUE_BITS_ARB                     0x2020
    #define WGL_ACCUM_ALPHA_BITS_ARB                    0x2021
    #define WGL_ALPHA_BITS_ARB                          0x201B
    #define WGL_ALPHA_SHIFT_ARB                         0x201C
    #define WGL_AUX_BUFFERS_ARB                         0x2024
    #define WGL_BLUE_BITS_ARB                           0x2019
    #define WGL_BLUE_SHIFT_ARB                          0x201A
    #define WGL_COLOR_BITS_ARB                          0x2014
    #define WGL_COLORSPACE_EXT                          0x309D
    #define WGL_COLORSPACE_SRGB_EXT                     0x3089
    #define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB   0x0002
    #define WGL_CONTEXT_CORE_PROFILE_BIT_ARB            0x0001
    #define WGL_CONTEXT_DEBUG_BIT_ARB                   0x0001
    #define WGL_CONTEXT_ES2_PROFILE_BIT_EXT             0x0004
    #define WGL_CONTEXT_FLAGS_ARB                       0x2094
    #define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB      0x0002
    #define WGL_CONTEXT_LAYER_PLANE_ARB                 0x2093
    #define WGL_CONTEXT_MAJOR_VERSION_ARB               0x2091
    #define WGL_CONTEXT_MINOR_VERSION_ARB               0x2092
    #define WGL_CONTEXT_OPENGL_NO_ERROR_ARB             0x31B3
    #define WGL_CONTEXT_PROFILE_MASK_ARB                0x9126
    #define WGL_CONTEXT_RELEASE_BEHAVIOUR_ARB           0x2097
    #define WGL_CONTEXT_RELEASE_BEHAVIOUR_FLUSH_ARB     0x2098
    #define WGL_CONTEXT_RELEASE_BEHAVIOUR_NONE_ARB      0x0000
    #define WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
    #define WGL_CONTEXT_ROBUST_ACCESS_BIT_ARB           0x0004
    #define WGL_DEPTH_BITS_ARB                          0x2022
    #define WGL_DOUBLE_BUFFER_ARB                       0x2011
    #define WGL_DRAW_TO_BITMAP_ARB                      0x2002
    #define WGL_DRAW_TO_WINDOW_ARB                      0x2001
    #define WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB            0x20A9
    #define WGL_FULL_ACCELERATION_ARB                   0x2027
    #define WGL_GENERIC_ACCELERATION_ARB                0x2026
    #define WGL_GREEN_BITS_ARB                          0x2017
    #define WGL_GREEN_SHIFT_ARB                         0x2018
    #define WGL_LOSE_CONTEXT_ON_RESET_ARB               0x8525
    #define WGL_NEED_PALETTE_ARB                        0x2004
    #define WGL_NEED_SYSTEM_PALETTE_ARB                 0x2005
    #define WGL_NO_ACCELERATION_ARB                     0x2025
    #define WGL_NO_RESET_NOTIFICATION_ARB               0x8261
    #define WGL_NUMBER_PIXEL_FORMATS_ARB                0x2000
    #define WGL_NUMBER_OVERLAYS_ARB                     0x2008
    #define WGL_NUMBER_UNDERLAYS_ARB                    0x2009
    #define WGL_PIXEL_TYPE_ARB                          0x2013
    #define WGL_RED_BITS_ARB                            0x2015
    #define WGL_RED_SHIFT_ARB                           0x2016
    #define WGL_SAMPLES_ARB                             0x2042
    #define WGL_SHARE_DEPTH_ARB                         0x200C
    #define WGL_SHARE_STENCIL_ARB                       0x200D
    #define WGL_SHARE_ACCUM_ARB                         0x200E
    #define WGL_STENCIL_BITS_ARB                        0x2023
    #define WGL_STEREO_ARB                              0x2012
    #define WGL_SUPPORT_GDI_ARB                         0x200F
    #define WGL_SUPPORT_OPENGL_ARB                      0x2010
    #define WGL_SWAP_COPY_ARB                           0x2029
    #define WGL_SWAP_EXCHANGE_ARB                       0x2028
    #define WGL_SWAP_LAYER_BUFFERS_ARB                  0x2006
    #define WGL_SWAP_METHOD_ARB                         0x2007
    #define WGL_SWAP_UNDEFINED_ARB                      0x202A
    #define WGL_TRANSPARENT_ALPHA_VALUE_ARB             0x203A
    #define WGL_TRANSPARENT_ARB                         0x200A
    #define WGL_TRANSPARENT_BLUE_VALUE_ARB              0x2039
    #define WGL_TRANSPARENT_GREEN_VALUE_ARB             0x2038
    #define WGL_TRANSPARENT_INDEX_VALUE_ARB             0x203B
    #define WGL_TRANSPARENT_RED_VALUE_ARB               0x2037
    #define WGL_TYPE_RGBA_ARB                           0x202B
    #define WGL_TYPE_COLORINDEX_ARB                     0x202C

    // Our definition of GL types.
    typedef unsigned char   GLubyte;
    typedef unsigned char   GLuchar;
    typedef signed char     GLbyte;
    typedef signed char     GLchar;
    typedef unsigned char   GLboolean;
    typedef unsigned short  GLushort;
    typedef short           GLshort;
    typedef unsigned int    GLbitfield;
    typedef unsigned int    GLenum;
    typedef unsigned int    GLuint;
    typedef int             GLint;
    typedef int             GLsizei;
    typedef float           GLfloat;
    typedef float           GLclampf;
    typedef void            GLvoid;
    typedef int             GLintptrARB;
    typedef int             GLsizeiptrARB;
    typedef int             GLfixed;
    typedef int             GLclampx;

    // Why does windows pixel format descriptor have to have its full name when
    // nothing else does? This is literally here just for continuity at this point.
    typedef PIXELFORMATDESCRIPTOR PFD;

    // Important function pointers.
    typedef       HGLRC (WINAPI *PFNWGLCREATECONTEXT)(HDC);
    typedef       BOOL  (WINAPI *PFNWGLDELETECONTEXT)(HGLRC);
    typedef       PROC  (WINAPI *PFNWGLGETPROCADDRESS)(LPCSTR);
    typedef       HDC   (WINAPI *PFNWGLGETCURRENTDC)(void);
    typedef       HGLRC (WINAPI *PFNWGLGETCURRENTCONTEXT)(void);
    typedef       BOOL  (WINAPI *PFNWGLMAKECURRENT)(HDC, HGLRC);
    typedef       BOOL  (WINAPI *PFNWGLSHARELISTS)(HGLRC, HGLRC);
    typedef       BOOL  (WINAPI *PFNWGLSWAPINTERVALEXT)(GLint);
    typedef       HGLRC (WINAPI *PFNWGLCREATECONTEXTATTRIBSARB)(HDC, HGLRC, const GLint*);
    typedef const char* (WINAPI *PFNWGLGETEXTENSIONSSTRINGARB)(HDC);
    typedef const char* (WINAPI *PFNWGLGETEXTENSIONSSTRINGEXT)(void);
    typedef       HGLRC (WINAPI *PFNWGLGETPIXELFORMATATTRIBIVARB)(HDC, GLint, GLint, GLuint, const GLint*, GLint*);

    /*
     * This structure represents the OpenGL library for Windows, or in other
     * words WGL. It will contain library specifics, like things from
     * opengl32.dll and possibly other things.
     */
    struct _win32_wgl_library final {
        /*
         * A handle to the opengl32.dll instance that will be used to get
         * function pointers for wgl calls.
         */
        HMODULE gl_instance;

        // Tells if wgl has been initialized.
        bool initialized;

        // Necessary function pointers.
        PFNWGLCREATECONTEXT             create_context;
        PFNWGLDELETECONTEXT             delete_context;
        PFNWGLGETPROCADDRESS            get_proc_address;
        PFNWGLGETCURRENTDC              get_current_dc;
        PFNWGLGETCURRENTCONTEXT         get_current_context;
        PFNWGLMAKECURRENT               make_current;
        PFNWGLSHARELISTS                share_lists;
        PFNWGLSWAPINTERVALEXT           swap_interval_ext;
        PFNWGLCREATECONTEXTATTRIBSARB   create_context_attribs_arb;
        PFNWGLGETEXTENSIONSSTRINGARB    get_extensions_string_arb;
        PFNWGLGETEXTENSIONSSTRINGEXT    get_extensions_string_ext;
        PFNWGLGETPIXELFORMATATTRIBIVARB get_pixel_format_attribiv_arb;

        /*
         * Things needed in order to set up a context the way the user wants it
         * to be. More things may be added later.
         */
        GLboolean ARB_context_flush_control;
        GLboolean ARB_create_context;
        GLboolean ARB_create_context_robustness;
        GLboolean ARB_create_context_no_error;
        GLboolean ARB_create_context_profile;
        GLboolean ARB_multisample;
        GLboolean ARB_pixel_format;
        GLboolean EXT_create_context_es2_profile;
        GLboolean EXT_swap_control;

        // Constructs a new win32 wgl library.
        explicit _win32_wgl_library();

        // Disallow copy construction.
        _win32_wgl_library(const _win32_wgl_library& other) = delete;

        // Disallow move construction.
        _win32_wgl_library(_win32_wgl_library&& other) = delete;

        // Deconstructs this library.
        ~_win32_wgl_library();

        // Checks for an extension in the given string.
        bool extension_in_list(const char* extension, const char* list);

        // Checks if an extension is supported.
        bool extension_supported(const char* extension);
    };

    /*
     * This structure defines a configuration for WGL specifically. These are
     * used in the initialization of WGL as well as the creation of a WGL
     * context. Values are set by default to their defaults.
     */
    struct _win32_wgl_config final {
        int profile             =  any_profile;
        int debug               =  false;
        int forward_compat      =  false;
        int no_error            =  false;
        int release_behaviour   =  any_release_behaviour;
        int robustness          =  no_robustness;
        int major_version       =  1;
        int minor_version       =  1;
        int creation_api        =  native_context_api;
        int client_api          =  opengl_api;
        int stereoscopic        =  false;
        int samples             =  0;
        int auxiliary_buffers   =  0;
        int double_buffered     =  1;
        int transparent         =  false;
        int accum_alpha_bits    =  0;
        int accum_green_bits    =  0;
        int accum_blue_bits     =  0;
        int accum_red_bits      =  0;
        int stencil_bits        =  8;
        int depth_bits          = 24;
        int alpha_bits          =  8;
        int alpha_shift         =  0;
        int blue_bits           =  8;
        int blue_shift          =  0;
        int green_bits          =  8;
        int green_shift         =  0;
        int red_bits            =  8;
        int red_shift           =  0;
        int handle              =  0;

        // Constructs a new win32 wgl configuration.
        explicit _win32_wgl_config() = default;

        // Copy constructor.
        _win32_wgl_config(const _win32_wgl_config& other);

        // Move constructor.
        _win32_wgl_config(_win32_wgl_config&& other);

        // Deconstructs this win32 wgl config, is default deconstructor.
        ~_win32_wgl_config() = default;

        // Copy-swap idiom assignment operator.
        _win32_wgl_config& operator=(_win32_wgl_config other);
    };

    // Gets the specified attribute of the specified format.
    int get_pixel_format_attrib(HDC device, int format, int attrib);

    // Chooses a pixel format that best represents what the user wants.
    int choose_pixel_format(HDC device, _win32_wgl_config expected);

    /*
     * This structure represents an OpenGL context for Windows. More
     * Specifically, a WGL context that can be used to later to load modern
     * OpenGL function pointers by a loading library like GLEW or GLAD.
     */
    struct _win32_wgl_context final {
        /*
         * A handle to the device context of the window that this context
         * renders to.
         */
        HDC hdc;

        /*
         * A handle to the rendering context itself. This is a OpenGL specific
         * rendering context that Window's allows us to use for legacy reasons.
         */
        HGLRC hrc;

        // Constructs a new _win32_wgl_context.
        explicit _win32_wgl_context(handle& _window);

        // Disallow copy construction, this is temporary.
        _win32_wgl_context(const _win32_wgl_context& other) = delete;

        // Disallow move construction, this is temporary.
        _win32_wgl_context(_win32_wgl_context&& other) = delete;

        // Deconstructs this context.
        ~_win32_wgl_context();

        // Makes this context current.
        void make_current();

        // Swaps the buffers of this context.
        void swap_buffers();
    };

#elif defined(_FIREPLACE_DIRECTX)

#endif
}

#endif
