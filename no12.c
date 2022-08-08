#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "def.h"
#include "var.h"
#include "bmpfile.h"

int main(int argc, char *argv[])
{
  imgdata idata;
  double c;
  int x, y,i,j;
  Uchar Y;
  int n=5;
  int load_sum=0;
  int center=1;
  int N=3*3-1;
  int diff_x,diff_y;
  int mul_x,mul_y;
  int result;

  if (argc < 3) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    else {
      for(y=0; y<idata.height;y++){
        for(x=0;x<idata.width;x++){
          diff_x=0;
          diff_y=0;
          N=3*3-1;
          for(i=0;i<3;i++){
            for(j=0;j<3;j++){
              if(((y+i-1>=0)&&(x+j-1>=0))&&((y+i-1<idata.height)&&(x+j-1<idata.width))){
                mul_x=1-j;
                mul_y=1-i;
                diff_x+=mul_x*(idata.source[RED][y][x+j-1]);
                diff_y+=mul_y*(idata.source[RED][y+i-1][x]);
                printf("diff(x,y):(%d,%d)\n",diff_x,diff_y);
              }else{
                diff_x=0;
                diff_y=0;
              }
            }
          }
          printf("N:%d\n",N);
          load_sum/=(n+N);
          printf("load_sum:%d\n",load_sum); 
          result=sqrt((diff_x*diff_x)+(diff_y*diff_y));
          if(result>255) result=255;
          idata.cwork[RED][y][x]=result;
        }
      }

  for (y=0;y<idata.height;y++){
	      for (x = 0; x < idata.width;x++){
          idata.results[RED][y][x]=idata.cwork[RED][y][x];
          idata.results[GREEN][y][x]=idata.cwork[RED][y][x];
          idata.results[BLUE][y][x]=idata.cwork[RED][y][x];
          printf("data=%d\n",idata.cwork[RED][y][x]);
        }
    }
      if (writeBMPfile(argv[2], &idata) > 0)
	printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);
    }
  }
}
