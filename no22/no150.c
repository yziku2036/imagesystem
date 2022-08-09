/*
This program maked by j17407.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EPS .00001
#define rand_range(min,max) (min)+(rand())%((max)-(min)+(1))
typedef struct {
	double real;
	double imag;
}complex;
void DFT(complex x[], int N, FILE* fp) {
	double re = 0, im = 0;
	for (int k = 0; k < N; k++) {
		re = 0;
		im = 0;
		for (int n = 0; n < N; n++) {
			re += x[n].real * cos(-2 * 3.14159265 * k * n / N) - x[n].imag * sin(-2 * 3.14159265 * k * n / N);
			im += x[n].real * sin(-2 * 3.14159265 * k * n / N) + x[n].imag * cos(-2 * 3.14159265 * k * n / N);
		}
		re /= N;
		im /= N;
		if (fabs(re) < EPS) re = fabs(re);
		if (fabs(im) < EPS) im = fabs(im);
		fprintf(fp, "%3d:%8.4f,%8.4f,%8.4f\n", k, re, im, sqrt(re * re + im * im));
	}
}
int main(int argc, char* argv[])
{
	complex x[256];
	if (argc > 3 || argc < 3) {
		printf("./a.out in21-?.txt ans21-?.txt\n");
		return 0;
	}
	else {
		FILE* fp;
		FILE* fo;
		fp = fopen(argv[1], "r");
		fo = fopen(argv[2], "w");
		int N;
		fscanf(fp, "%d", &N);
		fgetc(fp);
		for (int i = 0; i < N; i++) {
			x[i].real = x[i].imag = 0;
			fscanf(fp, "%lf", &x[i].real);
			char c = fgetc(fp);
			if (c == '+' || c == '-') {
				fscanf(fp, "%lf", &x[i].imag);
				fgetc(fp);
			}
		}

        
		for(int i=0;i<N;i++){
			printf("re=%lf\n",x[i].real);
			printf("im=%lf\n",x[i].imag);			
}
		fclose(fp);
		fprintf(fo, "j17407\n");

		DFT(x, N, fo);
		fclose(fo);
	}
	return 0;
}
