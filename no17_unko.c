#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "var.h"
#include "bmpfile.h"

int isOutofBounds(int, int, int);

typedef struct
{
  int x;
  int y;
} coord;

int main(int argc, char *argv[])
{
  imgdata idata;
  double c;
  int x, y;
  int i, j;
  int ave = 0;
  int var = 0;
  int N = 7;
  int tmp;
  int threshold[256][256] = {0};
  int prev_threshold = 0;
  int valid_pixel_count = 0;
  coord index;
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
        for (x = 0; x < idata.width; x++)
        {
          ave = 0;
          var = 0;
          valid_pixel_count = 0;
          for (i = 0; i < N; i++)
          {
            for (j = 0; j < N; j++)
            {
              index.x = x + j - ((N - 1) / 2);
              index.y = y + i - ((N - 1) / 2);
              if (isOutofBounds(index.x, index.y, idata.height) == 0)
              {
                ave += idata.source[RED][index.y][index.x];
                valid_pixel_count += 1;
              }
            }
          }
          ave = ave / valid_pixel_count;
          for (i = 0; i < N; i++)
          {
            for (j = 0; j < N; j++)
            {
              index.x = x + j - ((N - 1) / 2);
              index.y = y + i - ((N - 1) / 2);
              if (isOutofBounds(index.x, index.y, idata.height) == 0)
              {
                tmp = idata.source[RED][index.y][index.x];
                tmp -= ave;
                // printf("tmp-ave=%d\n",tmp);
                tmp = tmp * tmp;
                // printf("tmp^2=%d\n",tmp);
                // printf("var changed:%d\n",tmp);
                // printf("Index:(%d,%d)\n",index.x,index.y);
                // printf("tmp=%d-%d tmp^2=%d\n",idata.source[RED][index.y][index.x],ave,tmp);
                var += tmp;
              }
            }
          }
          var = var / valid_pixel_count;
          printf("threshold:%d\n", prev_threshold);
          if (var >= 1000)
          {
            idata.cwork[RED][y][x] = ave;
            prev_threshold = ave;
          }
          else
            idata.cwork[RED][y][x] = prev_threshold;
        }
      }

      /* 例題：コピーするプログラム */
      for (y = 0; y < idata.height; y++)
      {
        for (x = 0; x < idata.width; x++)
        {
          if (idata.cwork[RED][y][x] <= idata.source[RED][y][x])
          {
            idata.results[RED][y][x] = 255;
            idata.results[GREEN][y][x] = 255;
            idata.results[BLUE][y][x] = 255;
          }
          else
          {
            idata.results[RED][y][x] = 0;
            idata.results[GREEN][y][x] = 0;
            idata.results[BLUE][y][x] = 0;
          }
        }
      }
      if (writeBMPfile(argv[2], &idata) > 0)
        printf("コピー先ファイル%sに保存できませんでした\n", argv[2]);
    }
  }
}
int isOutofBounds(int a, int b, int max)
{
  if ((a < 0 || b < 0) || (a > max - 1 || b > max - 1))
    return 1;
  else
    return 0;
}