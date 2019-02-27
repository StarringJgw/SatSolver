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
        sudokuSolver.GenerateFinal();
    }

    void Start() {
        cout << "Welcome" << endl;
        cout << "1.Sudoku Game" << endl;
        cout << "2.Solve SAT" << endl;
        int status;
        cin >> status;
        if (status == 1) {
            cout << "Question: " << endl;
            sudokuSolver.ShowBoard(0);
        }
    }

};

#endif //TESTC_INTERFACE_H
