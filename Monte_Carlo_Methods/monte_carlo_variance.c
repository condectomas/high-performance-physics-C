#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NormRANu (2.3283063671E-10F)

unsigned int irr[256];
unsigned int ir1;
unsigned char ind_ran, ig1, ig2, ig3;
float x[10000000];

void init_rand(int seed) {
    int ini, factor, sum, i;
    srand(seed);
    ini = seed;
    factor = 67397;
    sum = 7364893;
    for (i = 0; i < 256; i++) {
        ini = (ini * factor + sum);
        irr[i] = ini;
    }
    ind_ran = ig1 = ig2 = ig3 = 0;
}

float Random(void) {
    float r;
    ig1 = ind_ran - 24;
    ig2 = ind_ran - 55;
    ig3 = ind_ran - 61;
    irr[ind_ran] = irr[ig1] + irr[ig2];
    ir1 = (irr[ind_ran] ^ irr[ig3]);
    ind_ran++;
    r = ir1 * NormRANu;
    return r;
}

double my_rand(double a, double b) {
    return a + (double)Random() * (b - a);
}

void compute_mean_variance(float *x_arr, int n, float *mean, float *variance) {
    int i;
    float sum = 0, sum2 = 0;
    for (i = 0; i < n; i++) {
        sum += x_arr[i];
        sum2 += x_arr[i] * x_arr[i];
    }
    *mean = sum / n;
    *variance = ((float)n / (n - 1)) * ((sum2 / n) - (*mean * *mean));
}

void metropolis(double a, double b, double epsilon, int n_data, float data[]) {
    int i;
    double x0, w, delta, C;
    x0 = 0;

    for (i = 0; i < n_data; i++) {
        delta = my_rand(-epsilon, epsilon);
        w = my_rand(0, 1);
        C = exp(-10 * x0 * delta);

        if (C > w) {
            x0 += delta;
            if (x0 > b) x0 = x0 - delta;
            else if (x0 < a) x0 = x0 - delta;
        }
        data[i] = x0;
    }
}

int main() {
    int n = 10;
    double epsilon = 0.1, a = -2, b = 5;
    float mean, variance;

    init_rand(161616);

    FILE *f;
    f = fopen("monte_carlo_variance.csv", "w");
    fprintf(f, "N,mean,variance,std_dev\n");

    while (n <= 10000000) {
        metropolis(a, b, epsilon, n, x);
        compute_mean_variance(x, n, &mean, &variance);
        fprintf(f, "%d,%lf,%lf,%lf\n", n, mean, variance, sqrt(variance / n));
        n = n * 10;
    }
    fclose(f);

    return 0;
}

