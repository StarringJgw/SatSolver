//
// Created by Jgw on 22/2/19.
//

#ifndef TESTC_CNFPARSER_H
#define TESTC_CNFPARSER_H

#include "myVector.h"
#include "myList.h"
#include "fstream"
#include "iostream"
#include "cmath"
#include "regex"

typedef myList<myList<int >> Formula;
typedef myList<int> Clause;
typedef myVector<int> Solution;

class CnfParser {
public:
    int symbolNum;
    Formula readCnf(string target);
//    void outputSolution(int status, string target, double time);

    void outputSolution(bool status, Solution solution, double time);

    void outputSolution(bool status, Solution solution, double time, string givenName);

    void outputSudoku(Formula target);
private:
    string localName;
    string realName;

};

Formula CnfParser::readCnf(string target) {

    localName = target;
    regex pattern(".cnf");
    realName = regex_replace(localName, pattern, "");

    fstream localFile;
    localFile.open("../set/" + localName, ios::in);
    Formula newFormula;
    for (; !localFile.eof();) {
        int newSymbol;
        localFile >> newSymbol;
//        string c("c"),p("p");
        if (localFile.fail()) {
            string tempSymbol;
            localFile.clear();
            localFile >> tempSymbol;
            if (tempSymbol == "p") {
                localFile >> tempSymbol;
                localFile >> newSymbol;
                if (localFile.fail())
                    localFile.ignore(numeric_limits<streamsize>::max(), '\n');
                else
                    symbolNum = newSymbol;
            } else if (tempSymbol == "c")
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
    localFile.close();
    return newFormula;
}

//void CnfParser::outputSolution(int status, string target, double time) {
//    fstream localFile;
//    localFile.open(target, ios::out);
//    localFile << "s " << status << endl;
//    localFile << "v" << endl;
//    localFile << "t " << time << endl;
//
//}

void CnfParser::outputSolution(bool status, Solution solution, double time) {
    //use status to tell true from false
    if (status == 1) {
        fstream localFile;
        localFile.open("../set/" + realName + ".res", ios::out);
        localFile << "s 1" << endl;
        localFile << "v ";
//        for (int i = 0, size = solution.Size(), absNum = 1;;) {
//            if (i < size) {
//                if (abs(solution[i]) > absNum) {
//                    localFile << absNum << " ";
//                    absNum++;
//                    continue;
//                } else {
//                    localFile << solution[i] << " ";
//                    i++;
//                    absNum++;
//                    continue;
//                }
//            } else {
//                for (; absNum <= symbolNum; absNum++) {
//                    localFile << absNum << " ";
//                }
//                break;
//            }
//        }
        for (int i = 0, size = solution.Size(); i < size;) {
            localFile << solution[i] << " ";
            i++;
        }
        localFile << endl;
        localFile << "t " << time * 1000 << endl;
    } else {
        fstream localFile;
        localFile.open("../set/" + realName + ".res", ios::out);
        localFile << "s " << status << endl;
        localFile << "v" << endl;
        localFile << "t " << time * 1000 << endl;
    }
}

void CnfParser::outputSolution(bool status, Solution solution, double time, string givenName) {
    //use status to tell true from false
    if (status == 1) {
        fstream localFile;
        localFile.open("../set/" + givenName + ".res", ios::out);
        localFile << "s 1" << endl;
        localFile << "v ";
//        for (int i = 0, size = solution.Size(), absNum = 1;;) {
//            if (i < size) {
//                if (abs(solution[i]) > absNum) {
//                    localFile << absNum << " ";
//                    absNum++;
//                    continue;
//                } else {
//                    localFile << solution[i] << " ";
//                    i++;
//                    absNum++;
//                    continue;
//                }
//            } else {
//                for (; absNum <= symbolNum; absNum++) {
//                    localFile << absNum << " ";
//                }
//                break;
//            }
//        }
        for (int i = 0, size = solution.Size(); i < size;) {
            localFile << solution[i] << " ";
            i++;
        }
        localFile << endl;
        localFile << "t " << time * 1000 << endl;
    } else {
        fstream localFile;
        localFile.open("../set/" + givenName + ".res", ios::out);
        localFile << "s " << status << endl;
        localFile << "v" << endl;
        localFile << "t " << time * 1000 << endl;
    }
}
void CnfParser::outputSudoku(Formula target) {
    fstream localFile;
    localFile.open("../set/Sudoku.cnf", ios::out);
    localFile << "c @Jgw" << endl;
    localFile << "p cnf 729 " << target.Size() << endl;
    for (auto p = target.Start(); p != NULL && p != target.End()->next;) {
        for (auto pList = p->data.Start(); pList != NULL && pList != p->data.End()->next;) {
            localFile << pList->data << " ";
            pList = pList->next;
        }
        localFile << "0" << endl;
        p = p->next;
    }
}
#endif //TESTC_CNFPARSER_H
