#include <stdio.h>
#include <stdlib.h>

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
  int square_size=3;
  int load_sum=0;
  int edge_index=(square_size-1)/2;
  int center=edge_index;
  int N=square_size*square_size-1;

  if (argc < 3) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    else {
      for(y=0; y<idata.height;y++){
        for(x=0;x<idata.width;x++){
          load_sum=0;
          N=square_size*square_size-1;
          for(i=0;i<square_size;i++){
            for(j=0;j<square_size;j++){
              if(((y+i-edge_index>=0)&&(x+j-edge_index>=0))&&((y+i-edge_index<idata.height)&&(x+j-edge_index<idata.width))){
                if(i==center&&j==center){
                  load_sum+=n*idata.source[RED][y+i-edge_index][x+j-edge_index];
                }
                else{
                  load_sum+=idata.source[RED][y+i-edge_index][x+j-edge_index];
                }
                printf("load:%d\n",load_sum);
              }else{
                N--;
              }
            }
          }
          printf("N:%d\n",N);
          load_sum/=(n+N);
          printf("load_sum:%d\n",load_sum); 
          idata.cwork[RED][y][x]=load_sum;
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