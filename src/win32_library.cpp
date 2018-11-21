// This file contains the definitions for the win32 library structure as defined
// by the win32_platform header.
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
#ifdef _WIN32

// Constructs a new _win32_library.
fireplace::_win32_library::_win32_library() :
    wndcls()
{
    wndcls.cbClsExtra       = NULL;
    wndcls.cbSize           = sizeof(WNDCLASSEX);
    wndcls.cbWndExtra       = NULL;
    wndcls.hbrBackground    = (HBRUSH)(COLOR_WINDOW + 1);
    wndcls.hCursor          = NULL;
    wndcls.hIcon            = NULL;
    wndcls.hIconSm          = NULL;
    wndcls.hInstance        = ::GetModuleHandle(NULL);
    wndcls.lpszClassName    = FIREPLACE_WIN32CLASSNAME;
    wndcls.lpszMenuName     = FIREPLACE_WIN32MENUNAME;
    wndcls.lpfnWndProc      = _window_procedure;
    wndcls.style            = CS_HREDRAW | CS_OWNDC | CS_VREDRAW;

    if (!::RegisterClasseEx(&wndcls)) {
        _firelib.lib_errors.push(fireplace::_error(
            fireplace::_error(nullptr, WIN32_ERROR, _win32_library::last_error()),
            FAILED_INITIALIZATION,
            L"Failed to register window class."
        ));
        return;
    }
}

// Deconstructs this library.
fireplace::_win32_library::~_win32_library() {
    if (!::UnregisterClass(FIREPLACE_WIN32CLASSNAME, GetModuleHandle(NULL))) {
        _firelib.lib_errors.push(fireplace::_error(
            fireplace::_error(nullptr, WIN32_ERROR, _win32_library::last_error()),
            FAILED_TERMINATION,
            L"Failed to unregister window class."
        ));
        return;
    }
}

// Gets the last error registered by windows.
void fireplace::_win32_library::last_error() {
    // Windows cause for this error.
    LPWSTR message_buffer   = nullptr;
    DWORD err_code          = ::GetLastError();

    ::FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER  |
        FORMAT_MESSAGE_FROM_SYSTEM      |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        err_code,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR)&message_buffer,
        0,
        NULL
    );

    std::wstring res(message_buffer);
    ::LocalFree(message_buffer);

    return res;
}

#endif
