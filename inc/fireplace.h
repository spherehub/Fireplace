// This header contains important constructs of the fireplace api, including
// other important files.
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
#ifndef _FIREPLACE_HEADER
#define _FIREPLACE_HEADER

#if !defined(_WIN32) && (defined(__WIN32__) || defined(WIN32) || defined(__MINGW32__))
#define _WIN32
#endif // _WIN32

#ifdef _WIN32
// These defines are important to specific windows things.
#ifndef APIENTRY
#define APIENTRY __stdcall
#endif // APIENTRY
#ifndef CALLBACK
#define CALLBACK __stdcall
#endif // CALLBACK
#ifndef WINGDIAPI
#define WINGDIAPI __declspec(dllimport)
#endif // WINGDIAPI
#endif // _WIN32

// Including string because our headers needs it.
#include <string>

// Versioning.
#define FIREPLACE_MAJOR 0
#define FIREPLACE_MINOR 1
#define FIREPLACE_PATCH 1

// Context rendering apis.
#ifdef _FIREPLACE_OPENGL
// OpenGL and OpenGL ES headers.
#ifdef _FIREPLACE_INCLUDE_ES1
#include <GLES/gl.h>
#ifdef _FIREPLACE_INCLUDE_GLEXT
#include <GLES/glext.h>
#endif // _FIREPLACE_INCLUDE_GLEXT
#elif defined(_FIREPLACE_INCLUDE_ES2)
#include <GLES2/gl2.h>
#ifdef _FIREPLACE_INCLUDE_GLEXT
#include <GLES2/gl2ext.h>
#endif // _FIREPLACE_INCLUDE_GLEXT
#elif defined(_FIREPLACE_INCLUDE_ES3)
#include <GLES3/gl3.h>
#ifdef _FIREPLACE_INCLUDE_GLEXT
#include <GLES2/gl2ext.h>
#endif // _FIREPLACE_INCLUDE_GLEXT
#elif _FIREPLACE_INCLUDE_ES31
#include <GLES3/gl31.h>
#ifdef _FIREPLACE_INCLUDE_GLEXT
#include <GLES2/gl2ext.h>
#endif // _FIREPLACE_INCLUDE_GLEXT
#elif _FIREPLACE_INCLUDE_ES32
#include <GLES3/gl32.h>
#ifdef _FIREPLACE_INCLUDE_GLEXT
#include <GLES2/gl2ext.h>
#endif // _FIREPLACE_INCLUDE_GLEXT
#elif _FIREPLACE_INCLUDE_GLCOREARB
#include <GL/glcorearb.h>
#endif // _FIREPLACE_INCLUDE_ES
#define opengl                      0x1000

// OpenGL Attribute constants.
constexpr unsigned int context_profile              = 0x1001;
constexpr unsigned int context_debug                = 0x1002;
constexpr unsigned int context_forward_compatible   = 0x1003;
constexpr unsigned int context_no_error             = 0x1004;
constexpr unsigned int context_release_behaviour    = 0x1005;
constexpr unsigned int context_robustness           = 0x1006;
constexpr unsigned int context_major_version        = 0x1007;
constexpr unsigned int context_minor_version        = 0x1008;
constexpr unsigned int context_creation_api         = 0x1009;
constexpr unsigned int context_client_api           = 0x100A;
constexpr unsigned int stereoscopic                 = 0x100B;
constexpr unsigned int samples                      = 0x100C;
constexpr unsigned int auxiliary_buffers            = 0x100D;
constexpr unsigned int double_buffered              = 0x100E;
constexpr unsigned int transparent                  = 0x100F;
constexpr unsigned int accum_alpha_bits             = 0x1010;
constexpr unsigned int accum_green_bits             = 0x1011;
constexpr unsigned int accum_blue_bits              = 0x1013;
constexpr unsigned int accum_red_bits               = 0x1014;
constexpr unsigned int stencil_bits                 = 0x1015;
constexpr unsigned int depth_bits                   = 0x1016;
constexpr unsigned int alpha_bits                   = 0x1017;
constexpr unsigned int alpha_shift                  = 0x1018;
constexpr unsigned int blue_bits                    = 0x1019;
constexpr unsigned int blue_shift                   = 0x101A;
constexpr unsigned int green_bits                   = 0x101B;
constexpr unsigned int green_shift                  = 0x101C;
constexpr unsigned int red_bits                     = 0x101D;
constexpr unsigned int red_shift                    = 0x101E;

