#include <fireplace.h>

// For convenience.
constexpr unsigned int width    = 1280;
constexpr unsigned int height   = 720;

int main(int argc, char** argv) {
    fireplace::frame window;
    window.resize_to(1280, 720);
    window.position_at((1600 - width) / 2, (900 - height) / 2);
    window.make_current();
    window.show();

    while (window.is_open()) {
        window.poll_events();
        window.swap_buffers();
    }

    return EXIT_SUCCESS;
}
