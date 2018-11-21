#include "fireplace_internal.h"
#ifdef _WIN32
#define ASHWND(handle) \
    ((HWND)handle)

#define ASHANDLE(_handle) \
    ((fireplace::handle)_handle)

// Closes the given window.
void fireplace::_win32_close(fireplace::handle _window) {
    fireplace::_win32_destroy_window(_window);
}

// Creates a window with the given name.
void fireplace::_win32_create_window(
    fireplace::handle _window,
    const wchar_t* title,
    fireplace::frame* _frame
) {
    _window = (fireplace::handle)::CreateWindowEx(
        WS_EX_APPWINDOW | WS_EX_OVERLAPPEDWINDOW,
        FIREPLACE_WIN32CLASSNAME,
        title,
        WS_OVERLAPPEDWINDOW,
        0,
        0,
        640,
        480,
        NULL,
        NULL,
        _firelib.win32.wndcls.hInstance,
        NULL
    );

    // Check that window succeeded to create.
    if (!_window) {
        _firelib.lib_errors.push(fireplace::_error(
            fireplace::_error(
                nullptr,
                WIN32_ERROR,
                _win32_library::last_error()
            ),
            WINDOW_ERROR,
            L"Could not close window."
        ));
        return;
    }

    ::SetProp(ASHWND(_window), L"FIREPLACE_PROP", _frame);
}

// Destroys a given window.
void fireplace::_win32_destroy_window(fireplace::handle _window) {
    // Confirm window exists.
    if (!::IsWindow(ASHWND(_window)) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            WINDOW_ERROR,
            L"Could not close window, window is invalid."
        ));
        return;
    }

    // Remove props from window.
    ::RemoveProp(ASHWND(_window), L"FIREPLACE_PROP");

    // Attempt to destroy window.
    if (!::DestroyWindow(ASHWND(_window))) {
        _firelib.lib_errors.push(fireplace::_error(
            fireplace::_error(
                nullptr,
                WIN32_ERROR,
                _win32_library::last_error()
            ),
            WINDOW_ERROR,
            L"Could not close window."
        ));
        return;
    }
}

// Disables the given window.
void fireplace::_win32_disable(fireplace::handle _window) {
    // Confirm window exists.
    if (!::IsWindow(ASHWND(_window))) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            WINDOW_ERROR,
            L"Could not disable window, window is invalid."
        ));
        return;
    }

    ::EnableWindow(ASHWND(_window), false);
}

// Enables the given window.
void fireplace::_win32_enable(fireplace::handle _window) {
    // Confirm window exists.
    if (!::IsWindow(ASHWND(_window))) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            WINDOW_ERROR,
            L"Could not enable window, window is invalid."
        ));
        return;
    }

    ::EnableWindow(ASHWND(_window), true);
}

// Focuses the given window.
void fireplace::_win32_focus(fireplace::handle _window) {
    // Confirm window exists.
    if (!::IsWindow(ASHWND(_window))) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            WINDOW_ERROR,
            L"Could not focus window, window is invalid."
        ));
        return;
    }

    ::SetFocus(ASHWND(_window));
}

// Gets the position of the given window.
void fireplace::_win32_get_position(
    fireplace::handle _window,
    int& pos_x,
    int& pos_y
) {
    // Confirm window exists.
    if (!::IsWindow(ASHWND(_window))) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            WINDOW_ERROR,
            L"Could not get window position, window is invalid."
        ));
        return;
    }

    RECT rect;
    if (!::GetWindowRect(ASHWND(_window), &rect)) {
        _firelib.lib_errors.push(fireplace::_error(
            fireplace::_error(
                nullptr,
                WIN32_ERROR,
                _win32_library::last_error()
            ),
            WINDOW_ERROR,
            L"Could not get window position."
        ));
    }

    pos_x = rect.left;
    pos_y = rect.top;
}

