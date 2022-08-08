#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "var.h"
#include "bmpfile.h"

int main(int argc, char *argv[])
{
  imgdata idata;
  double c;
  int x, y;
  Uchar Y;
  int n=5;
  int square_size=3;
  int load_sum=0;

  if (argc < 3) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    else {
  for (y=0;y < idata.height;y++){
	  for (x = 0; x < idata.width;x++){
      printf("sum reset result:%d\n",load_sum);
      load_sum=0;
      for(int i=0;i<square_size;i++){
        for(int j=0;j<square_size;j++){
          if((y+j-1 >=0 && x+i-1 >=0)&&(y+j-1 <idata.height && x+i-1 <idata.width)){
            //もし真ん中の成分なら
            if(i==((square_size-1)/2)&&j==((square_size-1)/2)){
              load_sum+= n*idata.source[RED][y+j-1][x+i-1]/(n+square_size);
            }
            else{
              load_sum+= idata.source[RED][y+j-1][x+i-1]/(n+square_size);
            }
            //printf("load_sum:%d\n",load_sum);
          }
        }
      }
      idata.cwork[RED][y][x]=load_sum;
    }
  }

  for (y=0;y<idata.height;y++){
	      for (x = 0; x < idata.width;x++){
          idata.results[RED][y][x]=idata.cwork[RED][y][x];
          idata.results[GREEN][y][x]=idata.cwork[RED][y][x];
          idata.results[BLUE][y][x]=idata.cwork[RED][y][x];
          //printf("data=%d\n",idata.cwork[RED][y][x]);
        }
    }
      if (writeBMPfile(argv[2], &idata) > 0)
	printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);
    }
  }
}
