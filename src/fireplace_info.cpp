// This file contains the definitions for the _info log structure as described
// by the fireplace_internal header.
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

// Constructs a new error.
fireplace::_info::_info() :
    message(L"")
{
}

// Constructs a new error with the given cause, code, and message.
fireplace::_info::_info(std::wstring _message) :
    message(_message)
{
}

// Copy constructor.
fireplace::_info::_info(const _info& other) :
    message(other.message)
{
}

// Move constructor.
fireplace::_info::_info(_info&& other) :
    message(L"")
{
    std::swap(message, other.message);
}

// Deconstructs this error.
fireplace::_info::~_info() {
}

// Copy-swap idiom operator.
fireplace::_info& fireplace::_info::operator=(_info other) {
    this->message = other.message;

    return *this;
}
