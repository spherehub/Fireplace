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
#define FIREPLACE_MINOR 0
#define FIREPLACE_PATCH 29

// Known Fireplace errors.
#define FAILED_INITIALIZATION   0x01001200
#define FAILED_TERMINATION      0x01001201
#define WINDOW_ERROR            0x01001202

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
#define context_profile             0x1001
#define context_debug               0x1002
#define context_forward_compatible  0x1003
#define context_no_error            0x1004
#define context_release_behaviour   0x1005
#define context_robustness          0x1006
#define context_major_version       0x1007
#define context_minor_version       0x1008
#define context_creation_api        0x1009
#define context_client_api          0x100A
#define stereoscopic                0x100B
#define multisample                 0x100C
#define auxiliary_buffers           0x100D
#define accumulation_alpha_bits     0x100E
#define accumulation_green_bits     0x100F
#define accumulation_blue_bits      0x1010
#define accumulation_red_bits       0x1011
#define stencil_bits                0x1012
#define depth_bits                  0x1013
#define alpha_bits                  0x1014
#define blue_bits                   0x1015
#define green_bits                  0x1016
#define red_bits                    0x1017

// OpenGL Attribute values constants.
#define no_api                      0x1100
#define opengl_api                  0x1101
#define opengl_es_api               0x1102
#define any_profile                 0x1103
#define core_profile                0x1104
#define compatibility_profile       0x1105
#define no_robustness               0x1106
#define no_reset_notification       0x1107
#define lose_context_on_reset       0x1108
#define any_release_behaviour       0x1109
#define release_behaviour_flush     0x110A
#define release_behaviour_none      0x110B
#define native_context_api          0x110C
#define egl_context_api             0x110D // Future support for egl.
#define osmesa_context_api          0x110E // Future support for osmesa.
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

        // Tells whether or not this window is open.
        bool m_open;

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
        void disable() const;

        // Enables this window.
        void enable() const;

        // Focuses this window.
        void focus() const;

        // Gets the position of this window.
        void get_position(int& pos_x, int& pos_y) const;

        // Gets the size of this window.
        void get_size(int& width, int& height) const;

        // Returns the handle to this window.
        const void* handle() const;

        // Hides this window.
        void hide() const;

        // Checks if this window is enabled.
        bool is_enabled() const;

        // Checks if this window is focused.
        bool is_focused() const;

        // Checks if this window is maximized.
        bool is_maximized() const;

        // Checks if this window is minimized.
        bool is_minimized() const;

        // Returns whether or not this window is open.
        bool is_open() const;

        // Makes this window the current window to be rendered to.
        void make_current() const;

        // Maximizes this window.
        void maximize() const;

        // Minimizes this window.
        void minimize() const;

        // Polls the events of this window.
        void poll_events() const;

        // Repositions this window.
        void position_at(int pos_x, int pos_y);

        // Resizes this window.
        void resize_to(int width, int height);

        // Sets the title of this window.
        void set_title(std::wstring title);

        // Shows this window.
        void show() const;

        // Swaps this window's frame buffers.
        void swap_buffers() const;

        // Gets the title of this window.
        std::wstring title() const;
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
