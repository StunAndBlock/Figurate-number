#ifndef FN_window_H_ 
#define FN_window_H_
#pragma once
#include "X11/Xlib.h"
#include "X11/Xutil.h"

struct FNwin {
    Display *dpy;
    Window root;
    GC gc;
    unsigned int width;
    unsigned int height;
};

typedef struct FNwin FNwin;

void initScr(FNwin* global);
#endif //FN_window_H_ end definition