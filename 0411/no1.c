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
  // 例題プログラム
  // 　BMPファイルをコピーするプログラム

  if (argc < 3) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    else {
    /* 例題：コピーするプログラム */
      for (y = 0; y < idata.height; y++){
	for (x = 0; x < idata.width; x++){
    Y = idata.source[RED][y][x]*0.299+idata.source[GREEN][y][x]*0.587
      +idata.source[BLUE][y][x]*0.114;

    idata.results[RED][y][x]
	    = Y;
	  idata.results[GREEN][y][x]
	    = Y;
	  idata.results[BLUE][y][x]
	    = Y;
	}
      }
      if (writeBMPfile(argv[2], &idata) > 0)
	printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);
    }
  }
}
