#include "FN-window.h"
#include "./materials/colours.h"
void initDpy(FN* global){
 global->dpy = XOpenDisplay(NULL);
}

void initScr(FN* global){
    int scr = DefaultScreen(global->dpy);
    int depth = DefaultDepth(global->dpy, scr);
    global->height=DisplayHeight(global->dpy, scr);
    global->width=DisplayWidth(global->dpy, scr);
    XSetWindowAttributes attr;
    XSizeHints hint;
    Pixmap pix;
    /*--------------------------global------------------------------*/
    hint.min_width=800;
    hint.min_height=600;
    attr.override_redirect = False;
    attr.background_pixel = WhitePixel(global->dpy, scr);
    
    global->root.win =
      XCreateWindow(global->dpy, DefaultRootWindow(global->dpy), 0, 0,
                    800,600, 0,
                    depth, InputOutput, CopyFromParent,
                    (CWOverrideRedirect | CWBackPixel), &attr);
    
    hint.flags = (PMinSize);
    XSetNormalHints(global->dpy, global->root.win, &hint);
    /*------------------------menu-----------------------------*/
    pix=XCreatePixmap(global->dpy,DefaultRootWindow(global->dpy),200,1,depth);
    XDrawLine(global->dpy,pix,global->menu.gc[0],0,0,198,0);
    XDrawPoint(global->dpy,pix,global->menu.gc[1],199,0);
    attr.background_pixmap=pix;
    global->menu.win=
          XCreateWindow(global->dpy, global->root.win , 0, 0,
                    200,600, 0,
                    depth, InputOutput, CopyFromParent,
                    (CWBackPixmap), &attr);

    pix=XCreatePixmap(global->dpy,DefaultRootWindow(global->dpy),200,50,depth);
    XFillRectangle(global->dpy,pix,global->menu.gc[0],0,0,200,50);
    XDrawLine(global->dpy,pix,global->menu.gc[1],0,49,199,49);
    XDrawLine(global->dpy,pix,global->menu.gc[1],199,0,199,49);
    XDrawString(global->dpy,pix,global->menu.gc[1],10,10,"choose type",11);
    attr.background_pixmap=pix;
    global->menu.field=
            XCreateWindow(global->dpy, global->root.win , 0, 0,
                    200,50, 0,
                    depth, InputOutput, CopyFromParent,
                    (CWBackPixmap), &attr);

    pix=XCreatePixmap(global->dpy,DefaultRootWindow(global->dpy),200,50,depth);
    XFillRectangle(global->dpy,pix,global->menu.gc[0],0,0,200,50);
    XDrawLine(global->dpy,pix,global->menu.gc[1],0,0,199,0);
    XDrawLine(global->dpy,pix,global->menu.gc[1],199,0,199,49);
    XDrawString(global->dpy,pix,global->menu.gc[1],10,10,"draw",4);
    attr.background_pixmap=pix;
    global->menu.drawButton=
            XCreateWindow(global->dpy, global->root.win , 0,600-50,
                    200,50, 0,
                    depth, InputOutput, CopyFromParent,
                    (CWBackPixmap), &attr);
}

void initGraphics(FN* global){
    XFontStruct *fn; /* Font parameters structure */
    char *fontname = "9x15";
    /*--------------------------global------------------------------*/
    ;
    /*------------------------menu-----------------------------*/
    global->menu.gc[0]=XDefaultGC(global->dpy,0);
    global->menu.gc[1]=XCreateGC(global->dpy,DefaultRootWindow(global->dpy),0,0);
    XSetForeground(global->dpy, global->menu.gc[0], MENU_BACKGROUND);
    XSetForeground(global->dpy, global->menu.gc[1], MENU_BORDER);
    if ((fn = XLoadQueryFont(global->dpy, fontname)) != NULL){
    XSetFont(global->dpy,global->menu.gc[0], fn->fid);
    XSetFont(global->dpy,global->menu.gc[1], fn->fid);
    }
    
}