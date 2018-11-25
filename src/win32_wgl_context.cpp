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

#define ASHWND(_handle) \
    ((HWND)_handle)

// Gets the specified attribute of the specified format.
int fireplace::get_pixel_format_attrib(HDC device, int format, int attrib) {
    int value = 0;

    if (!_firelib.wgl.ARB_pixel_format)
        return 0;

    if (!_firelib.wgl.get_pixel_format_attribiv_arb(
        device,
        format,
        0,
        1,
        &attrib,
        &value
    )) return 0;

    return value;
}

// Chooses a pixel format that best represents what the user wants.
int fireplace::choose_pixel_format(
    HDC device,
    fireplace::_win32_wgl_config expected
) {
    int pixel_format = 0;
    int native_count = 0;
    int usable_count = 0;

    // Get the number of possible pixel formats that we could get.
    if (_firelib.wgl.ARB_pixel_format) {
        native_count = get_pixel_format_attrib(
            device,
            1,
            WGL_NUMBER_PIXEL_FORMATS_ARB
        );
    } else {
        native_count = ::DescribePixelFormat(device, 1, sizeof(PFD), NULL);
    }

    // An array of the usable configs that we could possibly get.
    _win32_wgl_config* usable_configs = new _win32_wgl_config[native_count];

    // Loop through, getting all usable configurations, if possible.
    for (int i = 0; i < native_count; i++) {
        const int n = i + 1;
        _win32_wgl_config* _current = usable_configs + usable_count;

        if (_firelib.wgl.ARB_pixel_format) {
            if (
                !get_pixel_format_attrib(device, n, WGL_SUPPORT_OPENGL_ARB) ||
                !get_pixel_format_attrib(device, n, WGL_DRAW_TO_WINDOW_ARB)
            ) continue;

            if (
                get_pixel_format_attrib(device, n, WGL_PIXEL_TYPE_ARB) !=
                    WGL_TYPE_RGBA_ARB
            ) continue;

            if (
                get_pixel_format_attrib(device, n, WGL_ACCELERATION_ARB) ==
                    WGL_NO_ACCELERATION_ARB
            ) continue;

            _current->red_bits          = get_pixel_format_attrib(device, n, WGL_RED_BITS_ARB);
            _current->green_bits        = get_pixel_format_attrib(device, n, WGL_GREEN_BITS_ARB);
            _current->blue_bits         = get_pixel_format_attrib(device, n, WGL_BLUE_BITS_ARB);
            _current->alpha_bits        = get_pixel_format_attrib(device, n, WGL_ALPHA_BITS_ARB);
            _current->depth_bits        = get_pixel_format_attrib(device, n, WGL_DEPTH_BITS_ARB);
            _current->stencil_bits      = get_pixel_format_attrib(device, n, WGL_STENCIL_BITS_ARB);
            _current->accum_red_bits    = get_pixel_format_attrib(device, n, WGL_ACCUM_RED_BITS_ARB);
            _current->accum_green_bits  = get_pixel_format_attrib(device, n, WGL_ACCUM_GREEN_BITS_ARB);
            _current->accum_blue_bits   = get_pixel_format_attrib(device, n, WGL_ACCUM_BLUE_BITS_ARB);
            _current->accum_alpha_bits  = get_pixel_format_attrib(device, n, WGL_ACCUM_ALPHA_BITS_ARB);
            _current->auxiliary_buffers = get_pixel_format_attrib(device, n, WGL_AUX_BUFFERS_ARB);

            if (get_pixel_format_attrib(device, n, WGL_STEREO_ARB))
                _current->stereoscopic = true;

            if (get_pixel_format_attrib(device, n, WGL_DOUBLE_BUFFER_ARB))
                _current->double_buffered = true;

            if (_firelib.wgl.ARB_multisample)
                _current->samples = get_pixel_format_attrib(device, n, WGL_SAMPLES_ARB);
        } else {
            PFD pfd;

            if (!::DescribePixelFormat(device, n, sizeof(PFD), &pfd)) continue;

            if (
                !(pfd.dwFlags & PFD_DRAW_TO_WINDOW) ||
                !(pfd.dwFlags & PFD_SUPPORT_OPENGL)
            ) continue;

            if (
                !(pfd.dwFlags & PFD_GENERIC_ACCELERATED) &&
                 (pfd.dwFlags & PFD_GENERIC_FORMAT)
            ) continue;

            if (pfd.iPixelType != PFD_TYPE_RGBA)
                continue;

            _current->red_bits          = pfd.cRedBits;
            _current->green_bits        = pfd.cGreenBits;
            _current->blue_bits         = pfd.cBlueBits;
            _current->alpha_bits        = pfd.cAlphaBits;
            _current->depth_bits        = pfd.cDepthBits;
            _current->stencil_bits      = pfd.cStencilBits;
            _current->accum_red_bits    = pfd.cAccumRedBits;
            _current->accum_green_bits  = pfd.cAccumGreenBits;
            _current->accum_blue_bits   = pfd.cAccumBlueBits;
            _current->accum_alpha_bits  = pfd.cAccumAlphaBits;
            _current->auxiliary_buffers = pfd.cAuxBuffers;

            if (pfd.dwFlags & PFD_STEREO)
                _current->stereoscopic = true;

            if (pfd.dwFlags& PFD_DOUBLEBUFFER)
                _current->double_buffered = true;
        }

        _current->handle = n;
        usable_count++;
    }

    // Check that there are usable configs.
    if (!usable_count) {
        _firelib.lib_errors.push(fireplace::_error(
            L"No suitable match for your requested frame buffer configuration."
        ));
        delete[] usable_configs;
        return 0;
    }

    unsigned int missing            = 0;
    unsigned int color_diff         = 0;
    unsigned int extra_diff         = 0;
    unsigned int least_missing      = UINT_MAX;
    unsigned int least_color_diff   = UINT_MAX;
    unsigned int least_extra_diff   = UINT_MAX;
    const _win32_wgl_config* _final;
    const _win32_wgl_config* closest;

    // Find closest match.
    for (int i = 0; i < usable_count; i++) {
        _final = usable_configs + i;

        // They must both either be double_buffered or not.
        if (expected.double_buffered != _final->double_buffered) continue;

        missing = 0;
        if (expected.alpha_bits     > 0 && _final->alpha_bits   == 0) missing++;
        if (expected.depth_bits     > 0 && _final->depth_bits   == 0) missing++;
        if (expected.stencil_bits   > 0 && _final->stencil_bits == 0) missing++;
        if (
            expected.auxiliary_buffers > 0 &&
            (_final->auxiliary_buffers < expected.auxiliary_buffers)
        ) missing += expected.auxiliary_buffers - _final->auxiliary_buffers;

        if (expected.samples > 0 && _final->samples == 0)   missing++;
        if (expected.stereoscopic != _final->stereoscopic)  missing++;
        if (expected.transparent != _final->transparent)   missing++;

        color_diff = 0;
        if (expected.red_bits != -1) {
            color_diff = (
                (expected.red_bits - _final->red_bits) *
                (expected.red_bits - _final->red_bits)
            );
        }

        if (expected.green_bits != -1) {
            color_diff = (
                (expected.green_bits - _final->green_bits) *
                (expected.green_bits - _final->green_bits)
            );
        }

        if (expected.blue_bits != -1) {
            color_diff = (
                (expected.blue_bits - _final->blue_bits) *
                (expected.blue_bits - _final->blue_bits)
            );
        }

        extra_diff = 0;
        if (expected.alpha_bits != -1) {
            color_diff = (
                (expected.alpha_bits - _final->alpha_bits) *
                (expected.alpha_bits - _final->alpha_bits)
            );
        }

        if (expected.depth_bits != -1) {
            color_diff = (
                (expected.depth_bits - _final->depth_bits) *
                (expected.depth_bits - _final->depth_bits)
            );
        }

        if (expected.stencil_bits != -1) {
            color_diff = (
                (expected.stencil_bits - _final->stencil_bits) *
                (expected.stencil_bits - _final->stencil_bits)
            );
        }

        if (expected.accum_red_bits != -1) {
            color_diff = (
                (expected.accum_red_bits - _final->accum_red_bits) *
                (expected.accum_red_bits - _final->accum_red_bits)
            );
        }

        if (expected.accum_green_bits != -1) {
            color_diff = (
                (expected.accum_green_bits - _final->accum_green_bits) *
                (expected.accum_green_bits - _final->accum_green_bits)
            );
        }

        if (expected.accum_blue_bits != -1) {
            color_diff = (
                (expected.accum_blue_bits - _final->accum_blue_bits) *
                (expected.accum_blue_bits - _final->accum_blue_bits)
            );
        }

        if (expected.samples != -1) {
            color_diff = (
                (expected.samples - _final->samples) *
                (expected.samples - _final->samples)
            );
        }

        if (missing < least_missing) closest = _final;
        if (missing == least_missing) {
            if (
                (color_diff < least_color_diff) ||
                (color_diff == least_color_diff &&
                 extra_diff < least_extra_diff)
            ) closest = _final;
        }

        if (_final == closest) {
            least_missing       = missing;
            least_color_diff    = color_diff;
            least_extra_diff    = extra_diff;
        }
    }

    // Confirm closest match of some kind.
    if (!closest) {
        _firelib.lib_errors.push(fireplace::_error(
            L"Failed to find closest match to requested frame buffer config."
        ));
        delete[] usable_configs;
        return 0;
    }

    pixel_format = closest->handle;
    delete[] usable_configs;
    return pixel_format;
}

