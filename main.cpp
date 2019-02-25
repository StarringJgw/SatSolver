#include "iostream"
//#include "referVector.h"
#include "myVector.h"
#include "myList.h"
#include "vector"
#include "memory"
#include "fstream"
#include "Dpll.h"
#include "chrono"
#include "CnfParser.h"
#include "regex"
//#include "algorithm"
using namespace std;


int main(void) {
    auto satSolver = *new SatSolver;
    auto cnfParser = *new CnfParser;

    Formula formula = cnfParser.readCnf("Base_B1.cnf");
    Solution solution = satSolver.Solve(formula);
    cnfParser.outputSolution(satSolver.status, solution, satSolver.time);

    return 0;
}