// Gets the size of the given window.
void fireplace::_win32_get_size(
    fireplace::handle _window,
    int& width,
    int& height
) {
    // Confirm window exists.
    if (!::IsWindow(ASHWND(_window))) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            WINDOW_ERROR,
            L"Could not get window size, window is invalid."
        ));
        return;
    }

    RECT rect;
    if (!::GetWindowRect(ASHWND(_window), &rect)) {
        _firelib.lib_errors.push(fireplace::_error(
            fireplace::_error(
                nullptr,
                WIN32_ERROR,
                _win32_library::last_error()
            ),
            WINDOW_ERROR,
            L"Could not get window size."
        ));
    }

    width   = rect.right - rect.left;
    height  = rect.bottom - rect.top;
}

// Hides the given window.
void fireplace::_win32_hide(fireplace::handle _window) {
    // Confirm window exists.
    if (!::IsWindow(ASHWND(_window))) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            WINDOW_ERROR,
            L"Could not hide window, window is invalid."
        ));
        return;
    }

    ::ShowWindow(ASHWND(_window), SW_HIDE);
}

// Checks if the given window is enabled.
bool fireplace::_win32_is_enabled(fireplace::handle _window) {
    // Confirm window exists.
    if (!::IsWindow(ASHWND(_window))) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            WINDOW_ERROR,
            L"Window is not enabled, window is invalid."
        ));
        return false;
    }

    return ::IsWindowEnabled(ASHWND(_window));
}

// Checks if the given window is focused.
bool fireplace::_win32_is_focused(fireplace::handle _window) {
    // Confirm window exists.
    if (!::IsWindow(ASHWND(_window))) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            WINDOW_ERROR,
            L"Window is not focused, window is invalid."
        ));
        return false;
    }

    return (::GetFocus() == ASHWND(_window));
}

// Checks if the given window is maximized.
bool fireplace::_win32_is_maximized(fireplace::handle _window) {
    // Confirm window exists.
    if (!::IsWindow(ASHWND(_window))) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            WINDOW_ERROR,
            L"Window is not maximized, window is invalid."
        ));
        return false;
    }

    WINDOWPLACEMENT wnd_placement = { sizeof(WINDOWPLACEMENT) };
    ::GetWindowPlacement(ASHWND(_window), &wnd_placement);
    return (wnd_placement.showCmd == SW_MAXIMIZE);
}

// Checks if the given window is maximized.
bool fireplace::_win32_is_minimized(fireplace::handle _window) {
    // Confirm window exists.
    if (!::IsWindow(ASHWND(_window))) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            WINDOW_ERROR,
            L"Window is not minimized, window is invalid."
        ));
        return false;
    }

    WINDOWPLACEMENT wnd_placement = { sizeof(WINDOWPLACEMENT) };
    ::GetWindowPlacement(ASHWND(_window), &wnd_placement);
    return (wnd_placement.showCmd == SW_MINIMIZE);
}

// Checks if the given window is open.
bool fireplace::_win32_is_open(fireplace::handle _window) {
    return ::IsWindow(ASHWND(_window));
}

// Maximizes the given window.
void fireplace::_win32_maximize(fireplace::handle _window) {
    // Confirm window exists.
    if (!::IsWindow(ASHWND(_window))) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            WINDOW_ERROR,
            L"Could not maximize window, window is invalid."
        ));
        return;
    }

    ::ShowWindow(ASHWND(_window), SW_MAXIMIZE);
}

void fireplace::_win32_minimize(fireplace::handle _window) {
    // Confirm window exists.
    if (!::IsWindow(ASHWND(_window))) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            WINDOW_ERROR,
            L"Could not minimize window, window is invalid."
        ));
        return;
    }

    ::ShowWindow(ASHWND(_window), SW_MINIMIZE);
}

