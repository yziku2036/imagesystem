#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS .00001
typedef struct
{
  double re;
  double im;
} complex;

void dft(complex *comp, int N, FILE *fp);

int main(int argc, char *argv[])
{
  double c; 
  int x, y;
  FILE *fp_input;
  FILE *fp_output;
  int N = -1;
  // 例題プログラム
  // BMPファイルをコピーするプログラム
  fp_input = fopen(argv[1], "r");
  fp_output = fopen(argv[2], "w");
  fscanf(fp_input, "%d", &N);
  char camma = ' ';
  double val;
  complex *comp;
  comp = (complex *)malloc(N * sizeof(complex));

  if (argc < 3)
    printf("使用法：cpbmp 元データ.txt 出力ファイル名.txt\n");
  else
  {
    if (N < 0)
    {
      printf("ファイル読み込み失敗?\n");
      exit(1);  
    }
    else
    {
      for (int i = 0; i < N; i++)
      {
        comp[i].re=0.0;
        comp[i].im=0.0;
        fscanf(fp_input, "%c%lf",&camma,&val);
        comp[i].re=val;
        printf("[%d]:%lf\n", i, val);
        if (val < 0)
          comp[i].im = val;
      }
    
    for (int i = 0; i < N; i++)
    {
    //  printf("re:%lf im:%lf\n",comp[i].re,comp[i].im);
    }
    fprintf(fp_output, "j18418\n");
    dft(comp, N, fp_output);
  }
  //free(fp_input);
  //free(fp_output);
  }
  return 0;
}

void dft(complex *comp, int N, FILE *fp)
{
  double re, im;
  double ret = 0;
  for (int i = 0; i < N; i++)
  {
    re = 0;
    im = 0;
    for (int j = 0; j < N; j++)
    {
      // re += comp[j].re * cos(-2 * M_PI * i * j / N);
      // im += comp[j].im * sin(-2 * M_PI * i * j / N);
      re += comp[j].re * cos(-2 * M_PI * i * j / N) - comp[j].im * sin(-2 * M_PI * i * j / N);
      im += comp[j].re * sin(-2 * M_PI * i * j / N) + comp[j].im * cos(-2 * M_PI * i * j / N);
    }
    re /= N;
    im /= N;
    if (fabs(re) < EPS)
      re = fabs(re);
    if (fabs(im) < EPS)
      im = fabs(im);
    ret = sqrt((re * re) + (im * im));
    printf("[%d]:re=%lf im=%lf\n",i,re,im );

    fprintf(fp, "%3d:  %.4lf, %.4lf, %.4lf\n", i, re, im, ret);
  }
  return;
}