// OpenGL Attribute values constants.
constexpr unsigned int no_api                       = 0x1100;
constexpr unsigned int opengl_api                   = 0x1101;
constexpr unsigned int opengl_es_api                = 0x1102;
constexpr unsigned int any_profile                  = 0x0000;
constexpr unsigned int core_profile                 = 0x1104;
constexpr unsigned int compatibility_profile        = 0x1105;
constexpr unsigned int no_robustness                = 0x1106;
constexpr unsigned int no_reset_notification        = 0x1107;
constexpr unsigned int lose_context_on_reset        = 0x1108;
constexpr unsigned int any_release_behaviour        = 0x0000;
constexpr unsigned int release_behaviour_flush      = 0x110A;
constexpr unsigned int release_behaviour_none       = 0x110B;
constexpr unsigned int native_context_api           = 0x110C;
constexpr unsigned int egl_context_api              = 0x110D; // Future support for egl.
constexpr unsigned int osmesa_context_api           = 0x110E; // Future support for osmesa.
#endif

namespace fireplace {
    // Aligning with Windows based handle types.
    typedef void* handle;

    /*
     * A structure representing a single manipulatable window on a given desktop
     * environment.
     */
    class frame final {
        // Handle to the underlying window.
        handle m_handle;

        // Handle to the underlying context of this window.
        handle m_context;

        // Swaps the contents of two frames.
        void swap(frame& other);

    public:
        // Constructs a default window.
        explicit frame();

        // Constructs a new window with the given unicode title.
        explicit frame(std::wstring title);

        // Copy constructor.
        frame(const frame& other);

        // Move constructor.
        frame(frame&& other);

        // Deconstructs this window.
        ~frame();

        // Copy-swap idiom operator.
        frame& operator=(frame other);

        // Closes this window. This releases some memory so it is non-const.
        void close();

        // Disables this window.
        void disable();

        // Enables this window.
        void enable();

        // Focuses this window.
        void focus();

        // Gets the position of this window.
        void get_position(int& pos_x, int& pos_y);

        // Gets the size of this window.
        void get_size(int& width, int& height);

        // Returns the handle to this window.
        const void* handle();

        // Hides this window.
        void hide();

        // Checks if this window is enabled.
        bool is_enabled();

        // Checks if this window is focused.
        bool is_focused();

        // Checks if this window is maximized.
        bool is_maximized();

        // Checks if this window is minimized.
        bool is_minimized();

        // Returns whether or not this window is open.
        bool is_open();

        // Makes this window the current window to be rendered to.
        void make_current();

        // Maximizes this window.
        void maximize();

        // Minimizes this window.
        void minimize();

        // Polls the events of this window.
        void poll_events();

        // Repositions this window.
        void position_at(int pos_x, int pos_y);

        // Resizes this window.
        void resize_to(int width, int height);

        // Sets the title of this window.
        void set_title(std::wstring title);

        // Shows this window.
        void show();

        // Swaps this window's frame buffers.
        void swap_buffers();

        // Gets the title of this window.
        std::wstring title();
    };

    // Prints all errors to the console.
    void dump_errors();

    // Prints all of the info log to the console.
    void dump_info_log();

    // Gets a user pointer by it's mapped name.
    handle get_user_pointer(std::string pointer_name);

    // Sets a user pointer.
    void set_user_pointer(std::string pointer_name, handle _handle);
}

#endif
