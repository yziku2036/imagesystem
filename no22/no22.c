
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define rand_range(min,max) (min)+(rand())%((max)-(min)+(1))


typedef struct {
	double re;
	double im;
}complex;


void dft(complex x[], int N, FILE* fp) {
	double re = 0, im = 0;
	double epsilon=0.00001;
  for (int i = 0; i < N; i++) {
		re = 0;
		im = 0;
		for (int j = 0; j < N; j++) {
			re += x[j].re * cos(-2 * M_PI * i * j / N) - x[j].im * sin(-2 * M_PI * i * j / N);
			im += x[j].re * sin(-2 * M_PI * i * j / N) + x[j].im * cos(-2 * M_PI * i * j / N);
		}
		re /= N;
		im /= N;
		if (fabs(re) < epsilon) re = fabs(re);
		if (fabs(im) < epsilon) im = fabs(im);
    fprintf(fp, "%3d:%8.4f,%8.4f,%8.4f\n", i, re, im, sqrt(re * re + im * im));
  }
}


int main(int argc, char* argv[])
{
	complex* comp;
  double val;
	if (argc != 3) {
		printf("Invalid Argument\n");
    printf("Usage:./a.out in22-X.txt ans22-X.txt\n");
		return 0;
	}
	else {
		FILE* fp_input;
		FILE* fp_output;
		fp_input = fopen(argv[1], "r");
		fp_output = fopen(argv[2], "w");
		int N;
		fscanf(fp_input, "%d", &N);
		comp=(complex*)malloc(sizeof(complex)*N);
    fgetc(fp_input);
		for (int i = 0; i < N; i++) {
			comp[i].re = comp[i].im = 0;
			fscanf(fp_input, "%lf", &comp[i].re);
      
			char c = fgetc(fp_input);
			if (c == '+' || c == '-') {
				fscanf(fp_input, "%lf", &comp[i].im);
				fgetc(fp_input);
			}
		}
		fclose(fp_input);
		fprintf(fp_output, "j18418\n");
		dft(comp, N, fp_output);
		fclose(fp_output);
	}
	return 0;
}
