#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int N = 1, i;
    double pi = 3.14159265, A = 0;

    FILE *f;
    f = fopen("riemann_integral_convergence.csv", "w");
    fprintf(f, "N,integral_value,error\n");

    while (N <= 100000) {
        A = 0;
        for (i = 1; i <= N; i++) {
            A = A + sin(pi * i / N) * (pi / N);
        }

        fprintf(f, "%d,%.16lf,%lf\n", N, A, (2 - A));
        N = N + 10;
    }
    fclose(f);

    return 0;
}