#include "FN-calcs.h"



unsigned int textSize(const char* text){
    unsigned int i=0;
    for(;*text;i++,text++);
    return i-1;
}
int keycodeToInt(int lastnumber,int keycode,int p){
   return lastnumber*10+((keycode+1)%10);
}

unsigned int triangularFormula(int n){
    return (pow(n,2)+n)/2;
}