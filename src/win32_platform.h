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

namespace fireplace {

}

#endif
