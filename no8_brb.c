/*
  This program maked by j17407.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "def.h"
#include "var.h"
#include "bmpfile.h"
#define NUM 256

int main(int argc, char* argv[])
{
  imgdata idata;
  static int h[NUM], h_results[NUM], dp[NUM];
  static int nm[NUM][NUM];
  static int cnt[NUM][NUM];
  static int m, n, d, k, g, sum, tmp, x, y, depth;


  if (argc < 3) {
    printf("使用法：%s 入力.bmp 出力.bmp\n", argv[0]);
  }
  else{
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定入力ファイル%sが見つかりません\n", argv[1]);
    else {

      /* make histogram */
      for (y = 0; y < idata.height; y++) {
	for (x = 0; x < idata.width; x++) {
	  tmp = idata.source[RED][y][x];
	  nm[tmp][tmp]++, h[tmp]++;
	  dp[tmp] = 1;
	}
      }

      /*  calc  */
      for (x = 0; x < NUM; x++) {
	depth = (dp[x] == 1) ? depth + 1 : depth;
	sum += h[x];
      }

      m = 256 * 256 / 256;

      /*  processing  */
      for (x = 0; x < NUM; x++) {
	n = 0;
	for (k = 0; k < NUM; k++) n += nm[k][x];
	if (n < m) {
	  for (y = 1; (y < NUM && n < m); y++) {
	    if (nm[x + y][x + y] != 0) {
	      if (n + nm[x + y][x + y] <= m) {
		nm[x + y][x] = nm[x + y][x + y];
		n += nm[x + y][x + y];
		nm[x + y][x + y] = 0;
	      }
	      else if (n + nm[x + y][x + y] > m) {
		d = m - n;
		nm[x + y][x] = d;
		n += d;
		nm[x + y][x + y] -= d;
	      }
	    }
	  }
	}
	else if (n > m) {
	  y = NUM - 1;
	  for (y = NUM - 1; (y >= 0 && n > m); y--) {
	    if (nm[y][x] != 0) {
	      if (n - nm[y][x] > m) {
		nm[y][x + 1] = nm[y][x];
		n -= nm[y][x];
		nm[y][x] = 0;
	      }
	      else if (n - nm[y][x] <= m) {
		d = n - m;
		nm[y][x + 1] = d;
		n -= d;
		nm[y][x] -= d;
	      }
	    }
	  }
	}
      }

      /*  answer  */
      for (y = idata.height - 1; y >= 0; y--) {
	for (x = 0; x < idata.width; x++) {
	  g = idata.source[RED][y][x];
	  for (k = 0; k < NUM; k++) {
	    if (cnt[g][k] < nm[g][k]) {
	      idata.results[RED][y][x] = idata.results[GREEN][y][x] = idata.results[BLUE][y][x] = k;
	      cnt[g][k]++;
	      break;
	    }
	  }
	  if (k == NUM)
	    idata.results[RED][y][x] = idata.results[GREEN][y][x] = idata.results[BLUE][y][x] = g;
	}
      }
    }

    if (writeBMPfile(argv[2], &idata) > 0) {
      printf("出力ファイル%sに保存できませんでした\n", argv[2]);
    }
  }
}
