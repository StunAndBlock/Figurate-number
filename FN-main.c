#include "stdio.h"
#include "FN-window.h"



void dispatch(FN*);


int main(){
    FN global;
    initDpy(&global);
    initGraphics(&global);
    initScr(&global);
    long mask=(ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask);
    XSelectInput(global.dpy,global.root.win,mask);
    XSelectInput(global.dpy,global.menu.win,mask);
    XMapWindow(global.dpy,global.root.win);
    XMapSubwindows(global.dpy,global.root.win);
    
    dispatch(&global);






    return 0;
}




void dispatch(FN* global){
    XEvent event;
    while (1){
     XNextEvent(global->dpy, &event);
     switch (event.type) {
        case ConfigureNotify:
        fprintf(stderr,"{%d}\n",event.xconfigure.height);
        //XDrawPoint(global->dpy,global->menu.win,global->menu.gc,199,event.xexpose.height);
        configureMenu(global,&event);
        break;
        case Expose:
        break;
        case ButtonPress:
        fprintf(stderr,"{%ld}\n",event.xbutton.window);
        break;
        default:

        //fprintf(stderr,"%d : \t%d\n",event.type,i);
        break;
     }
    }
    


}