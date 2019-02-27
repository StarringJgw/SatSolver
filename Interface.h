//
// Created by Jgw on 27/2/19.
//

#ifndef TESTC_INTERFACE_H
#define TESTC_INTERFACE_H

#include "SudokuSolver.h"
#include "Dpll.h"

class App {
private:
    SudokuSolver sudokuSolver;
    SatSolver satSolver;
public:
    App() {
        sudokuSolver = *new SudokuSolver;
        satSolver = *new SatSolver;

    }
    void Start() {
        for (;;) {
            cout << "Welcome" << endl;
            cout << "1.Sudoku Game" << endl;
            cout << "2.Solve SAT" << endl;
            cout << "0.Exit" << endl;
            int status;
            cin >> status;
            if (status == 0)
                break;
            else if (status == 1) {
                sudokuSolver.Reset();
                sudokuSolver.GenerateFinal();
                cout << "Question: " << endl;
                sudokuSolver.ShowBoard(-1);
                cout << "input Row Column and Number to fill blanks,input 0 to submit,input -1 to cheat" << endl;
                int row = 0, column = 0, num = 0;
                for (;;) {
                    cin >> row;
                    if (row == 0) {
                        if (sudokuSolver.submit()) {
                            cout << "Correct!" << endl;
                            break;
                        } else {
                            cout << "Wrong!" << endl;
                            sudokuSolver.ShowBoard(-1);
                            continue;
                        }
                    } else if (row == -1) {
                        sudokuSolver.Cheat();
                        sudokuSolver.ShowBoard(-1);
                    } else {
                        cin >> column >> num;
                        if (sudokuSolver.fill(row - 1, column - 1, num)) {
                            sudokuSolver.ShowBoard(-1);
                            continue;
                        } else {
                            cout << "Invalid Input" << endl;
                            sudokuSolver.ShowBoard(-1);
                            continue;
                        }
                    }

                }


            }

        }
    }
};

#endif //TESTC_INTERFACE_H
