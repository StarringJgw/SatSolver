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
#include "CnfParser.h"
typedef myList<myList<int >> Formula;
typedef myList<int> Clause;
typedef Clause *Iterator;
typedef myVector<int> Solution;


typedef int Board[9][9];

class SudokuSolver {
private:
    SatSolver satSolver;
    CnfParser cnfParser;
public:
    Formula formula;
    int answerBoard[9][9];
    int questionBoard[9][9];
    int playerBoard[9][9];

    int ShowBoard(int type) {
        if (type == 1) {
            cout << endl << "------------------------" << endl;
            for (int i1 = 0; i1 < 9; i1++) {
                for (int i2 = 0; i2 < 9; i2++) {
                    if (answerBoard[i1][i2] == 0)
                        cout << "  ";
                    else
                        cout << answerBoard[i1][i2] << " ";
                }
                if (i1 % 3 == 2)
                    cout << endl << "----------------------";
                cout << endl;
            }
            cout << endl << "------------------------" << endl;
            fflush(stdout);
        } else if (type == 0) {
            cout << endl << "------------------------" << endl;
            for (int i1 = 0; i1 < 9; i1++) {
                for (int i2 = 0; i2 < 9; i2++) {
                    if (questionBoard[i1][i2] == 0)
                        cout << "_";
                    else
                        cout << questionBoard[i1][i2];
                    if (i2 % 3 == 2)
                        cout << "|";
                    else
                        cout << " ";
                }
                if (i1 % 3 == 2)
                    cout << endl << "----------------------";
                cout << endl;
            }
            cout << endl << "------------------------" << endl;
            fflush(stdout);
        } else if (type == -1) {
            cout << endl << "------------------------" << endl;
            for (int i1 = 0; i1 < 9; i1++) {
                for (int i2 = 0; i2 < 9; i2++) {
                    if (playerBoard[i1][i2] == 0)
                        cout << "_";
                    else
                        cout << playerBoard[i1][i2];
                    if (i2 % 3 == 2)
                        cout << "|";
                    else
                        cout << " ";
                }
                if (i1 % 3 == 2)
                    cout << endl << "----------------------";
                cout << endl;
            }
            cout << endl << "------------------------" << endl;
        }


        return 0;
    }

