#include "stdio.h"
#include "FN-window.h"
#include "FN-calcs.h"


void dispatch(FN*);


int main(){
    FN global;
    initDpy(&global);
    initGraphics(&global);
    initScr(&global);
    dispatch(&global);






    return 0;
}




void dispatch(FN* global){
    XEvent event;
    FNcontrols controls;
    controls.numberOpt=-1;
    controls.numberN=-1;
    controls.tempNumber=0;
    controls.listMenuIsOpened=0;
    controls.inputIsOpened=0;
    controls.numericKeyPressedinRow=0;
    while (1){
     XNextEvent(global->dpy, &event);
     switch (event.type) {
        case ConfigureNotify:
        //fprintf(stderr,"{%d}\n",event.xconfigure.height);
        //XDrawPoint(global->dpy,global->menu.win,global->menu.gc,199,event.xexpose.height);
        configureMenu(global,&event);
        configureFigure(global,&event);
        break;
        case Expose:
        break;
        case ButtonPress:
        buttonControl(global,&event,&controls);
       // if(event.xbutton.window==global->menu.field){
         //   for(int i=0;i<MENU_LIST_AMMOUNT;i++)
         //   XMapWindow(global->dpy,global->menu.list[i]);
       // }
        fprintf(stderr,"{%ld}\n",event.xbutton.window);
        break;
        case KeyPress:
        keyControl(global,&event,&controls);
        break;
        default:

        //fprintf(stderr,"%d : \t%d\n",event.type,i);
        break;
     }
    }
    


}