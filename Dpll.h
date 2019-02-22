//
// Created by Jgw on 20/2/19.
//
#ifndef TESTC_DPLL_H
#define TESTC_DPLL_H

#include "iostream"
#include "myVector.h"
#include "myList.h"
#include "cmath"

typedef myList<myList<int >> Formula;
typedef myList<int> Clause;
typedef myVector<int> Solution;

Formula Simplify(Formula origin, int target) {
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

int findSingle(Formula origin) {
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

bool findBlank(Formula origin) {
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

Formula Show(Formula origin) {
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

