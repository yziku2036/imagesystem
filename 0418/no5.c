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
  int LUT[256];
  double Zmax=255;
  // 例題プログラム
  // 　BMPファイルをコピーするプログラム

  if (argc < 3) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    else {
      for(int i=0;i<Zmax+1;i++){
        LUT[i]=(int)(Zmax*(((i/Zmax))*((i/Zmax))));
        printf("%d\n",LUT[i]);
      }


    /* 例題：コピーするプログラム */
      for (y = 0; y < idata.height; y++){
	for (x = 0; x < idata.width; x++){
    idata.results[RED][y][x]
	    = LUT[idata.source[RED][y][x]];
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
