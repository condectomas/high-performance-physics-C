#include <math.h>
#include <stdio.h>


const double SPRING_K = 3.0;
const double EQUILIBRIUM_L = 10.0;
const double SHIFT = 0.0;
const double MASS = 4.0;

const double DT = 0.01;
const int MAX_ITER = 1000;


double compute_force(double x) {
    return -SPRING_K * (x - EQUILIBRIUM_L - SHIFT);
}

int main() {
    double x_euler = SHIFT;
    double v_euler = 3.0;
    
    double x_verlet = SHIFT;
    double v_verlet = 3.0;
    
    double force, v_temp, t, e_potential, e_kinetic, e_total;


    FILE *file_euler = fopen("euler_kinematics.csv", "w");
    
    fprintf(file_euler, "time,position,velocity,kinetic_energy,potential_energy,total_energy\n");

    for (int i = 0; i < MAX_ITER; i++) {
        force = compute_force(x_euler);
        x_euler += DT * v_euler;
        v_euler += force * DT / MASS;

        e_potential = 0.5 * SPRING_K * (x_euler - EQUILIBRIUM_L - SHIFT) * (x_euler - EQUILIBRIUM_L - SHIFT);
        e_kinetic = 0.5 * MASS * v_euler * v_euler;
        e_total = e_kinetic + e_potential;
        t = i * DT;

        
        fprintf(file_euler, "%lf,%lf,%lf,%lf,%lf,%lf\n", t, x_euler, v_euler, e_kinetic, e_potential, e_total);
    }
    fclose(file_euler);

 
    FILE *file_verlet = fopen("verlet_kinematics.csv", "w");
    fprintf(file_verlet, "time,position,velocity,kinetic_energy,potential_energy,total_energy\n");

    for (int i = 0; i < MAX_ITER; i++) {
        force = compute_force(x_verlet);
        v_temp = v_verlet + 0.5 * force * DT / MASS;
        x_verlet += v_temp * DT;
        
        force = compute_force(x_verlet);
        v_verlet = v_temp + 0.5 * force * DT / MASS;

        e_potential = 0.5 * SPRING_K * (x_verlet - EQUILIBRIUM_L - SHIFT) * (x_verlet - EQUILIBRIUM_L - SHIFT);
        e_kinetic = 0.5 * MASS * v_verlet * v_verlet;
        e_total = e_kinetic + e_potential;
        t = i * DT;

        fprintf(file_verlet, "%lf,%lf,%lf,%lf,%lf,%lf\n", t, x_verlet, v_verlet, e_kinetic, e_potential, e_total);
    }
    fclose(file_verlet);

    printf("Simulation complete. Outputs saved to 'euler_kinematics.csv' and 'verlet_kinematics.csv'.\n");

    return 0;
}
