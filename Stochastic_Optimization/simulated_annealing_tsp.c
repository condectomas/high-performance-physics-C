#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NormRANu (2.3283063671E-10F)
#define N 10

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

typedef struct {
    double x, y;
} Point;

Point random_point(double min, double max) {
    double x = my_rand(min, max);
    double y = my_rand(min, max);
    return (Point){.x = x, .y = y};
}

void generate_points(double min, double max, Point *coords) {
    int i;
    for (i = 0; i < N; i++) {
        coords[i] = random_point(min, max);
    }
}

void swap_order(int *order1, int *order2) {
    int i, j, k, temp;

    for (k = 0; k < N; k++) {
        order2[k] = order1[k];
    }

    i = (int)my_rand(0, N);
    if (i >= N) i = N - 1;

    j = (int)my_rand(0, N);
    if (j >= N) j = N - 1;

    temp = order2[i];
    order2[i] = order2[j];
    order2[j] = temp;
}

double distance_between_points(Point i, Point j) {
    double x = i.x - j.x;
    double y = i.y - j.y;
    return sqrt(x * x + y * y);
}

double total_distance(int *order, Point *coords) {
    int i;
    double dist = 0;

    for (i = 0; i < N - 1; i++) {
        dist += distance_between_points(coords[order[i]], coords[order[i + 1]]);
    }
    return dist;
}

int main() {
    init_rand(272313);

    double min = -10, max = 10, beta = 1.0, w;
    Point coords[N];
    int order1[N], order2[N], j;
    int iter = 1000000;

    double current_energy, new_energy, delta_e;

    generate_points(min, max, coords);

    for (int i = 0; i < N; i++) {
        order1[i] = i;
    }

    current_energy = total_distance(order1, coords);
    printf("Initial distance: %lf\n", current_energy);

    for (j = 0; j < iter; j++) {
        if (j % 10000 == 0) {
            beta += 0.1;
        }

        swap_order(order1, order2);
        new_energy = total_distance(order2, coords);
        delta_e = new_energy - current_energy;
        w = my_rand(0, 1);

        if (delta_e < 0 || exp(-beta * delta_e) > w) {
            for (int k = 0; k < N; k++) {
                order1[k] = order2[k];
            }
            current_energy = new_energy;
        }
    }

    printf("\n--- OPTIMIZATION COMPLETE ---\n");
    printf("Final optimized distance: %lf\n", current_energy);
    printf("Path order: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", order1[i]);
    }
    printf("\n");

    return 0;
}