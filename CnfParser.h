//
// Created by Jgw on 22/2/19.
//

#ifndef TESTC_CNFPARSER_H
#define TESTC_CNFPARSER_H

#include "myVector.h"
#include "myList.h"
#include "fstream"
#include "iostream"
#include "cmath"

typedef myList<myList<int >> Formula;
typedef myList<int> Clause;
typedef myVector<int> Solution;

Formula readCNF(string target) {
    fstream localFile;
    localFile.open(target, ios::in);
    Formula newFormula;
    for (; !localFile.eof();) {
        int newSymbol;
        localFile >> newSymbol;
//        string c("c"),p("p");
        if (localFile.fail()) {
            localFile.clear();
            localFile.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        Clause newClause;
//        localFile >> newSymbol;
        for (; newSymbol != 0;) {
            newClause.push_back(newSymbol);
            localFile >> newSymbol;
        }
        newFormula.push_back(newClause);
        cout << "";
    }
    localFile.close();
    return newFormula;
}

void outputSolution(int status, string target, double time) {
    fstream localFile;
    localFile.open(target, ios::out);
    localFile << "s " << status << endl;
    localFile << "v" << endl;
    localFile << "t " << time << endl;

}

void outputSolution(Solution solution, string target, double time) {
    fstream localFile;
    localFile.open(target, ios::out);
    localFile << "s 1" << endl;
    localFile << "v ";
    for (int i = 0, size = solution.Size(), absNum = 1;;) {
        if (i < size) {
            if (abs(solution[i]) > absNum) {
                localFile << absNum << " ";
                absNum++;
                continue;
            } else {
                localFile << solution[i] << " ";
                i++;
                absNum++;
                continue;
            }
        } else
            break;

    }
    localFile << endl;
    localFile << "t " << time << endl;
}

#endif //TESTC_CNFPARSER_H
