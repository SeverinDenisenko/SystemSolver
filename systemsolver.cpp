//
// Created by Severin on 25.03.2022.
//

#include <iostream>
#include <cmath>
#include "systemsolver.h"

SystemSolver::SystemSolver() {}
SystemSolver::~SystemSolver() {}

void SystemSolver::ReadData(FILE *DATA) {
    if(getc(DATA) != '#'){
        printf("Error: file in wrong format.");
        exit(1);
    }

    fscanf(DATA, "%d", &n);

    A = new double[n*n];
    B = new double[n];
    X = new double[n];

    for (int i = 0; i < n * n; ++i) {
        fscanf(DATA, "%lf", &A[i]);
    }

    for (int i = 0; i < n; ++i) {
        fscanf(DATA, "%lf", &B[i]);
    }
}

void SystemSolver::WriteData(FILE *RESULT) {
    fprintf(RESULT, "# %d \n", n);

    for (int i = 0; i < n; ++i) {
        fprintf(RESULT, "%lf\n", X[i]);
    }
}

void SystemSolver::SolveGauss() {

}

void SystemSolver::SolveIordan() {

}

void SystemSolver::SolveLeadElement() {

}

double SystemSolver::GetResidual() {
    double residual = 0;

    AX = new double[n];

    for (int i = 0; i < n; ++i) {
        AX[i] = 0;

        for (int j = 0; j < n; ++j) {
            AX[i] += X[j] * A[j];
        }
    }

    for (int i = 0; i < n; ++i) {
        residual += AX[i] * AX[i];
    }

    residual = sqrt(residual);

    return residual;
}
