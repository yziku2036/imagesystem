#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "def.h"
#include "var.h"
#include "bmpfile.h"

void averaging(int**);
void copy_array(int*,int*);

int main(int argc, char *argv[])
{


  imgdata idata;
  double c;
  int x, y;
  Uchar Y;
  int LUT[256];
  double Zmax=256;
  double a=7.0;
  int pixel_freq[256]={0};//0埋め
  int pixel_freq_copy[256];
  int totu;
  int hekomi;
  int nm[256][256];

  // 例題プログラム
  // 　BMPファイルをコピーするプログラム
  if (argc < 3) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    else {
      for(int i=0;i<Zmax;i++){
        LUT[i]=(int)(Zmax*(1/(1+(pow(M_E,-1*a*((i/Zmax)-0.5))))));
        //printf("%d\n",LUT[i]);
      }

  double mean=(idata.height*idata.width)/idata.color_depth;

    /* 例題：コピーするプログラム */
  for (y = idata.height-1; y > -1; y--){
	   for (x = 0; x < idata.width; x++){
       pixel_freq[idata.source[RED][y][x]]++;


          }
      }
  int bright_mean=0;
      //pixel_freqに濃度平均を作成&コピー
  for (int i =0;i<256;i++){
    printf("pixel_freq[%d]=%d\n",i,pixel_freq[i]);
    bright_mean+=pixel_freq[i];
  }
  bright_mean/=256;
  printf("bright_mean:%d\n",bright_mean);
  copy_array(pixel_freq,pixel_freq_copy);

/**
      for (y = idata.height-1; y > -1; y--){
        for (x = 0; x < idata.width; x++){
          if(bright_mean> pixel_freq[] ){
          }
          }
      }
*/
//  int count=0;
  int target_index=0;
  //棒グラフが移動する量の値
  int val_moving_pixel=0;//動く量
  int val_move_process=0;//動かすための値
  int next_index=0;
  int lack=0;
  int bring=0;
  for(int i=0;i<255;i++){
    if(bright_mean > pixel_freq[i]){
      lack=bright_mean-pixel_freq[i];
      for(int j=i+1;j<255;j++){
        //不足分がでかすぎた場合(ループする)
        if(pixel_freq[j]<lack){
          lack-=pixel_freq[j];
          nm[j][i]=pixel_freq[j];
        }  
        //次のデータが十分にデカかった場合
        else{
          lack=0;
          nm[j][i]=pixel_freq[j];
        }
      
      if(lack<=0) break;
    }
  }
  }
  /* 例題：コピーするプログラム */
    for (y = 0; y < idata.height; y++){
for (x = 0; x < idata.width; x++){
  ///idata.results[RED][y][x]
    //= nm[][];
  idata.results[GREEN][y][x]
    = LUT[idata.source[GREEN][y][x]];
  idata.results[BLUE][y][x]
    =LUT[idata.source[BLUE][y][x]];

}
    }
      if (writeBMPfile(argv[2], &idata) > 0)
	printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);

    }

  }
}

void copy_array(int* original,int* copied){

  for(int i=0;original[i]!='\0';i++){
    copied[i]=original[i];
  }
}
