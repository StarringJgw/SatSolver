//
// Created by Jgw on 20/2/19.
//
#ifndef TESTC_DPLL_H
#define TESTC_DPLL_H

#include "iostream"
#include "myVector.h"
#include "myList.h"
#include "cmath"
#include "regex"

typedef myList<myList<int >> Formula;
typedef myList<int> Clause;
typedef myVector<int> Solution;

class SatSolver {
public:
    Solution solution;

    SatSolver() {
        Solution solution = *new Solution;
    }

    Formula Simplify(Formula origin, int target);

    int findSingle(Formula origin);

    bool findBlank(Formula origin);

    Formula Show(Formula origin);

    bool Dpll(Formula origin, int baseValue);

    void Open(string name) {
        localName = name;
        regex pattern(".cnf");
        realName = regex_replace(localName, pattern, "");
    }

private:
    string localName;
    string realName;
    auto
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

Formula SatSolver::Show(Formula origin) {
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

void SortSolution(Solution &solution) {
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

