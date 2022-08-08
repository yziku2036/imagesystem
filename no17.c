#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "var.h"
#include "bmpfile.h"

int isOutofIndex(int, int, int, int);

int main(int argc, char *argv[])
{
  imgdata idata;
  double c;
  int x, y;
  int i, j;
  int ave, var, tmp;
  int N = 7;
  int looking_x, looking_y;
  int valid_pixel_count;
  int prev_threshold;
  // 例題プログラム
  // 　BMPファイルをコピーするプログラム
  if (argc < 3)
    printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else
  {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n", argv[1]);
    else
    {
      for (y = 0; y < idata.height; y++)
      {
        prev_threshold=0;
        for (x = 0; x < idata.width; x++)
        {
          ave = 0;
          var = 0;
          valid_pixel_count = 0;

          for (i = 0; i < N; i++)
          {
            for (j = 0; j < N; j++)
            {
              looking_x = x + j - ((N - 1) / 2);
              looking_y = y + i - ((N - 1) / 2);
              if (!isOutofIndex(looking_x, looking_y, idata.width, idata.height))
              {
                ave += idata.source[RED][looking_y][looking_x];
                valid_pixel_count += 1;
              }
            }
          }
          printf("ave=%d/%d\n",ave,valid_pixel_count);
          ave = ave / valid_pixel_count;

          for (i = 0; i < N; i++)
          {
            for (j = 0; j < N; j++)
            {
              looking_x = x + j - ((N - 1) / 2);
              looking_y = y + i - ((N - 1) / 2);
              if (!isOutofIndex(looking_x, looking_y, idata.width, idata.height))
              {
                tmp = idata.source[RED][looking_y][looking_x];
                tmp -= ave;
                tmp = tmp * tmp;
                var += tmp;
              }
            }
          }
          var = var / valid_pixel_count;
          if (var >= 1000)
          {
            idata.cwork[RED][y][x] = ave;
            prev_threshold = ave;
          }
          else
            idata.cwork[RED][y][x] = prev_threshold;
        }
      }
      int result;
      /* 例題：コピーするプログラム */
      for (y = 0; y < idata.height; y++)
      {
        for (x = 0; x < idata.width; x++)
        {
          if (idata.cwork[RED][y][x] <= idata.source[RED][y][x])
            result = 255;
          else
            result = 0;
          idata.results[RED][y][x] = result;
          idata.results[GREEN][y][x] = result;
          idata.results[BLUE][y][x] = result;
        }
      }
      if (writeBMPfile(argv[2], &idata) > 0)
        printf("コピー先ファイル%sに保存できませんでした\n", argv[2]);
    }
  }
}

int isOutofIndex(int x, int y, int xmax, int ymax)
{
  if (x < 0 || y < 0 || x >= xmax || y >= ymax)
    return 1;
  else
    return 0;
}