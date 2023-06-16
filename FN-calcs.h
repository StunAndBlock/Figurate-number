#ifndef FN_calcs_H_
#define FN_calcs_H_
#include "math.h"

#define FN_XK_1 10
#define FN_XK_9 19
#define FN_XK_ENTER 36
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))





unsigned int textSize(const char* text);
int keycodeToInt(int lastnumber,int keycode,int);
unsigned int triangularFormula(int n);

#endif //FN_calcs_H_ end definition