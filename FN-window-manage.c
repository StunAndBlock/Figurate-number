#include "FN-window.h"
#include "stdio.h"
    static XWindowChanges values;
    static unsigned int valueMask;
void configureMenu(FN* global,XEvent* event){
    valueMask=(CWHeight);
    values.height=event->xconfigure.height;
    XConfigureWindow(global->dpy,global->menu.win,valueMask,&values);
    valueMask=(CWY);
    values.y=values.height-50;
    XConfigureWindow(global->dpy,global->menu.drawButton,valueMask,&values);
  //  XDrawLine(global->dpy,global->menu.win,global->menu.gc,199,0,199,values.height);

}

void configureFigure(FN* global,XEvent* event){


}