// Constructs a new win32 wgl context.
fireplace::_win32_wgl_context::_win32_wgl_context(fireplace::handle& _window) {
    if (!(hdc = ::GetDC(ASHWND(_window)))) {
        _firelib.lib_errors.push(fireplace::_error(
            new fireplace::_error(_win32_library::last_error()),
            L"Failed to get window device context."
        ));
        return;
    }

    int format = choose_pixel_format(hdc, config);

    // Confirm format
    if (!format) {
        _firelib.lib_errors.push(fireplace::_error(
            L"Failed to pick appropriate pixel format."
        ));
        return;
    }

    // The description of the format we got back.
    PFD description;

    // Attempt to describe pixel format.
    if (!::DescribePixelFormat(hdc, format, sizeof(PFD), &description)) {
        _firelib.lib_errors.push(fireplace::_error(
            new fireplace::_error(_win32_library::last_error()),
            L"Failed to describe pixel format."
        ));
        return;
    }

    // Attempt to set pixel format.
    if (!::SetPixelFormat(hdc, format, &description)) {
        _firelib.lib_errors.push(fireplace::_error(
            new fireplace::_error(_win32_library::last_error()),
            L"Failed to set pixel format."
        ));
        return;
    }

    // Set wgl attributes and create context with attributes.
    GLint attribs[40];

    // This is for ease of use.
    #define set_attrib(attrib, value)   \
        attribs[index++] = attrib;      \
        attribs[index++] = value;

    if (config.client_api == opengl_api) {
        if (config.forward_compat) {
            if (!_firelib.wgl.ARB_create_context) {
                _firelib.lib_errors.push(fireplace::_error(
                    L"A forward compatible context is unavailable."
                ));
                return;
            }
        }

        if (config.profile) {
            if (!_firelib.wgl.ARB_create_context_profile) {
                _firelib.lib_errors.push(fireplace::_error(
                    L"OpenGL profile requested but is unavailable."
                ));
                return;
            }
        }
    } else {
        if (
            !_firelib.wgl.ARB_create_context        ||
            !_firelib.wgl.ARB_create_context_profile||
            !_firelib.wgl.EXT_create_context_es2_profile
        ) {
            _firelib.lib_errors.push(fireplace::_error(
                L"OpenGL ES requested but is unavailable."
            ));
            return;
        }
    }

    if (_firelib.wgl.ARB_create_context) {
        int index   = 0;
        int mask    = 0;
        int flags   = 0;

        if (config.client_api == opengl_api) {
            if (config.forward_compat)
                flags |= WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;
            if (config.profile == core_profile)
                mask |= WGL_CONTEXT_CORE_PROFILE_BIT_ARB;
            else if (config.profile == compatibility_profile)
                mask |= WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;
        } else {
            mask |= WGL_CONTEXT_ES2_PROFILE_BIT_EXT;
        }

        if (config.debug)
            flags |= WGL_CONTEXT_DEBUG_BIT_ARB;

        if (config.robustness) {
            if (_firelib.wgl.ARB_create_context_robustness) {
                if (config.robustness == no_reset_notification) {
                    set_attrib(
                        WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB,
                        WGL_NO_RESET_NOTIFICATION_ARB
                    );
                } else if (config.robustness == lose_context_on_reset) {
                    set_attrib(
                        WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB,
                        WGL_LOSE_CONTEXT_ON_RESET_ARB
                    );
                }

                flags |= WGL_CONTEXT_ROBUST_ACCESS_BIT_ARB;
            }
        }

        if (config.release_behaviour) {
            if (_firelib.wgl.ARB_context_flush_control) {
                if (config.release_behaviour == release_behaviour_none) {
                    set_attrib(
                        WGL_CONTEXT_RELEASE_BEHAVIOUR_ARB,
                        WGL_CONTEXT_RELEASE_BEHAVIOUR_NONE_ARB
                    );
                } else if (config.release_behaviour == release_behaviour_flush) {
                    set_attrib(
                        WGL_CONTEXT_RELEASE_BEHAVIOUR_ARB,
                        WGL_CONTEXT_RELEASE_BEHAVIOUR_FLUSH_ARB
                    );
                }
            }
        }

        if (config.no_error) {
            if (_firelib.wgl.ARB_create_context_no_error) {
                set_attrib(WGL_CONTEXT_OPENGL_NO_ERROR_ARB, true);
            }
        }

        if (config.major_version != 1 || config.minor_version != 0) {
            set_attrib(WGL_CONTEXT_MAJOR_VERSION_ARB, config.major_version);
            set_attrib(WGL_CONTEXT_MINOR_VERSION_ARB, config.minor_version);
        }

        if (flags) {
            set_attrib(WGL_CONTEXT_FLAGS_ARB, flags);
        }

        if (mask) {
            set_attrib(WGL_CONTEXT_PROFILE_MASK_ARB, mask);
        }

        set_attrib(NULL, NULL);

        hrc = _firelib.wgl.create_context_attribs_arb(hdc, NULL, attribs);
    } else {
        hrc = _firelib.wgl.create_context(hdc);
    }

    // Check that we got out rendering context.
    if (!hrc) {
        _firelib.lib_errors.push(fireplace::_error(
            new fireplace::_error(fireplace::_win32_library::last_error()),
            L"Failed to create rendering context."
        ));
        return;
    }

    #undef set_attrib
}

// Deconstructs this context.
fireplace::_win32_wgl_context::~_win32_wgl_context() {
    if (hrc)
        _firelib.wgl.delete_context(hrc);
}

// Makes this context current.
void fireplace::_win32_wgl_context::make_current() {
    if (!_firelib.wgl.make_current(hdc, hrc)) {
        _firelib.lib_errors.push(fireplace::_error(
            new fireplace::_error(_win32_library::last_error()),
            L"Could not make context current."
        ));
        return;
    }
}

// Swaps the buffers of the given window.
void fireplace::_win32_wgl_context::swap_buffers() {
    if (!::SwapBuffers(hdc)) {
        _firelib.lib_errors.push(fireplace::_error(
            new fireplace::_error(_win32_library::last_error()),
            L"Failed to swap frame buffers."
        ));
        return;
    }
}

#endif
