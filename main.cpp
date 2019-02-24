#include "iostream"
//#include "referVector.h"
#include "myVector.h"
#include "myList.h"
#include "vector"
#include "memory"
#include "fstream"
#include "Dpll.h"
#include "chrono"
#include "CnfParser.h"
#include "regex"
//#include "algorithm"
using namespace std;





int main(void) {


    string localFileName;
    localFileName = "True_M2";
    regex pattern(".cnf");
    string localFileNameSelected = regex_replace(localFileName, pattern, "");
    auto f1 = readCNF("../set/" + localFileName);

    auto t1 = chrono::steady_clock::now();
    auto x = Dpll(f1, 0);
    auto t2 = chrono::steady_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double >>(t2 - t1);
    cout << x << endl << "Time(s): " << time_span.count() << "" << endl;
    ShowVector(solution);
    if (x == 0) {
        outputSolution(0, "../set/" + localFileNameSelected + ".res", time_span.count() * 1000);
    } else {
        SortSolution(solution);
        outputSolution(solution, "../set/" + localFileNameSelected + ".res", time_span.count() * 1000);
    }


}