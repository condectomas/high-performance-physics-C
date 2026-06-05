#include <math.h>
#include <stdio.h>


void update_temperature(double T[][2], int L, double C, double C0) {
    int i, j;

    for (i = 1; i < L - 1; i++) {
        T[i][1] = C0 * T[i][0] + C * (T[i + 1][0] + T[i - 1][0]);
    }

    for (j = 1; j < L - 1; j++) {
        T[j][0] = T[j][1];
    }
}

int main() {
    int i, t, m, L = 100;
    double C, C0, dt, dx, k;
    
    double T[L][2]; 
    
    k = 0.01;
    dx = 1.0 / L;
    dt = 0.0001;
    C = k * dt / (dx * dx);
    C0 = 1 - 2 * C;
    
    T[0][1] = 10;
    T[0][0] = 10;
    T[L-1][1] = 100;
    T[L-1][0] = 100;

    for (i = 1; i < L - 1; i++) {
        T[i][1] = 0;
        T[i][0] = 0;
    }

    FILE *f;
    f = fopen("heat_diffusion.csv", "w");
    
    fprintf(f, "position,time_step,temperature\n");

    for (t = 0; t < 200000; t++) {
        update_temperature(T, L, C, C0);

        if (t % 1000 == 0) {
            for (m = 0; m < L; m++) {
                
                fprintf(f, "%d,%d,%lf\n", m, t, T[m][1]);
            }
            
        }
    }
    
    fclose(f); 
    printf("Simulation complete. Data saved to heat_diffusion.csv\n");

    return 0;
}