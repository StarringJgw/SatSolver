//
// Created by Jgw on 25/2/19.
//

#ifndef TESTC_SUDOKUSOLVER_H
#define TESTC_SUDOKUSOLVER_H

#include "myList.h"
#include "myVector.h"

typedef myList<myList<int >> Formula;
typedef myList<int> Clause;
typedef Clause *Iterator;
typedef myVector<int> Solution;


typedef int Board[9][9];

class Sudoku {
private:
    Formula formula;
public:
    Sudoku() {
        formula = *new Formula;
    }

    Formula PushBasicRule(int target[9]) {
        for (int i = 0; i < 9; i++) {
            for (int i1 = i + 1; i1 < 9; i1++) {
                Clause temp = *new Clause;
                temp.push_back(-target[i]);
                temp.push_back(-target[i1]);
                formula.push_back(temp);
            }
        }
    }
};

#endif //TESTC_SUDOKUSOLVER_H
