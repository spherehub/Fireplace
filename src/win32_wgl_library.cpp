// This file contains all the definitions for the win32 wgl library.
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
#include "fireplace_internal.h"
#if defined(_WIN32) && defined(_FIREPLACE_OPENGL)

// Constructs a new win32 wgl library.
fireplace::_win32_wgl_library::_win32_wgl_library() {
    // create helper window.
    WNDCLASSEX tempcls = { 0 };
    tempcls.cbSize          = sizeof(WNDCLASSEX);
    tempcls.hInstance       = ::GetModuleHandle(NULL);
    tempcls.lpszClassName   = L"_fireplace_temp";
    tempcls.lpfnWndProc     = ::DefWindowProc;
    tempcls.style           = CS_HREDRAW | CS_OWNDC | CS_VREDRAW;

    // Make sure class was registered.
    if (!::RegisterClassEx(&tempcls)) {
        _firelib.lib_errors.push(fireplace::_error(
            fireplace::_error(nullptr, _win32_library::last_error()),
            L"Failure to register temporary class for WGL."
        ));
        return;
    }

    // Create temp window.
    HWND temp = ::CreateWindowEx(
        WS_EX_APPWINDOW,
        tempcls.lpszClassName,
        L"temp",
        WS_POPUP,
        0,
        0,
        640,
        480,
        NULL,
        NULL,
        tempcls.hInstance,
        NULL
    );

    if (!temp) {
        _firelib.lib_errors.push(fireplace::_error(
            fireplace::_error(nullptr, _win32_library::last_error()),
            L"Failure to create temporary window for WGL."
        ));
        return;
    }

    // Our temporaries.
    HDC dc;
    HGLRC rc;
    PFD pfd = { 0 };

    // Check that we have an instance for opengl32.dll.
    if (!gl_instance)
        gl_instance = dll_open(L"opengl32.dll");

    // Get function pointers.
    create_context      = (PFNWGLCREATECONTEXT)     get_dll_symbol(gl_instance, "wglCreateContext");
    delete_context      = (PFNWGLDELETECONTEXT)     get_dll_symbol(gl_instance, "wglDeleteContext");
    get_proc_address    = (PFNWGLGETPROCADDRESS)    get_dll_symbol(gl_instance, "wglGetProcAddress");
    get_current_dc      = (PFNWGLGETCURRENTDC)      get_dll_symbol(gl_instance, "wglGetCurrentDC");
    get_current_context = (PFNWGLGETCURRENTCONTEXT) get_dll_symbol(gl_instance, "wglGetCurrentContext");
    make_current        = (PFNWGLMAKECURRENT)       get_dll_symbol(gl_instance, "wglMakeCurrent");
    share_lists         = (PFNWGLSHARELISTS)        get_dll_symbol(gl_instance, "wglShareLists");

    // Check that we did aquire necessary function pointers.
    if (
        !create_context     ||
        !delete_context     ||
        !get_proc_address   ||
        !get_current_dc     ||
        !get_current_context||
        !make_current       ||
        !share_lists
    ) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            L"Failed to load function pointers for wgl."
        ));
        return;
    }

    // Attempt to aquire DC.
    if (!(dc = ::GetDC(temp))) {
        _firelib.lib_errors.push(fireplace::_error(
            fireplace::_error(nullptr, _win32_library::last_error()),
            L"Failed to get temp window device context."
        ));
        return;
    }

    // Set pfd values.
    pfd.cAlphaBits      = 8;
    pfd.cAuxBuffers     = 4;
    pfd.cBlueBits       = 8;
    pfd.cColorBits      = 32;
    pfd.cDepthBits      = 24;
    pfd.cGreenBits      = 8;
    pfd.cRedBits        = 8;
    pfd.cStencilBits    = 8;
    pfd.dwFlags         = PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | PFD_SUPPORT_COMPOSITION | PFD_SUPPORT_OPENGL;
    pfd.iLayerType      = PFD_MAIN_PLANE;
    pfd.iPixelType      = PFD_TYPE_RGBA;
    pfd.nSize           = sizeof(PFD);
    pfd.nVersion        = 1;

    // Have windows choose a pixel format.
    int format = ::ChoosePixelFormat(dc, &pfd);

    // Attempt to set pixel format descriptor.
    if (!::SetPixelFormat(dc, format, &pfd)) {
        _firelib.lib_errors.push(fireplace::_error(
            fireplace::_error(nullptr, _win32_library::last_error()),
            L"Failed to set pixel format for WGL initialization."
        ));
        return;
    }

    // Attempt to create wgl dummy context.
    if (!(rc = create_context(dc))) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            L"Failed to create dummy context for WGL."
        ));
        return;
    }

    // Attempt to make that context current.
    if (!make_current(dc, rc)) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            L"Failed to create dummy context for WGL."
        ));
        return;
    }

    // Get extensions.
    create_context_attribs_arb      = (PFNWGLCREATECONTEXTATTRIBSARB)   get_proc_address("wglCreateContextAttribsARB");
    get_extensions_string_arb       = (PFNWGLGETEXTENSIONSSTRINGARB)    get_proc_address("wglGetExtensionsStringARB");
    get_extensions_string_ext       = (PFNWGLGETEXTENSIONSSTRINGEXT)    get_proc_address("wglGetExtensionsStringEXT");
    get_pixel_format_attribiv_arb   = (PFNWGLGETPIXELFORMATATTRIBIVARB) get_proc_address("wglGetPixelFormatAttribivARB");
    swap_interval_ext               = (PFNWGLSWAPINTERVALEXT)           get_proc_address("wglSwapIntervalEXT");

    // Check for other extensions.
    ARB_context_flush_control       = extension_supported("WGL_ARB_context_flush_control");
    ARB_create_context              = extension_supported("WGL_ARB_create_context");
    ARB_create_context_no_error     = extension_supported("WGL_ARB_create_context_no_error");
    ARB_create_context_profile      = extension_supported("WGL_ARB_create_context_profile");
    ARB_create_context_robustness   = extension_supported("WGL_ARB_create_context_robustness");
    ARB_multisample                 = extension_supported("WGL_ARB_multisample");
    ARB_pixel_format                = extension_supported("WGL_ARB_pixel_format");
    EXT_swap_control                = extension_supported("WGL_EXT_swap_control");
    EXT_create_context_es2_profile  = extension_supported("WGL_EXT_create_context_es2_profile");

    // Clean up.
    make_current(dc, NULL);
    delete_context(rc);
    ::DestroyWindow(temp);
    ::UnregisterClass(tempcls.lpszClassName, tempcls.hInstance);

    // At the end, set initialized to true.
    initialized = true;
}

// Deconstructs this library.
fireplace::_win32_wgl_library::~_win32_wgl_library() {
    if (gl_instance)
        dll_close(gl_instance);
}

#endif
