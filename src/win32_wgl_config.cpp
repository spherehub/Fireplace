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
    profile(other.profile),
    debug(other.debug),
    forward_compat(other.forward_compat),
    no_error(other.no_error),
    release_behaviour(other.release_behaviour),
    robustness(other.robustness),
    major_version(other.major_version),
    minor_version(other.minor_version),
    creation_api(other.creation_api),
    client_api(other.client_api),
    stereoscopic(other.stereoscopic),
    samples(other.samples),
    auxiliary_buffers(other.auxiliary_buffers),
    double_buffered(other.double_buffered),
    transparent(other.transparent),
    accum_alpha_bits(other.accum_alpha_bits),
    accum_blue_bits(other.accum_blue_bits),
    accum_green_bits(other.accum_green_bits),
    accum_red_bits(other.accum_red_bits),
    stencil_bits(other.stencil_bits),
    depth_bits(other.depth_bits),
    alpha_bits(other.alpha_bits),
    blue_bits(other.blue_bits),
    green_bits(other.green_bits),
    red_bits(other.red_bits),
    handle(other.handle)
{
}

// Move constructor.
fireplace::_win32_wgl_config::_win32_wgl_config(
    _win32_wgl_config&& other
) :
    profile(0),
    debug(0),
    forward_compat(0),
    no_error(0),
    release_behaviour(0),
    robustness(0),
    major_version(0),
    minor_version(0),
    creation_api(0),
    client_api(0),
    stereoscopic(0),
    samples(0),
    auxiliary_buffers(0),
    double_buffered(0),
    transparent(0),
    accum_alpha_bits(0),
    accum_blue_bits(0),
    accum_green_bits(0),
    accum_red_bits(0),
    stencil_bits(0),
    depth_bits(0),
    alpha_bits(0),
    blue_bits(0),
    green_bits(0),
    red_bits(0),
    handle(0)
{
    std::swap(profile, other.profile);
    std::swap(debug, other.debug);
    std::swap(forward_compat, other.forward_compat);
    std::swap(no_error, other.no_error);
    std::swap(release_behaviour, other.release_behaviour);
    std::swap(robustness, other.robustness);
    std::swap(major_version, other.major_version);
    std::swap(minor_version, other.minor_version);
    std::swap(creation_api, other.creation_api);
    std::swap(client_api, other.client_api);
    std::swap(stereoscopic, other.stereoscopic);
    std::swap(samples, other.samples);
    std::swap(auxiliary_buffers, other.auxiliary_buffers);
    std::swap(double_buffered, other.double_buffered);
    std::swap(transparent, other.transparent);
    std::swap(accum_alpha_bits, other.accum_alpha_bits);
    std::swap(accum_blue_bits, other.accum_blue_bits);
    std::swap(accum_green_bits, other.accum_green_bits);
    std::swap(accum_red_bits, other.accum_red_bits);
    std::swap(stencil_bits, other.stencil_bits);
    std::swap(depth_bits, other.depth_bits);
    std::swap(alpha_bits, other.alpha_bits);
    std::swap(blue_bits, other.blue_bits);
    std::swap(green_bits, other.green_bits);
    std::swap(red_bits, other.red_bits);
    std::swap(handle, other.handle);
}

// Copy-swap idiom assignment operator.
fireplace::_win32_wgl_config& fireplace::_win32_wgl_config::operator=(
    _win32_wgl_config other
) {
    std::swap(profile, other.profile);
    std::swap(debug, other.debug);
    std::swap(forward_compat, other.forward_compat);
    std::swap(no_error, other.no_error);
    std::swap(release_behaviour, other.release_behaviour);
    std::swap(robustness, other.robustness);
    std::swap(major_version, other.major_version);
    std::swap(minor_version, other.minor_version);
    std::swap(creation_api, other.creation_api);
    std::swap(client_api, other.client_api);
    std::swap(stereoscopic, other.stereoscopic);
    std::swap(samples, other.samples);
    std::swap(auxiliary_buffers, other.auxiliary_buffers);
    std::swap(double_buffered, other.double_buffered);
    std::swap(transparent, other.transparent);
    std::swap(accum_alpha_bits, other.accum_alpha_bits);
    std::swap(accum_blue_bits, other.accum_blue_bits);
    std::swap(accum_green_bits, other.accum_green_bits);
    std::swap(accum_red_bits, other.accum_red_bits);
    std::swap(stencil_bits, other.stencil_bits);
    std::swap(depth_bits, other.depth_bits);
    std::swap(alpha_bits, other.alpha_bits);
    std::swap(blue_bits, other.blue_bits);
    std::swap(green_bits, other.green_bits);
    std::swap(red_bits, other.red_bits);
    std::swap(handle, other.handle);
}

#endif
