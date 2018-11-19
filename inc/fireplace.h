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

// Versioning.
#define FIREPLACE_MAJOR 0
#define FIREPLACE_MINOR 0
#define FIREPLACE_PATCH 4

// Context rendering apis.
#ifdef _FIREPLACE_OPENGL
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
#define egl_context_api             0x110D
#define osmesa_context_api          0x110E
#endif

namespace fireplace {

}

#endif
