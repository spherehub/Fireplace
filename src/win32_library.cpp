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
        fireplace::_error err(
            fireplace::_error(nullptr, err_code, this->last_error()),
            FAILED_INITIALIZATION,
            L"Failed to register window class."
        );

        _firelib.lib_errors.push(err);
        return;
    }
}

// Deconstructs this library.
fireplace::_win32_library::~_win32_library() {
    if (!::UnregisterClass(FIREPLACE_WIN32CLASSNAME, GetModuleHandle(NULL))) {
        fireplace::_error err(
            fireplace::_error(nullptr, err_code, this->last_error()),
            FAILED_TERMINATION,
            L"Failed to unregister window class."
        );

        _firelib.lib_errors.push(err);
        return;
    }
}

//
std::wstring fireplace::_win32_library::last_error() {
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
