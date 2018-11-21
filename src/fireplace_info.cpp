#include "fireplace_internal"

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
    message(std::copy(other.message))
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
}
