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
          
          for(i=-1;i<3-1;i++){
            for(j=-1;j<3-1;j++){
              //printf("(i,j)=(%d,%d)\n",i,j);
           
                mul_x=j*(-1);
                mul_y=i*(-1);
                //printf("mul(x,y))=%d %d\n",mul_x,mul_y);
                if(x+j>=0&&x+j<idata.width)
                  diff_x+=mul_x*(idata.source[RED][y][x+j]);
                else{
                  printf("At %d,%d:\n",x,y);
                  printf("x=%d is out of bounds!\n\n",x+j);
                }
                if(y+i>=0&&y+i<idata.height)
                  diff_y+=mul_y*(idata.source[RED][y+i][x]);
                else{
                  printf("At %d,%d:\n",x,y);
                  printf("y=%d is out of bounds!\n\n",y+i);
                }
                
                //printf("diff(x,y):(%d,%d)\n",diff_x,diff_y);
              
              }
            }
          
      
          result=sqrt((diff_x*diff_x)+(diff_y*diff_y)-100);
         // printf("result=%d\n",result);
          if(result>255) result=255;
          idata.cwork[RED][y][x]=result;
        }
      }

  for (y=0;y<idata.height;y++){
	      for (x = 0; x < idata.width;x++){
          idata.results[RED][y][x]=idata.cwork[RED][y][x];
          idata.results[GREEN][y][x]=idata.cwork[RED][y][x];
          idata.results[BLUE][y][x]=idata.cwork[RED][y][x];
         // printf("data=%d\n",idata.cwork[RED][y][x]);
        }
    }
      if (writeBMPfile(argv[2], &idata) > 0)
	printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);
    }
  }
}
