// This header contains the internal constructs and inner workings of the
// fireplace api.
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
#ifndef _FIREPLACE_INTERNAL_HEADER
#define _FIREPLACE_INTERNAL_HEADER

// For ostream and other printing operations.
#include <fireplace.h>
#include <iostream>
#include <unordered_map>
#include <queue>

// Include our own platform headers.
#ifdef _WIN32
#include "win32_platform.h"
#endif

namespace fireplace {
    /*
     * This is a structure representing an error that can be filed by any
     * processes performed by the library.
     */
    struct _error final {
        // A possible cause for this error.
        _error cause;

        // The message of this error.
        std::wstring message;

        // Constructs an empty error.
        explicit _error();

        // Constructs an error with the given cause, code, and message.
        explicit _error(_error cause, std::wstring message);

        // Copy constructor.
        _error(const _error& other);

        // Move constructor.
        _error(_error&& other);

        // Deconstructs this error.
        ~_error();

        // Copy-swap idiom operator.
        _error& operator=(_error other);
    };

    /*
     * This is a structure representing an information log that can be filed by
     * any processes performed by the library.
     */
    struct _info final {
        // The message of this info log.
        std::wstring message;

        // Constructs an empty info log.
        explicit _info();

        // Constructs an new info log with the given message.
        _info(std::wstring message);

        // Copy constructor.
        _info(const _info& other);

        // Move constructor.
        _info(_info&& other);

        // Deconstructs this info log.
        ~_info();

        // Copy-swap idiom operator.
        _info& operator=(_info other);
    };

    /*
     * This structure represents the library itself, and what the library is
     * responsible with keeping up with, including platform specific libraries.
     */
    struct _fireplace_library final {
        // The registered errors from processes in the library that threw errors.
        std::queue<_error> lib_errors;

        // The registered info from processes in the library that provide info.
        std::queue<_info> lib_infolog;

        // A map of user pointers to names.
        std::unordered_map<std::string, handle> user_pointers;

    #ifdef _WIN32
        // The windows necessary library.
        _win32_library win32;

    #ifdef _FIREPLACE_OPENGL
        // The window necessary wgl library.
        _win32_wgl_library wgl;

    #endif // _FIREPLACE_OPENGL
    #endif // _WIN32

        // Constructs a new instance of the library.
        explicit _fireplace_library();

        // Copy construction is not allowed.
        _fireplace_library(const _fireplace_library& other) = delete;

        // Move construction is not allowed.
        _fireplace_library(_fireplace_library&& other) = delete;

        // Deconstructs this library.
        ~_fireplace_library();

        // Assignment not allowed.
        _fireplace_library& operator=(_fireplace_library& other) = delete;
    };

    /*
     * The external instance of the fireplace library that is usable by the
     * compilation units.
     */
    extern _fireplace_library _firelib;
}

#endif
