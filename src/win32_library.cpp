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
    wndcls.hInstance        = GetModuleHandle(NULL);
    wndcls.lpszClassName    = FIREPLACE_WIN32CLASSNAME;
    wndcls.lpszMenuName     = FIREPLACE_WIN32MENUNAME;
    wndcls.lpfnWndProc      = _window_procedure;
    wndcls.style            = CS_HREDRAW | CS_OWNDC | CS_VREDRAW;

    if (!::RegisterClasseEx(&wndcls)) {
        // Throw error.
    }
}

// Deconstructs this library.
fireplace::_win32_library::~_win32_library() {
    if (!::UnregisterClass(FIREPLACE_WIN32CLASSNAME, GetModuleHandle(NULL))) {
        // Throw error.
    }
}

#endif
