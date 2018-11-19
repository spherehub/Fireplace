#ifndef _FIREPLACE_INTERNAL_HEADER
#define _FIREPLACE_INTERNAL_HEADER

// For ostream and other printing operations.
#include <fireplace.h>
#include <iostream>

// Include our own platform headers.
#ifdef _WIN32
// include win32 header.
#endif

namespace fireplace {
    /*
     * This is a structure representing an error that can be filed by any
     * processes performed by the library.
     */
    struct _error final {
        // A possible cause for this error.
        _error* cause;

        // A numeric representation of this error.
        unsigned long code;

        // The message of this error.
        std::wstring message;

        // Constructs an empty error.
        explicit _error();

        // Constructs an error with the given cause, code, and message.
        explicit _error(_error cause, unsigned long code, std::wstring message);

        // Copy constructor.
        _error(const _error& other);

        // Move constructor.
        _error(_error&& other);

        // Deconstructs this error.
        ~_error();

        // Copy-swap idiom operator.
        _error& operator=(_error& other);
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
        _info& operator=(_info& other);
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

        // Constructs a new instance of the library.
        explicit _fireplace_library();

        // Copy construction is not allowed.
        _fireplace_library(const _fireplace_library& other) = delete;

        // Move construction is not allowed.
        _fireplace_library(_fireplace_library&& other) = delete;

        // Deconstructs this library.
        ~_fireplace_library();

        // Assignment not allowed.
        _fireplace_library& operator=(_fireplace_library other) = delete;
    };

    /*
     * The external instance of the fireplace library that is usable by the
     * compilation units.
     */
    extern _fireplace_library _firelib;
}

#endif