    SudokuSolver() {
        srand((unsigned) time(NULL));


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
//        cout << formula.Size() << endl;
        //ensure each row
        for (int row = 1; row <= 9; row++) {
            int currentNum = (row - 1) * 81 + 1;
            for (int i = 1; i <= 9; currentNum++, i++) {
                int current[9] = {currentNum, currentNum + 9, currentNum + 18, currentNum + 27, currentNum + 36,
                                  currentNum + 45, currentNum + 54, currentNum + 63, currentNum + 72};
                PushBasicRule(current);
            }
        }
//        cout << formula.Size() << endl;
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
//        cout << formula.Size() << endl;
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

    void Reset() {
        for (int i1 = 0; i1 < 9; i1++) {
            for (int i2 = 0; i2 < 9; i2++) {
                answerBoard[i1][i2] = 0;
                playerBoard[i1][i2] = 0;
                questionBoard[i1][i2] = 0;
            }
        }
    }

    bool fill(int row, int cloumn, int num) {
        if (questionBoard[row][cloumn] == 0) {
            playerBoard[row][cloumn] = num;
            return true;
        } else
            return false;
    }

    void Cheat() {
        for (int i1 = 0; i1 < 9; i1++) {
            for (int i2 = 0; i2 < 9; i2++) {
                playerBoard[i1][i2] = answerBoard[i1][i2];
            }
        }
    }

    bool submit() {
        for (int i1 = 0; i1 < 9; i1++) {
            for (int i2 = 0; i2 < 9; i2++) {
                if (playerBoard[i1][i2] != answerBoard[i1][i2]) {
                    return false;
                }

            }
        }
        return true;
    }

    void PushBasicRule(int target[9]) {
        //push rules matched to 9 limited symbol into formula set
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

    void GenerateFinal() {
        //set a new quiz and its answer into two board
        CreateAnswer();
        for (int i1 = 0; i1 < 9; i1++) {
            for (int i2 = 0; i2 < 9; i2++) {
                questionBoard[i1][i2] = answerBoard[i1][i2];
            }
        }

        int randomSeq[81];
        for (int i = 0; i < 81; i++) {
            randomSeq[i] = i;
        }
        random_shuffle(begin(randomSeq), end(randomSeq));

        for (int i = 0; i < 50; i++) {
            digHoleOpt(randomSeq[i] / 9, randomSeq[i] % 9);
        }
//        cout << "Answer:" << endl;
//        ShowBoard(1);
//        cout << "Question: " << endl;
//        ShowBoard(0);

//        cout << isValid(CreateConstraint(0));
//        ShowVector(satSolver.solutionOpt);
        for (int i1 = 0; i1 < 9; i1++) {
            for (int i2 = 0; i2 < 9; i2++) {
                playerBoard[i1][i2] = questionBoard[i1][i2];
            }
        }
        SaveSudoku();
    }

    void CreateAnswer() {
        //set a new final answer into answerBoard
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

            satSolver.Reset();
            satSolver.Solve(answer, 729);
            if (satSolver.status == true) {
//                ShowVector(satSolver.solution);
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
//                ShowBoard(1);
//                ShowVector(satSolver.solution);
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
        //turns the requirment of certain num into Dpll-symbol
        return status * 9 * entry + num;
    }

    Formula CreateConstraint(int status) {
        //create contraints with selected board,
        Formula assume = satSolver.Clone(formula);
        if (status == 1) {
            for (int i1 = 0; i1 < 9; i1++) {
                for (int i2 = 0; i2 < 9; i2++) {
                    if (answerBoard[i1][i2] != 0) {
                        AssignValue(i1 * 9 + i2, answerBoard[i1][i2], assume);
                    }
                }
            }
        } else {
            for (int i1 = 0; i1 < 9; i1++) {
                for (int i2 = 0; i2 < 9; i2++) {
                    if (questionBoard[i1][i2] != 0) {
                        AssignValue(i1 * 9 + i2, questionBoard[i1][i2], assume);
                    }
                }
            }
        }
        return assume;
    }

    void AssignValue(int entry, int num, Formula assume) {
        //assign the given entry with given number and add its rules into assume
        Clause newRule = *new Clause;
        newRule.push_back(toCode(entry, num, 1));
        assume.push_back(newRule);
        answerBoard[entry / 9][entry % 9] = num;
//        ShowBoard(1);
    }

    bool isValid(Formula target) {
        //use dpll to verify if target can be solved
        satSolver.Reset();
        satSolver.Solve(target, 729);
        return satSolver.status;
    }

    bool digHole(int row, int column) {
        //dig legal hole in [row][column]
        int num = questionBoard[row][column];
        for (int i = 1; i <= 9; i++) {
            if (i == num)
                continue;
            questionBoard[row][column] = i;
            if (isValid(CreateConstraint(0))) {
                questionBoard[row][column] = num;
                return false;
            }
        }
        questionBoard[row][column] = 0;
//        ShowBoard(0);
        return true;
    }

    bool digHoleOpt(int row, int column) {
        //dig legal hole in [row][column] with backTrace
        int num = questionBoard[row][column];
        for (int i = 1; i <= 9; i++) {
            if (i == num)
                continue;
            questionBoard[row][column] = i;
            if (backTrace(0)) {
                questionBoard[row][column] = num;
                return false;
            }
        }
        questionBoard[row][column] = 0;
//        ShowBoard(0);
        return true;
    }

    bool backTrace(int entry) {
        //start to solve the questionBoard from given entry
        if (entry == 81)
            return true;
        int row = entry / 9, column = entry % 9;
        if (questionBoard[row][column] == 0) {
            for (int i = 1; i <= 9; i++) {
                questionBoard[row][column] = i;
                if (isValidPlace(entry)) {
//                    questionBoard[row][column]=0;
                    backTrace(entry + 1);
                }
            }
            questionBoard[row][column] = 0;
        } else {
            backTrace(entry + 1);
        }
    }

    bool isValidPlace(int entry) {
        //judge if it's legal after setting entry
        if (entry == 82)
            return true;
        int row = entry / 9, column = entry % 9;
        int num = questionBoard[row][column];
        for (int i = 0; i < 9; i++) {
            if (questionBoard[row][i] == num && i != column)
                return false;
        }
        for (int i = 0; i < 9; i++) {
            if (questionBoard[i][column] == num && i != row)
                return false;
        }

        int gridRow = row / 3 * 3, gridColumn = column / 3 * 3;
        for (int i = gridRow; i < gridRow + 3; i++) {
            for (int j = gridColumn; j < gridColumn + 3; j++) {
                if (questionBoard[i][j] == num && i != row && j != column)
                    return false;
            }
        }
        return true;
    }

    void SaveSudoku() {
        Formula temp = CreateConstraint(0);
        cnfParser.outputSudoku(temp);
//        ShowBoard(0);
        Solution tempSolution = satSolver.Solve(temp, 729);
        satSolver.OutputLog();
        cnfParser.outputSolution(1, tempSolution, satSolver.time, "Sudoku");
    }

};

#endif //TESTC_SUDOKUSOLVER_H
