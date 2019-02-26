//
// Created by Jgw on 25/2/19.
//

#ifndef TESTC_SUDOKUSOLVER_H
#define TESTC_SUDOKUSOLVER_H

#include "myList.h"
#include "myVector.h"
#include "cmath"
#include "iostream"
#include "stdlib.h"
#include "time.h"
#include "algorithm"
#include "Dpll.h"
typedef myList<myList<int >> Formula;
typedef myList<int> Clause;
typedef Clause *Iterator;
typedef myVector<int> Solution;


typedef int Board[9][9];

class SudokuSolver {
private:
    int tried[81];
    SatSolver satSolver = *new SatSolver;
public:
    Formula formula;
    int answerBoard[9][9];
    int questionBoard[9][9];

    int ShowBoard(int type) {
        if (type == 1) {
            cout << endl << "------------------------" << endl;
            for (int i1 = 0; i1 < 9; i1++) {
                for (int i2 = 0; i2 < 9; i2++) {
                    cout << answerBoard[i1][i2] << " ";
                }
                cout << endl;
            }
            cout << endl << "------------------------" << endl;
            fflush(stdout);
        } else {
            cout << endl << "------------------------" << endl;
            for (int i1 = 0; i1 < 9; i1++) {
                for (int i2 = 0; i2 < 9; i2++) {
                    cout << questionBoard[i1][i2] << " ";
                }
                cout << endl;
            }
            cout << endl << "------------------------" << endl;
            fflush(stdout);
        }


        return 0;
    }



    SudokuSolver() {

        for (int i = 0; i < 81; i++) {
            tried[i] = 0;
        }

        for (int i1 = 0; i1 < 9; i1++) {
            for (int i2 = 0; i2 < 9; i2++) {
                answerBoard[i1][i2] = 0;
                questionBoard[i1][i2] = 0;
            }
        }

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

    bool IsUnique(int num) {
        int begin = (num - 1) / 9;
    }

    void GenerateFinal() {
        CreateAnswer();
        for (int i1 = 0; i1 < 9; i1++) {
            for (int i2 = 0; i2 < 9; i2++) {
                questionBoard[i1][i2] = answerBoard[i1][i2];
            }
        }
        for (int i1 = 0; i1 < 9; i1++) {
            for (int i2 = 0; i2 < 9; i2++) {
                digHole(i1, i2);
            }
        }
        ShowBoard(0);
    }

    void CreateAnswer() {
        Formula answer = satSolver.Clone(formula);
        srand((unsigned) time(NULL));
        for (;;) {
            int randomSeq[81];
            for (int i = 0; i < 81; i++) {
                randomSeq[i] = i;
            }
            random_shuffle(begin(randomSeq), end(randomSeq));

            for (int i = 0; i < 11; i++) {
                int randomVal = (rand() % 9) + 1;
                if (randomVal == 0)
                    cout << "";
                AssignValue(randomSeq[i], randomVal, answer);
                cout << "";
            }
            for (int i1 = 0; i1 < 9; i1++) {
                for (int i2 = 0; i2 < 9; i2++) {
                    cout << answerBoard[i1][i2] << " ";
                }
                cout << endl;
            }

            satSolver.Reset();
            satSolver.Solve(answer, 729);
            if (satSolver.status == true) {
                ShowVector(satSolver.solution);
                ShowBoard(1);
                int size = satSolver.solution.Size();
                for (int i = 0; i < size; i++) {
                    int temp = satSolver.solution[i];
                    if (temp > 0) {
                        int entry = (temp - 1) / 9;
                        int row = entry / 9;
                        int column = entry % 9;
                        int num = temp - entry * 9;
                        answerBoard[row][column] = num;
                    }
                }
                ShowBoard(1);
                return;
            } else {
                for (int i = 0; i < 11; i++) {
                    answer.erase(answer.End());
                }
                for (int i1 = 0; i1 < 9; i1++) {
                    for (int i2 = 0; i2 < 9; i2++) {
                        answerBoard[i1][i2] = 0;
                    }
                }
            }
        }
    }

    int toCode(int entry, int num, int status) {
        return status * 9 * entry + num;
    }

    void toNum(int code, int &entry, int &num) {
        entry = code / 9;
        num = code % 9;
    }

    void AssignValue(int entry, int num, Formula assume) {
        Clause newRule = *new Clause;
        newRule.push_back(toCode(entry, num, 1));
        assume.push_back(newRule);
        answerBoard[entry / 9][entry % 9] = num;
//        ShowBoard(1);
    }

    bool isValid(Formula target) {
        satSolver.Reset();
        satSolver.Solve(target, 729);
        return satSolver.status;
    }

    bool digHole(int row, int column) {
        int num = questionBoard[row][column];
        for (int i = 1; i <= 9; i++) {
            if (i == num)
                continue;
            questionBoard[row][column] = i;
            if (isValid(CreateConstraint())) {
                questionBoard[row][column] = num;
                return false;
            }
        }
        questionBoard[row][column] = 0;
        ShowBoard(0);
        return true;
    }

    Formula CreateConstraint() {
        Formula assume = satSolver.Clone(formula);
        for (int i1 = 0; i1 < 9; i1++) {
            for (int i2 = 0; i2 < 9; i2++) {
                if (questionBoard[i1][i2] != 0) {
                    AssignValue(i1 * 9 + i2, questionBoard[i1][i2], assume);
                }
            }
        }
        return assume;
    }
};

#endif //TESTC_SUDOKUSOLVER_H
