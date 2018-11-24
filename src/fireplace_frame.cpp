// This file contains the definitions for the frame class declared in the main
// fireplace header. Each method here contains a platform specific body.
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

// Constructs a default window.
fireplace::frame::frame() :
    frame(L"Fireplace")
{
}

// Constructs a window with the given unicode title.
fireplace::frame::frame(std::wstring title) :
    m_handle(nullptr),
    m_context(nullptr)
{
#ifdef _WIN32
    _win32_create_window(m_handle, title.c_str(), this);

    if (m_handle) {
        // create window context.
    }
#endif
}

// Copy constructor.
fireplace::frame::frame(const frame& other) :
    m_handle(other.m_handle),
    m_context(other.m_context)
{
}

// Move constructor.
fireplace::frame::frame(frame&& other) :
    m_handle(nullptr),
    m_context(nullptr)
{
    this->swap(other);
}

// Deconstructs this window.
fireplace::frame::~frame() {
    if (m_handle) free(m_handle);
    if (m_context) delete m_context;
}

// Copy-swap idiom operator.
fireplace::frame& fireplace::frame::operator=(frame other) {
    this->swap(other);
}

// Closes this window. This releases some memory so it is non-const.
void fireplace::frame::close() {
#ifdef _WIN32
    _win32_destroy_window(m_handle);
#endif
}

// Disables this window.
void fireplace::frame::disable() const {
#ifdef _WIN32
    _win32_disable(m_handle);
#endif
}

// Enables this window.
void fireplace::frame::enable() const {
#ifdef _WIN32
    _win32_enable(m_handle);
#endif
}

// Focuses this window.
void fireplace::frame::focus() const {
#ifdef _WIN32
    _win32_focus(m_handle);
#endif
}

// Gets the position of this window.
void fireplace::frame::get_position(int& pos_x, int& pos_y) const {
#ifdef _WIN32
    _win32_get_position(m_handle, pos_x, pos_y);
#endif
}

// Gets the size of this window.
void fireplace::frame::get_size(int& width, int& height) const {
#ifdef _WIN32
    _win32_get_size(m_handle, width, height);
#endif
}

// Returns the handle to the underlying window.
const void* fireplace::frame::handle() const {
    return m_handle;
}

// Hides this window.
void fireplace::frame::hide() const {
#ifdef _WIN32
    _win32_hide(m_handle);
#endif
}

// Checks if this window is enabled.
bool fireplace::frame::is_enabled() const {
#ifdef _WIN32
    return _win32_is_enabled(m_handle);
#endif
}

// Checks if this window is focused.
bool fireplace::frame::is_focused() const {
#ifdef _WIN32
    return _win32_is_focused(m_handle);
#endif
}

// Checks if this window is maximized.
bool fireplace::frame::is_maximized() const {
#ifdef _WIN32
    return _win32_is_maximized(m_handle);
#endif
}

// Checks if this window is minimized.
bool fireplace::frame::is_minimized() const {
#ifdef _WIN32
    return _win32_is_minimized(m_handle);
#endif
}

// Returns whether or not this window is open.
bool fireplace::frame::is_open() const {
#ifdef _WIN32
    return _win32_is_open(m_handle);
#endif
}

// Makes this window current.
void fireplace::frame::make_current() const {
#ifdef _WIN32
// Unimplementable right now.
#endif
}

// Maximizes this window.
void fireplace::frame::maximize() const {
#ifdef _WIN32
    _win32_maximize(m_handle);
#endif
}

// Minimizes this window.
void fireplace::frame::minimize() const {
#ifdef _WIN32
    _win32_minimize(m_handle);
#endif
}

// Polls the events for this window.
void fireplace::frame::poll_events() const {
#ifdef _WIN32
    _win32_poll_events(m_handle);
#endif
}

// Repositions this window.
void fireplace::frame::position_at(int pos_x, int pos_y) {
#ifdef _WIN32
    _win32_position_at(m_handle, pos_x, pos_y);
#endif
}

// Resizes this window.
void fireplace::frame::resize_to(int width, int height) {
#ifdef _WIN32
    _win32_resize_to(m_handle, width, height);
#endif
}

// Sets the title of this window.
void fireplace::frame::set_title(std::wstring title) {
#ifdef _WIN32
    _win32_set_title(m_handle, title.c_str());
#endif
}

// Shows this window.
void fireplace::frame::show() const {
#ifdef _WIN32
    _win32_show(m_handle);
#endif
}

// Swaps this window's frame buffers.
void fireplace::frame::swap_buffers() const {
#ifdef _WIN32
// Unimplementable right now.
#endif
}

// Swaps this window with the given window.
void fireplace::frame::swap(frame& other) {
    std::swap(m_handle, other.m_handle);
    std::swap(m_context, other.m_context);
}

// Gets the title of this window.
std::wstring fireplace::frame::title() const {
#ifdef _WIN32
    return _win32_title(m_handle);
#endif
}
