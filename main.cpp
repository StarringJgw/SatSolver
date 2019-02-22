#include "iostream"
//#include "referVector.h"
#include "myVector.h"
#include "myList.h"
#include "vector"
#include "memory"
#include "fstream"
#include "Dpll.h"
#include "chrono"
//#include "algorithm"
using namespace std;

Solution solution = *new Solution;

bool Dpll(Formula origin, int baseValue) {
    if (baseValue != 0) {
        origin = Simplify(origin, baseValue);
        cout << "";
        solution.push_back(baseValue);
    }

    int simpleValue = 0;

    if (origin.Size() == 0)
        return true;  //empty formula--Solved
    for (auto p = origin.Start();; p = p->next) {
        auto temp = p->data.Start();
        if (temp == NULL) {
            solution.erase(solution.End());
            return false;  //empty clause--No Slution

        }
        if (temp == p->data.End()) {
            //single clause--use it to further simplify
            simpleValue = temp->data;
            return Dpll(origin, simpleValue);
            break;
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

    if (Dpll(origin, simpleValue))
        return true;
    solution.erase(solution.End());
    origin.Clear();

    return Dpll(backup, -simpleValue);
    //remain backup!?
}

auto DpllBack(Formula origin) {
    int simpleValue = findSingle(origin);
    for (; simpleValue != 0;) {
//        Simplify(origin,simpleValue);
        for (auto p = origin.Start();; p = p->next) {
            auto temp = p->data.Start();
            if (temp == NULL) {
                return 0;  //empty clause--No Slution
            }
            if (temp == p->data.End()) {
                //single clause--use it to further simplify
                simpleValue = temp->data;
                break;
            }
            if (p == origin.End()) {
                simpleValue = temp->data;
                break;
            }
        }
    }
}

Formula readCNF() {
    fstream localFile;
    localFile.open("./set/True_L1", ios::in);
    Formula newFormula;
    for (; !localFile.eof();) {
        int newSymbol;
        localFile >> newSymbol;
//        string c("c"),p("p");
        if (localFile.fail()) {
            localFile.clear();
            localFile.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        Clause newClause;
//        localFile >> newSymbol;
        for (; newSymbol != 0;) {
            newClause.push_back(newSymbol);
            localFile >> newSymbol;
        }
        newFormula.push_back(newClause);
        cout << "";
    }
    return newFormula;
}


int main(void) {
    myList<myList<int>> formula;
    formula.push_back(*(new myList<int>));
    formula.push_back(*(new myList<int>));
    formula.push_back(*(new myList<int>));
    formula.push_back(*(new myList<int>));
    formula.push_back(*(new myList<int>));

    formula[0].push_back(2);
    formula[1].push_back(-3);
    formula[1].push_back(4);
    formula[2].push_back(-5);
    formula[2].push_back(-6);
    formula[3].push_back(6);
    formula[3].push_back(5);
    formula[3].push_back(-2);
    formula[4].push_back(3);

    Formula testF;
    testF.push_back(*(new Clause));
    testF.push_back(*(new Clause));
    testF.push_back(*(new Clause));
    testF.push_back(*(new Clause));
    testF[0].push_back(1);
    testF[0].push_back(2);
    testF[1].push_back(1);
    testF[1].push_back(-2);
    testF[2].push_back(-1);
    testF[2].push_back(2);
    testF[3].push_back(-1);
    testF[3].push_back(-2);

//    Show(formula);
    auto f1 = readCNF();
//    Show(f1);
    try {
//        Show(testF);
        auto t1 = chrono::steady_clock::now();
//        time_t start=time(NULL);
        auto x = Dpll(f1, 0);
        auto t2 = chrono::steady_clock::now();
        chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double >>(t2 - t1);
        cout << x << endl << time_span.count() << endl;
//        ShowVector(solution);
    }
    catch (int status) {
        cout << status << "\tNo Solution" << endl;
        //v1
    }
}