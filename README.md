# High-Performance Computational Physics

This repository contains numerical methods and stochastic simulations implemented in pure C. The focus is on low-level algorithmic efficiency, custom memory management, and deterministic/stochastic modeling for physical systems.

## Architecture

### 1. Differential Equations
* **Harmonic Kinematics:** Deterministic integration of physical systems using Euler and Verlet integration schemes.
* **Heat Diffusion:** Finite Difference Method (FDM) applied to the heat equation utilizing Forward Time, Centered Space (FTCS) algorithms.

### 2. Numerical Integration
* **Riemann Sum Convergence:** Deterministic area approximation under complex curves, demonstrating convergence scaling as N approaches infinity.

### 3. Monte Carlo Methods
* **Custom PRNGs:** Implementation of Pseudo-Random Number Generators using low-level bitwise XOR operations for maximum sampling efficiency.
* **Statistical Analysis:** Rejection sampling for custom probability distributions and statistical variance analysis over massive iterative sets.
* **State Transitions:** Core implementation of the Metropolis-Hastings algorithm.

### 4. Stochastic Optimization
* **Simulated Annealing:** Applied to spatial optimization (TSP heuristics), balancing exploration and exploitation through a dynamic cooling schedule ($\beta$).
* **Linear Solvers:** Probabilistic, random-walk solvers for linear algebra systems utilizing energy-residual minimization.

## Technical Details
* **Language:** C 
* **Data Integration:** All simulations output structured `.csv` data, designed for seamless ingestion into Python/Pandas data science pipelines.
* **Design Philosophy:** Zero external mathematical libraries beyond the standard `<math.h>`, prioritizing raw computational speed and explicit algorithmic control.