// Polls the events for the given window.
void fireplace::_win32_poll_events(fireplace::handle _window) {
    // Confirm window exists.
    if (!::IsWindow(ASHWND(_window))) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            WINDOW_ERROR,
            L"Cannot poll events of invalid window."
        ));
        return;
    }

    // TODO: set up message filters.

    MSG msg;
    while (::Peek(&msg, ASHWND(_window), 0, 0, PM_REMOVE) > 0) {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }
}

// Positions the given window at the given coordinates.
void fireplace::_win32_position_at(
    fireplace::handle _window,
    int pos_x,
    int pos_y
) {
    // Confirm window exists.
    if (!::IsWindow(ASHWND(_window))) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            WINDOW_ERROR,
            L"Could not position window, window is invalid."
        ));
        return;
    }

    // Attempt to position window, catch whatever could go wrong.
    if (
        !::SetWindowPos(ASHWND(_window), NULL, pos_x, pos_y, 0, 0, SWP_NOSIZE)
    ) {
        _firelib.lib_errors.push(fireplace::_error(
            fireplace::_error(
                nullptr,
                WIN32_ERROR,
                _win32_library::last_error()
            ),
            WINDOW_ERROR,
            L"Could not position window."
        ));
        return;
    }
}

// Resizes the given window.
void fireplace::_win32_resize_to(
    fireplace::handle _window,
    int width,
    int height
) {
    // Confirm window exists.
    if (!::IsWindow(ASHWND(_window))) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            WINDOW_ERROR,
            L"Could not resize window, window is invalid."
        ));
        return;
    }

    // Attempt to resize window, catch whatever could go wrong.
    if (
        !::SetWindowPos(ASHWND(_window), NULL, 0, 0, width, height, SWP_NOMOVE)
    ) {
        _firelib.lib_errors.push(fireplace::_error(
            fireplace::_error(
                nullptr,
                WIN32_ERROR,
                _win32_library::last_error()
            ),
            WINDOW_ERROR,
            L"Could not resize window."
        ));
        return;
    }
}

// Sets the title of the given window.
void fireplace::_win32_set_title(
    fireplace::handle _window,
    const wchar_t* title
) {
    // Confirm window exists.
    if (!::IsWindow(ASHWND(_window))) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            WINDOW_ERROR,
            L"Could not set window title, window is invalid."
        ));
        return;
    }

    // Attempt to set window title, catch whatever could go wrong.
    if (!::SetWindowText(ASHWND(_window), title)) {
        _firelib.lib_errors.push(fireplace::_error(
            fireplace::_error(
                nullptr,
                WIN32_ERROR,
                _win32_library::last_error()
            ),
            WINDOW_ERROR,
            L"Could not set window title."
        ));
        return;
    }
}

// Shows the given window.
void fireplace::_win32_show(fireplace::handle _window) {
    // Confirm window exists.
    if (!::IsWindow(ASHWND(_window))) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            WINDOW_ERROR,
            L"Could not show window, window is invalid."
        ));
        return;
    }

    ::ShowWindow(ASHWND(_window), SW_SHOW);
}

// Gets the title of the given window.
std::wstring fireplace::_win32_title(fireplace::handle _window) {
    // Confirm window exists.
    if (!::IsWindow(ASHWND(_window))) {
        _firelib.lib_errors.push(fireplace::_error(
            nullptr,
            WINDOW_ERROR,
            L"Could not get window title, window is invalid."
        ));
        return;
    }

    int length      = ::GetWindowTitleLength(ASHWND(_window));
    wchar_t* title  = (wchar_t*)::calloc(lenght, sizeof(wchar_t));
    int count       = ::GetWindowText(ASHWND(_window), title, length);

    // Something went wrong.
    if (count < length) {
        _firelib.lib_errors.push(fireplace::_error(
            fireplace::_error(
                nullptr,
                WIN32_ERROR,
                _win32_library::last_error()
            ),
            WINDOW_ERROR,
            L"Could not get window title."
        ));
        return std::wstring(L"");
    }

    return std::wstring(title, length);
}

#endif
