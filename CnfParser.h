//
// Created by Jgw on 22/2/19.
//

#ifndef TESTC_CNFPARSER_H
#define TESTC_CNFPARSER_H

#include "myVector.h"
#include "myList.h"
#include "fstream"
#include "iostream"

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
    return newFormula;
}

#endif //TESTC_CNFPARSER_H
