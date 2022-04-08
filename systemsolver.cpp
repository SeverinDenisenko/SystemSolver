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

    A = (double**)malloc(sizeof(double*) * n);
    for (int i = 0; i < n; ++i) {
        A[i] = (double*)malloc(sizeof(double) * (n + 1));
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fscanf(DATA, "%lf", &A[i][j]);
        }
    }

    for (int i = 0; i < n; ++i) {
        fscanf(DATA, "%lf", &A[i][n]);
    }
}

void SystemSolver::WriteData(FILE *RESULT) {
    fprintf(RESULT, "# %d \n", n);

    for (int i = 0; i < n; ++i) {
        fprintf(RESULT, "%lf\n", X[i]);
    }
}

void SystemSolver::SolveGauss() {
    X = (double*)malloc(sizeof(double) * n);

    for(int j = 0; j < n; j++)
    {
        if (A[j][j] == 0){
            printf("Element (%d, %d) is 0.\n", j + 1, j + 1);
            exit(1);
        }

        if (abs(A[j][j]) < 10e-5L){
            printf("Element (%d, %d) is too close to 0.\n", j + 1, j + 1);
        }

        for(int i = 0; i < n; i++)
        {
            if(i > j)
            {
                double div = A[i][j] / A[j][j];

                for(int k = 0; k < n; k++)
                {
                    A[i][k] = A[i][k] - div * A[j][k];
                }
            }
        }
    }

    X[n]=A[n - 1][n] / A[n - 1][n - 1];

    for(int i = n - 1; i >= 0; i--)
    {
        double sum = 0;
        for(int j = i; j < n; j++)
        {
            sum = sum + A[i][j] * X[j];
        }
        X[i] = (A[i][n] - sum) / A[i][i];
    }
}

void SystemSolver::SolveJordan() {
    X = (double*)malloc(sizeof(double) * n);

    for(int j = 0; j < n; j++)
    {
        if (A[j][j] == 0){
            printf("Element (%d, %d) is 0.\n", j + 1, j + 1);
            exit(1);
        }

        if (abs(A[j][j]) < 10e-5L){
            printf("Element (%d, %d) is too close to 0.\n", j + 1, j + 1);
        }

        for(int i = 0; i < n; i++)
        {
            if(i != j)
            {
                double div = A[i][j] / A[j][j];
                for(int k = 0; k < n + 1; k++)
                {
                    A[i][k] = A[i][k] - div * A[j][k];
                }
            }
        }
    }

    for(int i = 0; i < n; i++)
    {
        X[i] = A[i][n] / A[i][i];
    }
}

//TODO
void SystemSolver::SolveLeadElement() {
    X = (double*)malloc(sizeof(double) * n);

    for(int j = 0; j < n; j++)
    {
        for(int i = 0; i < n; i++)
        {
            if(i > j)
            {
                double div = A[i][j] / A[j][j];

                for(int k = 0; k < n; k++)
                {
                    A[i][k] = A[i][k] - div * A[j][k];
                }
            }
        }
    }

    X[n]=A[n - 1][n] / A[n - 1][n - 1];

    for(int i = n - 1; i >= 0; i--)
    {
        double sum = 0;
        for(int j = i; j < n; j++)
        {
            sum = sum + A[i][j] * X[j];
        }
        X[i] = (A[i][n] - sum) / A[i][i];
    }

}

double SystemSolver::GetResidual() {
    double residual = 0;

    AX = (double*)malloc(sizeof(double) * n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            AX[i] += X[j] * A[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        AX[i] -= A[i][n];
    }

    for (int i = 0; i < n; ++i) {
        residual += AX[i] * AX[i];
    }

    residual = sqrt(residual);

    return residual;
}
