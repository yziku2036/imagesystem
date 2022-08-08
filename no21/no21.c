#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "def550.h"
#include "var.h"
#include "bmpfile.h"

void binarization_img(imgdata*);

//類似度
int similar(imgdata* idata,imgdata* template,int y,int x);
//相関係数correlation coefficient
double cor_coe(imgdata* idata,imgdata* template,int y,int x);
//距離
int distance(imgdata* idata,imgdata* template,int y,int x);

int writecutimage(imgdata idata,imgdata template,int y,int x,char* string);

int main(int argc, char *argv[])
{
  imgdata idata,template;
  double c;
  int x, y;
  int i,j;
  int k,l;
  int f_ave=0;
  int g_ave=0;

  double rval;
  int sval;
  int dval;

  double rmax;//相関係数の最小値0より小さくする
  int smax;//類似度の最大値より小さくする
  int dmin;//距離の最小値0より大きくする

  int rcoord[2];
  int scoord[2];
  int dcoord[2];

  char rname[]="ans21-1r.bmp";
  char sname[]="ans21-1s.bmp";
  char dname[]="ans21-1d.bmp";

  // 例題プログラム
  // 　BMPファイルをコピーするプログラム
  if (argc < 4) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    if (readBMPfile(argv[2], &template) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[2]);
    
    else {
    /* 例題：コピーするプログラム */
      binarization_img(&idata);
      binarization_img(&template);
      printf("Binarization Completed\n");
      rmax=cor_coe(&idata,&template,0,0);
      smax=similar(&idata,&template,0,0);
      dmin=distance(&idata,&template,0,0);
      //template(「文字」の画像)のサイズを引くことですべての元画像の領域に対して
      //「文字」を示す画像を配置して比較する処理をする
      //左上からの処理をするためにyを反転(普通に0から始めると左下からになってしまう)
      for(x=0;x<idata.height-template.height;x++){
        for(y=0;y<idata.width-template.width;y++){
          
          
          rval=cor_coe(&idata,&template,y,x);
          sval=similar(&idata,&template,y,x);
          dval=distance(&idata,&template,y,x);
          if(rmax<rval){
            rmax=rval;
            rcoord[0]=x;
            rcoord[1]=y;
            printf("rmax updated to %d at %d,%d\n",rval,x,y);
          }
          if(smax<sval){
            smax=sval;
            scoord[0]=x;
            scoord[1]=y;
            printf("smax updated to %d at %d,%d\n",smax,x,y);
          }
          if(dmin>dval){
            dmin=dval;
            dcoord[0]=x;
            dcoord[1]=y;
            printf("dmin updated to %d at %d,%d\n",dmin,x,y);
          }
        }
      }
      //if (writeBMPfile(argv[3], &idata) > 0)
      //printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);
      printf("File Writing\n");
      writecutimage(idata,template,rcoord[1],rcoord[0],rname);
      writecutimage(idata,template,scoord[1],scoord[0],sname);
      writecutimage(idata,template,dcoord[1],dcoord[0],dname);
      printf("Program Finished Succesfully\n");
    }
  }
}


void binarization_img(imgdata* img){
  int i,j;
  for(i=0;i<img->height;i++){ 
    for(j=0;j<img->width;j++){
      if(img->source[RED][i][j]==255&&img->source[GREEN][i][j]==255&&img->source[BLUE][i][j]==255){
        img->cwork[RED][i][j]=0;
      }
      else{
        img->cwork[RED][i][j]=1;
      }
      }
    }
  return;
}
//R(i,j)
double cor_coe(imgdata* idata,imgdata* template,int y,int x){
  int a=0;
  int b=0;
  int c=0;
  double ret;
  for(int i=0;i<template->height;i++){
    for(int j=0;j<template->width;j++){
      a+=idata->cwork[RED][y+i][x+j] * template->cwork[RED][i][j];
      b+=idata->cwork[RED][y+i][x+j] * idata->cwork[RED][y+i][x+j];
      c+=template->cwork[RED][i][j] * template->cwork[RED][i][j];
    }
  }
  ret=a/(sqrt((double)b)*sqrt((double)c));
  return ret;
}
//s(i,j)
int similar(imgdata* idata,imgdata* template,int y,int x){
  int ret=0;
  for(int i=0;i<template->height;i++){
    for(int j=0;j<template->width;j++){
      ret+=idata->cwork[RED][y+i][x+j] * template->cwork[RED][i][j];
    }
  }
  return ret;
}
int distance(imgdata* idata,imgdata* template,int y,int x){
  int ret=0;
  for(int i=0;i<template->height;i++){
    for(int j=0;j<template->width;j++){
      ret+=abs(idata->cwork[RED][y+i][x+j] - template->cwork[RED][i][j]);
    }
  }
  return ret;
}

int writecutimage(imgdata idata,imgdata template,int y,int x,char* string){
  for(int i=0;i<template.height;i++){
    for(int j=0;j<template.width;j++){
      template.results[RED][i][j]=idata.source[RED][y+i][x+j];
      template.results[GREEN][i][j]=idata.source[GREEN][y+i][x+j];
      template.results[BLUE][i][j]=idata.source[BLUE][y+i][x+j];
    }
  }
  printf("(x,y)=(%d,%d)\n",x,y);
  if(writeBMPfile(string,&template)>0){
    printf("ファイル%sの保存に失敗しました",string);
    return -1;
  }
}