/*
  This program maked by j17407.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "def.h"
#include "var.h"
#include "bmpfile.h"

#define rand_range(min,max) (min)+(rand())%((max)-(min)+(1))

void init_LUT(int LUT[],int val){
  for(int i=0;i<256;i++){
    if(i < val)
      LUT[i] = 0;
    else
      LUT[i] = 255;
  }
}

int main(int argc, char* argv[])
{
  imgdata idata;
  double c;
  int x, y;
  int a = INT_MAX;
  int b = INT_MIN;
  int LUT[256];
  static int hist[256];
  if (argc < 3) printf("使用法：%s 入力.bmp 出力.bmp\n", argv[0]);
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定入力ファイル%sが見つかりません\n", argv[1]);
    else {
      for (y = 0; y < idata.height; y++) {
	for (x = 0; x < idata.width; x++) {
	  hist[idata.source[RED][y][x]]++;
	}
      }
      printf("%d\n",hist[255]);
      int first=0,second = 0;
      int mini = 0;
      first = 0;
      for(int i=0;i<256;i++){
	if(hist[first] - hist[i] <=0)
	  first = (hist[first] < hist[i]) ? i : first;
	else
	  break;
      }
      second = first+50;
      for(int i=first+50;i<256;i++){
	if(hist[second] - hist[i] <= 0 && hist[i]>=200)
	  second = (hist[second] < hist[i]) ? i : second;
	else
	  break;
      }
      mini = first;
      for(int i=first;i<=second;i++){
	mini = (hist[mini] > hist[i]) ? i : mini;
      }
      init_LUT(LUT,mini);
      for (y = 0; y < idata.height; y++) {
	for (x = 0; x < idata.width; x++) {
	  idata.results[RED][y][x] = LUT[idata.source[RED][y][x]];
	  idata.results[GREEN][y][x] = LUT[idata.source[GREEN][y][x]];
	  idata.results[BLUE][y][x] = LUT[idata.source[BLUE][y][x]];
	}
      }
      if (writeBMPfile(argv[2], &idata) > 0)
	printf("出力ファイル%sに保存できませんでした\n", argv[2]);
    }
  }
}
