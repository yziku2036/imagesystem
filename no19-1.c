#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "var.h"
#include "bmpfile.h"

#define copy_data(array1,array2,width,height) \
for(int i=0;i<height;i++){\
  for(int j=0;j<width;j++){\
    array1[RED][j][i]=array2[RED][j][i];\
  }\
}
//収縮
#define erode_4nei\
  if(i==0||j==0){\
    if(idata.source[RED][y][x]==255){\
      printf("白画素発見\n");\
      idata.cwork[RED][index_y][index_x]=255;\
    }\
  }

#define erode_8nei\
  if(idata.source[RED][y][x]==255){\
    printf("白画素発見\n");\
    idata.cwork[RED][index_y][index_x]=255;\
  }

//膨張
#define dilate_4nei\
  if(i==0||j==0){\
    if (idata.source[RED][y][x] == 0)\
    {\
      printf("黒画素発見\n");\
      idata.cwork[RED][index_y][index_x] = 0;\
    }\
  }
    
#define dilate_8nei\
  printf("i,j:%d,%d\n",i,j);\
  if (idata.source[RED][y][x] == 0)\
  {\
    printf("0画素発見\n");\
    idata.cwork[RED][index_y][index_x] = 0;\
  }
    


int isOutofIndex(int,int,int,int);

int main(int argc, char *argv[])
{
  imgdata idata;
  double c;
  int x, y;
  int index_x,index_y;
  // 例題プログラム
  // 　BMPファイルをコピーするプログラム
  if (argc < 3) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    else {

      copy_data(idata.cwork,idata.source,idata.width,idata.height)

      for(int mode=0;mode<4;mode++){
        for(int y=0;y<idata.height;y++){
          for(int x=0;x<idata.width;x++){
              printf("x,y:%d,%d\n",x,y);
              printf("val[%d][%d]=%d\n",y,x,idata.source[RED][y][x]);
              for(int i=-1;i<2;i++){
                for(int j=-1;j<2;j++){
                  index_x=x+j;
                  index_y=y+i;
                  if(!isOutofIndex(index_x,index_y,idata.width,idata.height)){
                    //8近傍のときこの下1行のコメントアウトを外すこと
                    //膨張:dilate 収縮:erode
                    if(mode==0||mode==3){
                      
                      dilate_4nei
                    }
                    else
                    {
                      
                      erode_4nei
                    }
                }
              }
          
            }
          }
        }        
        copy_data(idata.source,idata.cwork,idata.width,idata.height)
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


int isOutofIndex(int x, int y, int xmax, int ymax)
{
  if (x < 0 || y < 0 || x >= xmax || y >= ymax)
    return 1;
  else
    return 0;
}