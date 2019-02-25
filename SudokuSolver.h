//
// Created by Jgw on 25/2/19.
//

#ifndef TESTC_SUDOKUSOLVER_H
#define TESTC_SUDOKUSOLVER_H

#include "myList.h"
#include "myVector.h"
#include "cmath"
#include "iostream"
typedef myList<myList<int >> Formula;
typedef myList<int> Clause;
typedef Clause *Iterator;
typedef myVector<int> Solution;


typedef int Board[9][9];

class SudokuSolver {
private:
public:
    Formula formula;

    SudokuSolver() {
        formula = *new Formula;
        //ensure each entry have one number
        for (int i = 1; i <= 729; i = i + 9) {
            int current[9] = {i, i + 1, i + 2, i + 3, i + 4, i + 5, i + 6, i + 7, i + 8};
            PushBasicRule(current);
        }
        cout << formula.Size() << endl;
        //ensure each row
        for (int row = 1; row <= 9; row++) {
            int currentNum = (row - 1) * 81 + 1;
            for (int i = 1; i <= 9; currentNum++, i++) {
                int current[9] = {currentNum, currentNum + 9, currentNum + 18, currentNum + 27, currentNum + 36,
                                  currentNum + 45, currentNum + 54, currentNum + 63, currentNum + 72};
                PushBasicRule(current);
            }
        }
        cout << formula.Size() << endl;
        //ensure each column
        for (int column = 1; column <= 9; column++) {
            int currentNum = (column - 1) * 9 + 1;
            for (int i = 1; i <= 9; currentNum++, i++) {
                int current[9] = {currentNum, currentNum + 81, currentNum + 81 * 2, currentNum + 81 * 3,
                                  currentNum + 81 * 4, currentNum + 81 * 5, currentNum + 81 * 6, currentNum + 81 * 7,
                                  currentNum + 81 * 8};
                PushBasicRule(current);
            }
        }
        cout << formula.Size() << endl;
        //ensure each grid
        for (int grid = 1; grid <= 9; grid++) {
            int currentNum = ((grid - 1) / 3) * 243 + ((grid - 1) % 3) * 27 + 1;
            for (int i = 1; i <= 9; currentNum++, i++) {
                int current[9] = {currentNum, currentNum + 9, currentNum + 18, currentNum + 81, currentNum + 9 + 81,
                                  currentNum + 18 + 81, currentNum + 81 * 2, currentNum + 9 + 81 * 2,
                                  currentNum + 18 + 81 * 2};
                PushBasicRule(current);
            }
        }
    }

    void PushBasicRule(int target[9]) {
        Clause least = *new Clause;
        for (int i = 0; i < 9; i++) {
            least.push_back(target[i]);
            for (int i1 = i + 1; i1 < 9; i1++) {
                Clause temp = *new Clause;
                temp.push_back(-target[i]);
                temp.push_back(-target[i1]);
                formula.push_back(temp);
            }
        }
        formula.push_back(least);
    }
};

#endif //TESTC_SUDOKUSOLVER_H
