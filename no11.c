#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "def.h"
#include "var.h"
#include "bmpfile.h"

int isOutofBounds(int,int,int);

typedef struct{
  int x;
  int y;
}coord;

int main(int argc, char *argv[])
{
  imgdata idata;
  double c;
  int x, y;
  int dx,dy;
  int g;
  int i,j;
  coord index;
  int prewitt_x[3][3]={{1,0,-1},{1,0,-1},{1,0,-1}};
  int prewitt_y[3][3]={{1,1,1},{0,0,0},{-1,-1,-1}};
  // 例題プログラム
  // 　BMPファイルをコピーするプログラム

  if (argc < 3) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    else {

      for(y=0;y<idata.height;y++){
        for(x=0;x<idata.width;x++){
          idata.cwork[RED][y][x]=0;
        }
      }

      for(y=0;y<idata.height;y++){
        for(x=0;x<idata.width;x++){
          dx=0;
          dy=0;
          for(i=0;i<3;i++){
            for(j=0;j<3;j++){
              index.x=x+j-1;
              index.y=y+i-1;
              if(isOutofBounds(index.x,index.y,idata.height)==0){
              dx+=idata.source[RED][index.y][index.x]*prewitt_x[i][j];
              dy+=idata.source[RED][index.y][index.x]*prewitt_y[i][j];
              }
              else printf("OUTOFBOUNDS:%d,%d\n",index.x,index.y);
            }
          }
          g=sqrt(dx*dx+dy*dy);
          if(g>255)
          g=255;
          idata.cwork[RED][y][x]=g;
        }
      }



    /* 例題：コピーするプログラム */
      for (y = 0; y < idata.height; y++){
	for (x = 0; x < idata.width; x++){

    idata.results[RED][y][x]
	    = idata.cwork[RED][y][x];
	  idata.results[GREEN][y][x]
	    = idata.cwork[RED][y][x];
	  idata.results[BLUE][y][x]
	    = idata.cwork[RED][y][x];
	}
      }
      if (writeBMPfile(argv[2], &idata) > 0)
	printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);
    }
  }
}

int isOutofBounds(int a,int b,int max){
  if((a<0||b<0)||(a>max-1||b>max-1))
    return 1;
  else
    return 0;
}