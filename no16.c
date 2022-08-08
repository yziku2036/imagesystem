#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "var.h"
#include "bmpfile.h"

int max(int,int);
int min(int,int);

int main(int argc, char *argv[])
{
  imgdata idata;
  double c;
  int x, y;
  int hist_range=256;
  int hist[256]={0};
  // 例題プログラム
  // 　BMPファイルをコピーするプログラム

  if (argc < 3) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    else {
      int count=0;
      for(y=0;y<idata.height;y++){
        for(x=0;x<idata.width;x++){
          hist[idata.source[RED][y][x]]+=1;  
        }
      }

      int max_1st=0;
      int max_1st_index=0;
      int max_2nd=0;
      int max_2nd_index=0;

      for(int i=0;i<hist_range;i++){
        if (hist[i]>max_1st){
          max_1st=hist[i];
          max_1st_index=i;
          }
        }
        
      for(int i=0;i<max_1st_index-50;i++){
        if (hist[i]>max_1st){
          max_2nd=hist[i];
          max_2nd_index=i;
          }
        }

      for(int i=max_1st_index+50;i<hist_range;i++){
        if (hist[i]>max_2nd){
          max_2nd=hist[i];
          max_2nd_index=i;
          }
        }
      int tmp1=min(max_1st_index,max_2nd_index);
      int tmp2=max(max_1st_index,max_2nd_index);
      max_2nd_index=tmp1;
      max_1st_index=tmp2;
      //max_2nd<max_1st
      int volley=hist_range-1;
      int volley_index=0;
      for(int i=max_2nd_index;i<max_1st_index;i++){
        if(hist[i]<volley){
          volley=hist[i];
          volley_index=i;
          }
        }
      //printf("1st:%d\n",max_1st);
      //printf("2nd:%d\n",max_2nd);
      //printf("c=%d\n",count);
      for(y=0;y<idata.height;y++){
        for(x=0;x<idata.width;x++){
          if(idata.source[RED][y][x]<volley_index)
            idata.cwork[RED][y][x]=0;
          else
            idata.cwork[RED][y][x]=hist_range-1;
          }
        }
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

int max(int a,int b){
  if(a>b) return a;
  else return b;
}


int min(int a,int b){
  if(a>b)return b;
  else return a;
}