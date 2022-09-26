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
  int h[NUM], h_results[NUM];
  int nm[NUM][NUM];
  int cnt[NUM][NUM];
  int mean,dist,bright;
  int n,k,x, y;

  if (argc < 3) {
    printf("使用法：%s 入力.bmp 出力.bmp\n", argv[0]);
  }
  else{
    if (readBMPfile(argv[1], &idata) > 0)
    printf("指定入力ファイル%sが見つかりません\n", argv[1]);
      else {
      printf("%d\n",idata.color_depth);
      for (y = 0; y < idata.height; y++) {
		    for (x = 0; x < idata.width; x++) {
	  	    bright = idata.source[RED][y][x];
	  	    nm[bright][bright]++, h[bright]++;
		    }
      }
      mean = idata.height * idata.width / idata.color_depth;
        for (x = 0; x < NUM; x++) {
	        n = 0;
	        for (k = 0; k < NUM; k++) {
	          n += nm[k][x];
	        }

	    if (n < mean) {
	      for (y = 1; y < NUM ; y++) {
	        if(n >= mean)
            break;
        if (nm[x + y][x + y] != 0) {
	        if (n + nm[x + y][x + y] <= mean) {
		        nm[x + y][x] = nm[x + y][x + y];
		        n += nm[x + y][x + y];
		        nm[x + y][x + y] = 0;
	        }
      
	        else if (n + nm[x + y][x + y] > mean) {
		        dist = mean - n;
		        nm[x + y][x] = dist;
		        n += dist;
		        nm[x + y][x + y] -= dist;
	        }
	      }
	    }
	  }
	    else if (n > mean) {
	      y = NUM - 1;
	      for (y = NUM - 1; y >= 0; y--) {
	        if(n <= mean) 
            break;
          if (nm[y][x] != 0) {
	          if (n - nm[y][x] > mean) {
		          nm[y][x + 1] = nm[y][x];
		          n -= nm[y][x];
		          nm[y][x] = 0;
	        }
	        else if (n - nm[y][x] <= mean) {
		        dist = n - mean;
		        nm[y][x + 1] = dist;
		        n -= dist;
		        nm[y][x] -= dist;
	        }
	      }
	    }
	  }
  }


      for (y = idata.height - 1; y >= 0; y--) {
	      for (x = 0; x < idata.width; x++) {
	        bright = idata.source[RED][y][x];
	          for (k = 0; k < NUM; k++) {
	            if (cnt[bright][k] < nm[bright][k]) {
	              idata.results[RED][y][x] = k;
                idata.results[GREEN][y][x]= k; 
                idata.results[BLUE][y][x] = k;
	              cnt[bright][k]++;
	              break;
	            }
	          }
	        if (k == NUM){
	          idata.results[RED][y][x] = bright;
            idata.results[GREEN][y][x] =bright; 
            idata.results[BLUE][y][x] = bright;
        }
      }
    }
  }

    if (writeBMPfile(argv[2], &idata) > 0) {
      printf("出力ファイル%sに保存できませんでした\n", argv[2]);
    }
  }
}
