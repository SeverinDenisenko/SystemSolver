//
// Created by Severin on 25.03.2022.
//

#ifndef NUMERICAL_TASK_3_SYSTEMSOLVER_H
#define NUMERICAL_TASK_3_SYSTEMSOLVER_H

#include <iostream>
#include <vector>

class SystemSolver{
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
    std::vector< std::vector<double> > A;
    std::vector<double> X;
    std::vector<double> AX;
    int n;
};

#endif //NUMERICAL_TASK_3_SYSTEMSOLVER_H
