#include <stdio.h>

#define doubloop(x,y,limx,limy)\
    for(x=0;x<limx;x++){\
    for(y=0;y<limy;y++){


int main(){

    int x,y;
    int width=160;
    int height=160;

    doubloop(x,y,width,height)
    printf("%d,%d\n",x,y);
    }}
}