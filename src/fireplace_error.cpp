// This file contains the definitions for the _error structure as described by
// the fireplace_internal header.
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
fireplace::_error::_error() :
    cause(),
    message(L"")
{
}

// Constructs a new error with the given cause, code, and message.
fireplace::_error::_error(fireplace::_error _cause, std::wstring _message) :
    cause(_cause),
    message(_message)
{
}

// Copy constructor.
fireplace::_error::_error(const fireplace::_error& other) :
    cause(fireplace::_error(other.cause)),  // Follows deep copy construction.
    message(other.message)
{
}

// Move constructor.
fireplace::_error::_error(fireplace::_error&& other) :
    cause(),
    message(L"")
{
    std::swap(cause, other.cause);
    std::swap(message, other.message);
}

// Deconstructs this error.
fireplace::_error::~_error() {
    if (cause) delete cause;
}

// Copy-swap idiom operator.
fireplace::_error& fireplace::_error::operator=(fireplace::_error other) {
    this->cause     = other.cause;
    this->message   = other.message;
}
