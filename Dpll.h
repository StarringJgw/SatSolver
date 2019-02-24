//
// Created by Jgw on 20/2/19.
//
#ifndef TESTC_DPLL_H
#define TESTC_DPLL_H

#include "iostream"
#include "fstream"
#include "myVector.h"
#include "myList.h"
#include "cmath"
#include "regex"

typedef myList<myList<int >> Formula;
typedef myList<int> Clause;
typedef Clause *Iterator;
typedef myVector<int> Solution;

class SatSolver {
private:
    Formula origin;

public:
    Solution solution;

    double time;

    double timeOpt;

    bool status;

    SatSolver() {
        Solution solution = *new Solution;
    }

    Formula Simplify(Formula origin, int target);

    int findSingle(Formula origin);

    bool findBlank(Formula origin);

    void Show(Formula origin);

    Solution Solve(Formula origin);

    bool Dpll(Formula origin, int baseValue);

    bool DpllOpt(Formula origin, int baseValue);

    void Open(Formula x) {
        origin = x;
    }

    void SortSolution();
};
Formula SatSolver::Simplify(Formula origin, int target) {
    for (auto p = origin.Start();;) {
        //use p to traverse origin
        for (auto pList = p->data.Start(); pList != NULL; pList = pList->next) {
            //use plist to traverse selected clause
            if (pList->data == -target) {
                p->data.erase(pList);
                //delete current symbol
                break;
            }
            if (pList->data == target) {
                p = origin.erase(p);
                //delete current clause, already added p
                break;
            }
            if (pList == p->data.End())
                break;
        }

        if (origin.End() == NULL || p == origin.End())
            break;
        p = p->next;
    }
    return origin;
}

int SatSolver::findSingle(Formula origin) {
    for (auto p = origin.Start();;) {
        auto pFirst = p->data.Start();
        if (pFirst != NULL && pFirst == p->data.End()) {
            return pFirst->data;
        }
        if (p == origin.End()) {
            return 0;
        }
        p = p->next;
    }
}

bool SatSolver::findBlank(Formula origin) {
    for (auto p = origin.Start();;) {
        auto pFirst = p->data.Start();
        if (pFirst == NULL) {
            return true;
        }
        if (p == origin.End()) {
            return false;
        }
        p = p->next;
    }
}

void SatSolver::Show(Formula origin) {
    cout << "--------------------------------" << endl;
    for (int i = 0; i < origin.Size(); i++) {
        for (auto p = origin[i].Start();; p = p->next) {
            if (p == NULL) {
                cout << "none" << endl;
            } else
                cout << p->data << "\t";
            if (p == origin[i].End())
                break;
        }
        cout << endl;
    }
    cout << endl;
    fflush(stdout);
}

Solution SatSolver::Solve(Formula origin) {
    auto backup = *(new Formula);
    for (auto p = origin.Start();; p = p->next) {
        auto tempClause = *(new Clause);
        for (auto pList = p->data.Start(), pListEnd = p->data.End(); pList != NULL; pList = pList->next) {
            tempClause.push_back(pList->data);
            if (pList == pListEnd) {
                break;
            }
        }
        backup.push_back(tempClause);
        if (p == origin.End()) {
            break;
        }
    }
    auto t1 = chrono::steady_clock::now();
    status = DpllOpt(origin, 0);
    auto t2 = chrono::steady_clock::now();
    Dpll(backup, 0);
    auto t3 = chrono::steady_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double >>(t2 - t1);
    timeOpt = time_span.count();
    time_span = chrono::duration_cast<chrono::duration<double >>(t3 - t2);
    time = time_span.count();
    cout << status << endl << "TimeOptimize(s): " << timeOpt << endl;
    cout << "TimeOrign(s): " << time << endl;
    cout << "Rate: " << (time - timeOpt) / time << endl;

    if (status == 0)
        return {};
    else if (status == 1) {
        SortSolution();
        return solution;
    }
    return {};
}

