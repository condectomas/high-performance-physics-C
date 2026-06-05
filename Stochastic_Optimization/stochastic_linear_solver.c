#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define NormRANu (2.3283063671E-10F)
#define N 2

unsigned int irr[256];
unsigned int ir1;
unsigned char ind_ran, ig1, ig2, ig3;

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

double calculate_residual(double A[N][N], double *x, double *b) {
    int i, j, k;
    double r[N], norm = 0;

    for (k = 0; k < N; k++) {
        r[k] = 0;
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            r[i] += A[i][j] * x[j];
        }
    }

    for (k = 0; k < N; k++) {
        r[k] = r[k] - b[k];
    }

    for (i = 0; i < N; i++) {
        norm += r[i] * r[i];
    }

    return norm;
}

void random_step(double *x_old, double *x_new, double epsilon) {
    for (int i = 0; i < N; i++) {
        x_new[i] = x_old[i] + my_rand(-epsilon, epsilon);
    }
}

int main() {
    init_rand(1898309);

    double A[N][N], x1[N], x2[N], b[N], beta, epsilon, current_energy, w, C;
    int i = 0;

    epsilon = 0.1;
    beta = 1;

    A[0][0] = 1;
    A[0][1] = 1;
    A[1][0] = 1;
    A[1][1] = 2;

    b[0] = 4;
    b[1] = 7;

    x1[0] = 0;
    x1[1] = 2;

    current_energy = calculate_residual(A, x1, b);

    while (current_energy > 0.0000000001) {
        i++;

        if (i % 100 == 0) {
            beta += 0.1;
        }

        random_step(x1, x2, epsilon);
        w = my_rand(0, 1);
        C = exp(-beta * (calculate_residual(A, x2, b) - calculate_residual(A, x1, b)));

        if (C > w) {
            x1[0] = x2[0];
            x1[1] = x2[1];
        }

        current_energy = calculate_residual(A, x1, b);
    }

    printf("Final Error: %lf\n", current_energy);
    printf("x[0] = %lf\n", x1[0]);
    printf("x[1] = %lf\n", x1[1]);
    printf("Iterations: %d\n", i);

    return 0;
}