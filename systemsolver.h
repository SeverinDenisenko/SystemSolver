//
// Created by Severin on 25.03.2022.
//

#ifndef NUMERICAL_TASK_3_SYSTEMSOLVER_H
#define NUMERICAL_TASK_3_SYSTEMSOLVER_H

#include <iostream>

class SystemSolver
{
public:
    SystemSolver();
    ~SystemSolver();
    void ReadData(FILE *DATA);
    void WriteData(FILE *DATA);
    void SolveGauss();
    void SolveJordan();
    void SolveLeadElement();
    double GetResidual();

private:
    double **A;
    double **A_duplicate;
    double *X;
    double *AX;
    int n;
};

#endif // NUMERICAL_TASK_3_SYSTEMSOLVER_H
