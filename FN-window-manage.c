#include "FN-window.h"
#include "stdio.h"
#include "stdlib.h"
#include "FN-calcs.h"
    static XWindowChanges values;
    static unsigned int valueMask;
  
void configureMenu(FN* global,XEvent* event){
    valueMask=(CWHeight);
    values.height=event->xconfigure.height;
    XConfigureWindow(global->dpy,global->menu.win,valueMask,&values);
    valueMask=(CWY);
    values.y=values.height-MENU_BLOCK_HEIGHT;
    XConfigureWindow(global->dpy,global->menu.drawButton,valueMask,&values);
    valueMask=(CWY | CWX);
    //XUnmapWindow(global->dpy,global->menu.numberInput);
    values.x=event->xconfigure.width/2-MENU_BLOCK_WIDTH/2;
    values.y=event->xconfigure.height/2-MENU_BLOCK_HEIGHT/2;
    XConfigureWindow(global->dpy,global->menu.numberInput,valueMask,&values);
  //  XDrawLine(global->dpy,global->menu.win,global->menu.gc,199,0,199,values.height);

}

void configureFigure(FN* global,XEvent* event){
    valueMask=(CWHeight | CWWidth);
    values.height=MIN(event->xconfigure.height,event->xconfigure.width-MENU_BLOCK_WIDTH);
    values.width=MIN(event->xconfigure.height,event->xconfigure.width-MENU_BLOCK_WIDTH);
    XConfigureWindow(global->dpy,global->figure.win,valueMask,&values);

}

int findWindow(Window win,Window* list,int listsize){
   for(int i=0;i<listsize;i++){
        if(win==list[i]){
        return i;
        }
   }
   return -1;
}
void buttonControl(FN* global,XEvent* event,FNcontrols* controls){
  //if(!controls->inputIsOpened){
  if (!controls->listMenuIsOpened) { 
    if(event->xbutton.window==global->menu.field){
      for(int i=0;i<MENU_LIST_AMMOUNT;i++){
        XMapWindow(global->dpy,global->menu.list[i]);
      }
      controls->listMenuIsOpened=1;
    } else if(event->xbutton.window==global->menu.drawButton){
      fprintf(stderr,"draw the option:%d with n:%d",controls->numberOpt,controls->numberN);
      if(controls->numberOpt!=-1 && controls->numberN>0){
        XFillRectangle(global->dpy,global->figure.win,global->root.gc,0,0,600,600);
        assembleFigure(global,controls);
      }
    }
  }
  else {
    if (event->xbutton.window==global->menu.field){
      for(int i=0;i<MENU_LIST_AMMOUNT;i++){
        XUnmapWindow(global->dpy,global->menu.list[i]);
      }
      controls->listMenuIsOpened=0;
    } else {
      controls->numberOpt=findWindow(event->xbutton.window,global->menu.list,MENU_LIST_AMMOUNT);
      if(controls->numberOpt!=-1){
        XMapWindow(global->dpy,global->menu.numberInput);
        controls->inputIsOpened=1;
        fprintf(stderr,"choosed option: %d",controls->numberOpt);
      }
    }
  }
  //}else {
    if(event->xbutton.window!=global->menu.numberInput && findWindow(event->xbutton.window,global->menu.list,MENU_LIST_AMMOUNT)==-1){
      
      XUnmapWindow(global->dpy,global->menu.numberInput);
      controls->inputIsOpened=0;
      controls->numericKeyPressedinRow=0;
      controls->tempNumber=0;
      controls->numberN=-1;
    //}
  }

}

void keyControl(FN* global,XEvent* event,FNcontrols* controls){
  const char* c;
  char buf[10];
  if(event->xkey.keycode>=FN_XK_1 && event->xkey.keycode<=FN_XK_9){

   // fprintf(stderr,"num:%d %d",controls->tempNumber,controls->numericKeyPressedinRow);
   controls->tempNumber=keycodeToInt(controls->tempNumber,event->xkey.keycode,controls->numericKeyPressedinRow);
   sprintf(buf,"%d",controls->tempNumber);
   const char* c=buf;
   controls->numericKeyPressedinRow++;
   XDrawString(global->dpy,global->menu.numberInput,global->menu.gc[1],MENU_BLOCK_HEIGHT/4,MENU_BLOCK_HEIGHT/4,c,controls->numericKeyPressedinRow);
  } else if (event->xkey.keycode==FN_XK_ENTER){
   // fprintf(stderr,"num:%d %d\n",controls->tempNumber,controls->numericKeyPressedinRow);
    if(controls->numericKeyPressedinRow){
  controls->numberN=controls->tempNumber;
    } else {
  controls->numberN=-1;
    }
    controls->numericKeyPressedinRow=0;

    controls->tempNumber=0;
    XUnmapWindow(global->dpy,global->menu.numberInput);
    controls->inputIsOpened=0;
    for(int i=0;i<MENU_LIST_AMMOUNT;i++){
      XUnmapWindow(global->dpy,global->menu.list[i]);
    }
    controls->listMenuIsOpened=0;
    
  }
  
}
void triangularGraph(FN* global,int n,unsigned int pointsCount){
  XPoint* points=(XPoint*)malloc(sizeof(XPoint)*pointsCount);
  short d=600;
  short radius=d/60;
  short offset=d/(n+1);
  short xoffset=offset;
  short yoffset=d-offset;
  //fprintf(stderr,"\n(%d %d %d)\n",offset,pointsCount,n);
  int r=0;
  for(int i=0,pointsInRow=n;i<n;i++,pointsInRow--,yoffset-=offset){
    //points[r].y=yoffset;
    for(int j=0,xoffset=offset+offset/2*i;j<pointsInRow;j++,xoffset+=offset){
      points[r].x=xoffset;
      points[r].y=yoffset;
      r++;
      fprintf(stderr,"\n(%d %d)\n", xoffset,yoffset);
    }
  }
  XDrawPoints(global->dpy,global->figure.win,global->menu.gc[1],points,pointsCount,CoordModeOrigin);
  


  free(points);
}
void assembleFigure(FN* global,FNcontrols* controls){
  switch(controls->numberOpt){
    case 0:
    triangularGraph(global,controls->numberN,triangularFormula(controls->numberN));
    break;
    case 1:
    break;
    case 2:
    break;
    case 3:
    break;
    case 4:
    break;
    case 5:
    break;
    case 6:
    break;
    case 7:
    break;
    }
}
