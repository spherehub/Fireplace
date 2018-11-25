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

// The declaration of the external fireplace library.
fireplace::_fireplace_library _firelib;

// Prints all errors to the console.
void fireplace::dump_errors() {
// Unimplemented for the moment.
}

// Prints all the info log to the console.
void fireplace::dump_info_log() {
// Unimplemented for the moment.
}

// Gets a user pointer by it's mapped name.
fireplace::handle fireplace::get_user_pointer(std::string pointer_name) {
    return _firelib.user_pointers.find(pointer_name)->second;
}

// Sets the attribute of a given requested frame buffer.
void fireplace::set_attribute(const unsigned int attrib, const int value) {
    switch (attrib) {
    #ifdef _FIREPLACE_OPENGL
    case context_profile:
        _firelib.config.profile = value;
        break;
    case context_debug:
        _firelib.config.debug = value;
        break;
    case context_forward_compatible:
        _firelib.config.forward_compat = value;
        break;
    case context_no_error:
        _firelib.config.no_error = value;
        break;
    case context_release_behaviour:
        _firelib.config.release_behaviour = value;
        break;
    case context_robustness:
        _firelib.config.robustness = value;
        break;
    case context_major_version:
        _firelib.config.major_version = value;
        break;
    case context_minor_version:
        _firelib.config.minor_version = value;
        break;
    case context_creation_api:
        _firelib.config.creation_api = value;
        break;
    case context_client_api:
        _firelib.config.client_api = value;
        break;
    case stereoscopic:
        _firelib.config.stereoscopic = value;
        break;
    case samples:
        _firelib.config.samples = value;
        break;
    case auxiliary_buffers:
        _firelib.config.auxiliary_buffers = value;
        break;
    case double_buffered:
        _firelib.config.double_buffered = value;
        break;
    case transparent:
        _firelib.config.transparent = value;
        break;
    case accum_alpha_bits:
        _firelib.config.accum_alpha_bits = value;
        break;
    case accum_green_bits:
        _firelib.config.accum_green_bits = value;
        break;
    case accum_blue_bits:
        _firelib.config.accum_blue_bits = value;
        break;
    case accum_red_bits:
        _firelib.config.accum_red_bits = value;
        break;
    case stencil_bits:
        _firelib.config.stencil_bits = value;
        break;
    case depth_bits:
        _firelib.config.depth_bits = value;
        break;
    case alpha_bits:
        _firelib.config.alpha_bits = value;
        break;
    case alpha_shift:
        _firelib.config.alpha_shift = value;
        break;
    case blue_bits:
        _firelib.config.blue_bits = value;
        break;
    case blue_shift:
        _firelib.config.blue_shift = value;
        break;
    case green_bits:
        _firelib.config.green_bits = value;
        break;
    case green_shift:
        _firelib.config.green_shift = value;
        break;
    case red_bits:
        _firelib.config.red_bits = value;
        break;
    case red_shift:
        _firelib.config.red_shift = value;
        break;
    #endif
    }
}

// Stores a user pointer.
void fireplace::set_user_pointer(
    std::string pointer_name,
    fireplace::handle handle
) {
    _firelib.user_pointers.emplace(std::make_pair(pointer_name, handle));
}