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

    int ShowBoard() {
        cout << endl << "------------------------" << endl;
        for (int i1 = 0; i1 < 9; i1++) {
            for (int i2 = 0; i2 < 9; i2++) {
                cout << graphBoard[i1][i2] << " ";
            }
            cout << endl;
        }
        cout << endl << "------------------------" << endl;
        fflush(stdout);
        return 0;
    }

    int graphBoard[9][9];

    SudokuSolver() {

        for (int i = 0; i < 81; i++) {
            tried[i] = 0;
        }

        for (int i1 = 0; i1 < 9; i1++) {
            for (int i2 = 0; i2 < 9; i2++) {
                graphBoard[i1][i2] = 0;
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
                AssignValue(randomSeq[i], randomVal);
                cout << "";
            }
            for (int i1 = 0; i1 < 9; i1++) {
                for (int i2 = 0; i2 < 9; i2++) {
                    cout << graphBoard[i1][i2] << " ";
                }
                cout << endl;
            }

            satSolver.Reset();
            satSolver.Solve(satSolver.Clone(formula), 729);
            if (satSolver.status == true) {
                ShowVector(satSolver.solution);
                ShowBoard();
                int size = satSolver.solution.Size();
                for (int i = 0; i < size; i++) {
                    int temp = satSolver.solution[i];
                    if (temp > 0) {
                        int entry = (temp - 1) / 9;
                        int row = entry / 9;
                        int column = entry % 9;
                        int num = temp - entry * 9;

                        graphBoard[row][column] = num;
                        //have 0??
//                        for (int i1 = 0; i1 < 9; i1++) {
//                            for (int i2 = 0; i2 < 9; i2++) {
//                                cout << graphBoard[i1][i2]+1 << " ";
//                            }
//                            cout << endl;
//                        }
//                        cout <<endl<<"------------------------------"<<endl;
                    }
                }
                ShowBoard();
//                for (int i1 = 0; i1 < 9; i1++) {
//                    for (int i2 = 0; i2 < 9; i2++) {
//                        cout << graphBoard[i1][i2] << " ";
//                    }
//                    cout << endl;
//                }
                return;
            } else {
                for (int i = 0; i < 11; i++) {
                    formula.erase(formula.End());
                }
                for (int i1 = 0; i1 < 9; i1++) {
                    for (int i2 = 0; i2 < 9; i2++) {
                        graphBoard[i1][i2] = 0;
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

    void AssignValue(int entry, int num) {
        Clause newRule = *new Clause;
        newRule.push_back(toCode(entry, num, 1));
        formula.push_back(newRule);
        graphBoard[entry / 9][entry % 9] = num;
        ShowBoard();
    }

//    void AssignValue(int entry, int num){
//        Clause relatedRow=*new Clause;
//        Clause relatedColumn=*new Clause;
//        Clause relatedGrid=*new Clause;
//        for(int i=0;i<9;i++){
//            if(entry!=i)
//                relatedRow.push_back(toCode(entry-entry%9+i,num,-1));
//        }
//        formula.push_back(relatedRow);
//        for(int i=0;i<9;i++){
//            if(entry%9+i*9!=entry)
//                relatedColumn.push_back(toCode(entry%9+i*9,num,-1));
//        }
//        formula.push_back(relatedColumn);
//        {
//            int grid=3*((entry/9)/3)+(entry%9)%3-1;
//            int central=18*(grid/3)+3*(grid%3)+10;
//            relatedRow.push_back(toCode(central-10,num,-1));
//            relatedRow.push_back(toCode(central-8,num,-1));
//            relatedRow.push_back(toCode(central+10,num,-1));
//            relatedRow.push_back(toCode(central+8,num,-1));
//            formula.push_back(relatedGrid);
//        }
//    }

};

#endif //TESTC_SUDOKUSOLVER_H
