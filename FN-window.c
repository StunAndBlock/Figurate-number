#include "FN-window.h"



void initScr(FNwin* global){
    global->dpy = XOpenDisplay(NULL);
    int scr = DefaultScreen(global->dpy);
    int depth = DefaultDepth(global->dpy, scr);
    global->height=DisplayHeight(global->dpy, scr);
    global->width=DisplayWidth(global->dpy, scr);
    XSetWindowAttributes attr;
    XSizeHints hint;

    attr.override_redirect = False;
    attr.background_pixel = WhitePixel(global->dpy, scr);
    
    global->root =
      XCreateWindow(global->dpy, DefaultRootWindow(global->dpy), 0, 0,
                    global->width, global->height, 0,
                    depth, InputOutput, CopyFromParent,
                    (CWOverrideRedirect | CWBackPixel), &attr);
}