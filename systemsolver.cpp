//
// Created by Severin on 25.03.2022.
//

#include <iostream>
#include "systemsolver.h"

SystemSolver::SystemSolver() {}
SystemSolver::~SystemSolver() {}

void SystemSolver::ReadData(FILE *DATA) {
    if(getc(DATA) != '#'){
        printf("Error: file in wrong format.");
        exit(1);
    }

    fscanf(DATA, "%d", &n);
}

void SystemSolver::WriteData(FILE *RESULT) {

}

void SystemSolver::SolveGauss() {

}

void SystemSolver::SolveIordan() {

}

void SystemSolver::SolveLeadElement() {

}

double SystemSolver::GetResidual() {
    return 0;
}
