#include "fireplace_internal.h"

// The declaration of the external fireplace library.
fireplace::_fireplace_library _firelib;

// Prints all errors to the console.
void fireplace::dump_errors() {
// Unimplemented for the moment.
}

// Prints all the info log to the console.
void fireplace::dump_info_log() {
// Unimplemented for the moment.
}

// Gets a user pointer by it's mapped name.
fireplace::handle fireplace::get_user_pointer(std::string pointer_name) {
    return _firelib.user_pointers.find(pointer_name)->second;
}

// Stores a user pointer.
void fireplace::set_user_pointer(
    std::string pointer_name,
    fireplace::handle handle
) {
    _firelib.user_pointers.emplace(std::make_pair(pointer_name, handle));
}