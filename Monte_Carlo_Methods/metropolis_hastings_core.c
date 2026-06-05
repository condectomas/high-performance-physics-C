#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define NormRANu (2.3283063671E-10F)

unsigned int irr[256];
unsigned int ir1;
unsigned char ind_ran, ig1, ig2, ig3;

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

void compute_histogram(double data[], double hist[], int n_data, int n_intervals) {
    double max, min, delta;
    int i, valor;
    max = data[0];
    min = data[0];
    
    for (i = 0; i < n_intervals; i++) hist[i] = 0.0;
    
    for (i = 0; i < n_data; i++) {
        if (data[i] > max) max = data[i];
        else if (data[i] < min) min = data[i];
    }

    delta = (max - min) / n_intervals;

    for (i = 0; i < n_data; i++) {
        valor = (int)((data[i] - min) / delta);
        if (valor == n_intervals) valor = n_intervals - 1;
        hist[valor]++;
    }

    for (i = 0; i < n_intervals; i++) {
        hist[i] = hist[i] / n_data;
    }
}

void metropolis(double a, double b, double epsilon, int n_data, double data[]) {
    int i;
    double x0, w, delta, C;
    x0 = -9.8;

    for (i = 0; i < n_data; i++) {
        delta = my_rand(-epsilon, epsilon);
        w = my_rand(0, 1);
        C = exp(-40 * x0 * delta);

        if (C > w) {
            x0 += delta;
            if (x0 > b) x0 = x0 - delta;
            else if (x0 < a) x0 = x0 - delta;
        }
        data[i] = x0;
    }
}

int main() {
    int n_data = 100000, i, n_int = 100;
    double a = -10, b = 10, epsilon = 0.03, p;
    double data[n_data], h[n_int];

    metropolis(a, b, epsilon, n_data, data);
    compute_histogram(data, h, n_data, n_int);

    FILE *f;
    f = fopen("metropolis_distribution.csv", "w");
    fprintf(f, "probability\n");

    for (i = 0; i < n_int; i++) {
        p = h[i];
        fprintf(f, "%lf\n", p);
    }
    fclose(f);

    return 0;
}