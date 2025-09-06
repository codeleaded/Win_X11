#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    Display *display;
    Window window;
    XEvent event;
    int screen;

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Kann keine Verbindung zum X-Server herstellen\n");
        exit(1);
    }

    screen = DefaultScreen(display);

    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, 800, 600, 1,
                                 BlackPixel(display, screen), WhitePixel(display, screen));

    XMapWindow(display, window);

    while (1) {
        XNextEvent(display, &event);

        if (event.type == ClientMessage) {
            if ((Atom)event.xclient.data.l[0] == XInternAtom(display, "WM_DELETE_WINDOW", False)) {
                break;
            }
        }
    }

    XCloseDisplay(display);
    return 0;
}
