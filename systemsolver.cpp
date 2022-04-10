//
// Created by Severin on 25.03.2022.
//

#include <iostream>
#include <cmath>
#include "systemsolver.h"

SystemSolver::SystemSolver() {}
SystemSolver::~SystemSolver()
{
    for (int i = 0; i < n; ++i)
    {
        delete[] A[i];
    }
    delete[] X;
    delete[] AX;
}

void SystemSolver::ReadData(FILE *DATA)
{
    if (getc(DATA) != '#')
    {
        printf("Error: file in wrong format.");
        exit(1);
    }

    fscanf(DATA, "%d", &n);

    A = (double **)malloc(sizeof(double *) * n);
    for (int i = 0; i < n; ++i)
    {
        A[i] = (double *)malloc(sizeof(double) * (n + 1));
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            fscanf(DATA, "%lf", &A[i][j]);
        }
    }

    for (int i = 0; i < n; ++i)
    {
        fscanf(DATA, "%lf", &A[i][n]);
    }
}

void SystemSolver::WriteData(FILE *RESULT)
{
    fprintf(RESULT, "# %d \n", n);

    for (int i = 0; i < n; ++i)
    {
        fprintf(RESULT, "%lf\n", X[i]);
    }
}

void SystemSolver::SolveGauss()
{
    X = (double *)malloc(sizeof(double) * n);

    for (int j = 0; j < n; j++)
    {
        if (A[j][j] == 0)
        {
            printf("Element (%d, %d) is 0.\n", j + 1, j + 1);
            exit(1);
        }

        if (abs(A[j][j]) < 10e-5L)
        {
            printf("Element (%d, %d) is too close to 0.\n", j + 1, j + 1);
        }

        for (int i = j + 1; i < n; i++)
        {
            double div = A[i][j] / A[j][j];

            for (int k = 0; k < n + 1; k++)
            {
                A[i][k] = A[i][k] - div * A[j][k];
            }
        }
    }

    X[n - 1] = A[n - 1][n] / A[n - 1][n - 1];

    for (int i = n - 2; i >= 0; i--)
    {
        double sum = 0;
        for (int j = i + 1; j < n; j++)
        {
            sum = sum + A[i][j] * X[j];
        }
        X[i] = (A[i][n] - sum) / A[i][i];
    }
}

void SystemSolver::SolveJordan()
{
    X = (double *)malloc(sizeof(double) * n);

    for (int j = 0; j < n; j++)
    {
        if (A[j][j] == 0)
        {
            printf("Element (%d, %d) is 0.\n", j + 1, j + 1);
            exit(1);
        }

        if (abs(A[j][j]) < 10e-5L)
        {
            printf("Element (%d, %d) is too close to 0.\n", j + 1, j + 1);
        }

        for (int i = 0; i < n; i++)
        {
            if (i != j)
            {
                double div = A[i][j] / A[j][j];
                for (int k = 0; k < n + 1; k++)
                {
                    A[i][k] = A[i][k] - div * A[j][k];
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        X[i] = A[i][n] / A[i][i];
    }
}

void SystemSolver::SolveLeadElement()
{
    X = (double *)malloc(sizeof(double) * n);

    int *x_order = (int *) malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
    {
        x_order[i] = i;
    }

    for (int j = 0; j < n; j++)
    {
        // Serch for biggest element and change order //

        int max_i = 0;
        int max_j = 0;
        double max = 0;

        for (int z = j; z < n; z++)
        {
            for (int t = z; t < n; t++)
            {
                if (abs(A[z][t]) > max)
                {
                    max = abs(A[z][t]);
                    max_i = z;
                    max_j = t;
                }
            }
        }
        
        for (int i = 0; i < n; i++)
        {
            double tmp = A[i][max_j];
            A[i][max_j] = A[i][j];
            A[i][j] = tmp;
        }
        
        double* tmp1 = A[max_i];
        A[max_i] = A[j];
        A[j] = tmp1;

        int tmp = x_order[j];
        x_order[j] = x_order[max_j];
        x_order[max_j] = tmp;

        ////////////////////////////////////////////////

        for (int i = j + 1; i < n; i++)
        {
            double div = A[i][j] / A[j][j];

            for (int k = 0; k < n + 1; k++)
            {
                A[i][k] = A[i][k] - div * A[j][k];
            }
        }
    }

    X[n - 1] = A[n - 1][n] / A[n - 1][n - 1];

    for (int i = n - 2; i >= 0; i--)
    {
        double sum = 0;
        for (int j = i + 1; j < n; j++)
        {
            sum = sum + A[i][j] * X[j];
        }
        X[i] = (A[i][n] - sum) / A[i][i];
    }

    // Restore the order of X //

    for (int i = 0; i < n; i++)
    {
        double tmp = X[i];
        X[i] = X[x_order[i]];
        X[x_order[i]] = tmp;
    }
    
    ////////////////////////////
}

double SystemSolver::GetResidual()
{
    double residual = 0;

    AX = (double *)malloc(sizeof(double) * n);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            AX[i] += X[j] * A[i][j];
        }
    }

    for (int i = 0; i < n; ++i)
    {
        AX[i] -= A[i][n];
    }

    for (int i = 0; i < n; ++i)
    {
        residual += AX[i] * AX[i];
    }

    residual = sqrt(residual);

    return residual;
}
