// This file contains all the definitions for the win32 wgl configuration
// object. This is used to help determine what context configuration will be
// used by wgl.
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

// Copy constructor.
fireplace::_win32_wgl_config::_win32_wgl_config(
    const _win32_wgl_config& other
) :
    profile(std::copy(other.profile)),
    debug(std::copy(other.debug)),
    forward_compatibility(std::copy(other.forward_compatibility)),
    no_error(std::copy(other.no_error)),
    release_behaviour(std::copy(other.release_behaviour)),
    robustness(std::copy(other.robustness)),
    major_version(std::copy(other.major_version)),
    minor_version(std::copy(other.minor_version)),
    creation_api(std::copy(other.creation_api)),
    client_api(std::copy(other.client_api)),
    stereoscopic(std::copy(other.stereoscopic)),
    multisample(std::copy(other.multisample)),
    auxiliary_buffers(std::copy(other.auxiliary_buffers)),
    accumulation_alpha_bits(std::copy(other.accumulation_alpha_bits)),
    accumulation_blue_bits(std::copy(other.accumulation_blue_bits)),
    accumulation_green_bits(std::copy(other.accumulation_green_bits)),
    accumulation_red_bits(std::copy(other.accumulation_red_bits)),
    stencil_bits(std::copy(other.stencil_bits)),
    depth_bits(std::copy(other.depth_bits)),
    alpha_bits(std::copy(other.alpha_bits)),
    blue_bits(std::copy(other.blue_bits)),
    green_bits(std::copy(other.green_bits)),
    red_bits(std::copy(other.red_bits))
{
}

// Move constructor.
fireplace::_win32_wgl_config::_win32_wgl_config(
    _win32_wgl_config&& other
) :
    profile(0),
    debug(0),
    forward_compatibility(0),
    no_error(0),
    release_behaviour(0),
    robustness(0),
    major_version(0),
    minor_version(0),
    creation_api(0),
    client_api(0),
    stereoscopic(0),
    multisample(0),
    auxiliary_buffers(0),
    accumulation_alpha_bits(0),
    accumulation_blue_bits(0),
    accumulation_green_bits(0),
    accumulation_red_bits(0),
    stencil_bits(0),
    depth_bits(0),
    alpha_bits(0),
    blue_bits(0),
    green_bits(0),
    red_bits(0)
{
    std::swap(profile, other.profile);
    std::swap(debug, other.debug);
    std::swap(forward_compatibility, other.forward_compatibility);
    std::swap(no_error, other.no_error);
    std::swap(release_behaviour, other.release_behaviour);
    std::swap(robustness, other.robustness);
    std::swap(major_version, other.major_version);
    std::swap(minor_version, other.minor_version);
    std::swap(creation_api, other.creation_api);
    std::swap(client_api, other.client_api);
    std::swap(stereoscopic, other.stereoscopic);
    std::swap(multisample, other.multisample);
    std::swap(auxiliary_buffers, other.auxiliary_buffers);
    std::swap(accumulation_alpha_bits, other.accumulation_alpha_bits);
    std::swap(accumulation_blue_bits, other.accumulation_blue_bits);
    std::swap(accumulation_green_bits, other.accumulation_green_bits);
    std::swap(accumulation_red_bits, other.accumulation_red_bits);
    std::swap(stencil_bits, other.stencil_bits);
    std::swap(depth_bits, other.depth_bits);
    std::swap(alpha_bits, other.alpha_bits);
    std::swap(blue_bits, other.blue_bits);
    std::swap(green_bits, other.green_bits);
    std::swap(red_bits, other.red_bits);
}

// Copy-swap idiom assignment operator.
fireplace::_win32_wgl_config& fireplace::_win32_wgl_config::operator(
    _win32_wgl_config other
) {
    std::swap(profile, other.profile);
    std::swap(debug, other.debug);
    std::swap(forward_compatibility, other.forward_compatibility);
    std::swap(no_error, other.no_error);
    std::swap(release_behaviour, other.release_behaviour);
    std::swap(robustness, other.robustness);
    std::swap(major_version, other.major_version);
    std::swap(minor_version, other.minor_version);
    std::swap(creation_api, other.creation_api);
    std::swap(client_api, other.client_api);
    std::swap(stereoscopic, other.stereoscopic);
    std::swap(multisample, other.multisample);
    std::swap(auxiliary_buffers, other.auxiliary_buffers);
    std::swap(accumulation_alpha_bits, other.accumulation_alpha_bits);
    std::swap(accumulation_blue_bits, other.accumulation_blue_bits);
    std::swap(accumulation_green_bits, other.accumulation_green_bits);
    std::swap(accumulation_red_bits, other.accumulation_red_bits);
    std::swap(stencil_bits, other.stencil_bits);
    std::swap(depth_bits, other.depth_bits);
    std::swap(alpha_bits, other.alpha_bits);
    std::swap(blue_bits, other.blue_bits);
    std::swap(green_bits, other.green_bits);
    std::swap(red_bits, other.red_bits);
}

#endif
