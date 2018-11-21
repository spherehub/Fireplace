#include "fireplace_internal"

// Constructs a new error.
fireplace::_error::_error() :
    cause(nullptr),
    code(NULL),
    message(L"")
{
}

// Constructs a new error with the given cause, code, and message.
fireplace::_error::_error(
    _error _cause,
    unsigned long _code,
    std::wstring _message
) :
    cause(_cause),
    code(_code),
    message(_message)
{
}

// Copy constructor.
fireplace::_error::_error(const _error& other) :
    cause(std::copy(other.cause)),
    code(std::copy(other.code)),
    message(std::copy(other.message))
{
}

// Move constructor.
fireplace::_error::_error(_error&& other) :
    cause(nullptr),
    code(NULL),
    message(L"")
{
    std::swap(cause, other.cause);
    std::swap(code, other.code);
    std::swap(message, other.message);
}

// Deconstructs this error.
fireplace::_error::~_error() {
}

// Copy-swap idiom operator.
fireplace::_error& fireplace::_error::operator=(_error other) {
    this->cause     = other.cause;
    this->code      = other.code;
    this->message   = other.message;
}