bool SatSolver::Dpll(Formula origin, int baseValue) {
    if (baseValue != 0) {
        origin = Simplify(origin, baseValue);
        cout << "";
//        solution.push_back(baseValue);
    }

    int simpleValue = 0;

    if (origin.Size() == 0) {
//        solution.push_back(baseValue);
        return true;  //empty formula--Solved
    }
    for (auto p = origin.Start();; p = p->next) {
        auto temp = p->data.Start();
        if (temp == NULL) {
//            solution.erase(solution.End());
            return false;  //empty clause--No Slution

        }
        if (temp == p->data.End()) {
            //single clause--use it to further simplify
            simpleValue = temp->data;
            if (Dpll(origin, simpleValue)) {
                solution.push_back(simpleValue);
                return true;
            } else
                return false;
//            break;
        }
        if (p == origin.End()) {
            simpleValue = temp->data;
            break;
        }
    }
    auto backup = *(new Formula);
    for (auto p = origin.Start();; p = p->next) {
        auto tempClause = *(new Clause);

        for (auto pList = p->data.Start(), pListEnd = p->data.End(); pList != NULL; pList = pList->next) {
            tempClause.push_back(pList->data);
            if (pList == pListEnd) {
                break;
            }
        }
        backup.push_back(tempClause);
        if (p == origin.End()) {
            break;
        }
    }

    if (Dpll(origin, simpleValue)) {
        solution.push_back(simpleValue);
        return true;
    }
//    solution.erase(solution.End());
    origin.Clear();

    if (Dpll(backup, -simpleValue)) {
        solution.push_back(-simpleValue);
        return true;
    }
    return false;
    //remain backup!?
}

bool SatSolver::DpllOpt(Formula origin, int baseValue) {
    if (baseValue != 0) {
        origin = Simplify(origin, baseValue);
        cout << "";
//        solution.push_back(baseValue);
    }

    int simpleValue = 0;

    if (origin.Size() == 0) {
//        solution.push_back(baseValue);
        return true;  //empty formula--Solved
    }
    auto p = origin.Start();
    bool checkDouble = 0;
    int doubleVal = 0;
    for (;; p = p->next) {
        auto temp = p->data.Start();

        if (temp == NULL) {
//            solution.erase(solution.End());
            return false;  //empty clause--No Slution

        }
        if (temp == p->data.End()) {
            //single clause--use it to further simplify
            simpleValue = temp->data;
            if (DpllOpt(origin, simpleValue)) {
                solution.push_back(simpleValue);
                return true;
            } else
                return false;
//            break;
        }

        if (checkDouble == 0) {
            checkDouble = 1;
            if (p->data.Start()->next->next == p->data.End()) {
                doubleVal = p->data.Start()->data;
            }

        }
        if (p == origin.End()) {
            if (doubleVal != 0)
                simpleValue = doubleVal;
            else
                simpleValue = temp->data;
            break;
        }
    }
    auto backup = *(new Formula);
    for (auto p = origin.Start();; p = p->next) {
        auto tempClause = *(new Clause);

        for (auto pList = p->data.Start(), pListEnd = p->data.End(); pList != NULL; pList = pList->next) {
            tempClause.push_back(pList->data);
            if (pList == pListEnd) {
                break;
            }
        }
        backup.push_back(tempClause);
        if (p == origin.End()) {
            break;
        }
    }

    if (DpllOpt(origin, simpleValue)) {
        solution.push_back(simpleValue);
        return true;
    }
//    solution.erase(solution.End());
    origin.Clear();

    if (DpllOpt(backup, -simpleValue)) {
        solution.push_back(-simpleValue);
        return true;
    }
    return false;
    //remain backup!?
}

template<class T>
int ShowVector(myVector<T> target) {
    for (auto p = target.Start();;) {
        cout << *p << " ";
        if (p == target.End())
            break;
        p++;
    }
    fflush(stdout);
    return 1;
}

void SatSolver::SortSolution() {
    for (int flag = 1; flag != 0;) {
        flag = 0;
        for (int i = 0; i < solution.Size() - 1; i++) {
            if (abs(solution[i]) > abs(solution[i + 1])) {
                solution[i] = solution[i + 1] + solution[i];
                solution[i + 1] = solution[i] - solution[i + 1];
                solution[i] = solution[i] - solution[i + 1];
                flag = 1;
            }
        }
    }
}

#endif //TESTC_DPLL_H

