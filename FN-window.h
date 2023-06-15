#ifndef FN_window_H_ 
#define FN_window_H_
#pragma once
#include "X11/Xlib.h"
#include "X11/Xutil.h"
struct FNmenuwin {
    Window win;
    Window field;
    Window drawButton;
    Window list[13];
    XFontStruct *fn;
    GC gc[2];
};
typedef struct FNmenuwin FNmenu;

struct FNrootwin {
    Window win;
    GC gc;
};
typedef struct FNrootwin FNroot;

struct FNfigurewin{
    Window win;
    GC gc;
};
typedef struct FNfigurewin FNfigure;
struct FNglobal {
    Display *dpy;
    FNroot root;
    FNmenu menu;
    FNfigure figure;
    unsigned int width;
    unsigned int height;
};
typedef struct FNglobal FN;

void initDpy(FN* global);
void initScr(FN* global);
void initGraphics(FN* global);
void configureMenu(FN* global,XEvent* event);
void firstStart(FN*,unsigned char*);

#endif //FN_window_H_ end definition