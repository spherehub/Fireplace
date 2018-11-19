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
#define FIREPLACE_PATCH 3

namespace fireplace {

}

#endif
