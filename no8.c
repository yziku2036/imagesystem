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
  int val_moving_pixel;


  for(int i=0;i<256;i++){
    //val_moving_pixel=0;
    for (int j=i+1;j<256;j++){
      //濃度が高かった場合
      if(pixel_freq[i] >= bright_mean){
        //押し付け先が見つかるまでループ
        while(pixel_freq[j] < bright_mean){
          j++;
        }
        //pixel_freq[i]は必ず濃度平均より大きい
        //残ってる濃度空間のサイズを調べて、小さい方の空間文だけ移動する
        //はみでてる部分-凹んでる部分
        totu=pixel_freq[i]-bright_mean;
        hekomi=bright_mean-pixel_freq[j];
        if(totu<=hekomi){
          //はみ出た文移動
          val_moving_pixel=pixel_freq[j]-bright_mean;
          break;
        }


        //開いた穴のサイズだけ移動
      else  if(totu>hekomi) {
          val_moving_pixel=bright_mean-pixel_freq[i];
          //へこみの量だけ凸の量から減らす
          pixel_freq[i]=totu-hekomi;
        }
        nm[i][j]=val_moving_pixel;
      }


      //今注目してるのが凹んでた場合
      else if(pixel_freq[i] <= bright_mean){
        //今の棒と1つ次の棒の合計がbright_meanを越えてたら
        //必要な量だけ移動
        if(pixel_freq[i]+pixel_freq[j]>bright_mean){
          val_moving_pixel=bright_mean-pixel_freq[i];
        //今の棒と1つ次の棒の合計がbright_meanを越えてなかったら
        //1つ右の量をそのまま移動
        }else{
          val_moving_pixel = pixel_freq[j];
        }

      }
      //nm[i][j]=val_moving_pixel;
      printf("nm[%d][%d]=%d\n",i,j,nm[i][j]);

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
