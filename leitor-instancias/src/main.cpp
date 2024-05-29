#include <iostream>
#include <vector>
#include <ctime>

#include "Data.h"
#include "solucao.h"
#include "construcao.h"
#include "localsearch.h"
#include "perturbacao.h"

using namespace std;

int main(int argc, char** argv) {

    srand(time(NULL));

    auto data = Data(argc, argv[1]);
    data.read();
    int dimensao = data.getDimension();
    double **matrizAdj = data.getMatrixCost();
    int maxIterIls, maxIter = 50;
    if (dimensao >= 150){
        maxIterIls = dimensao/2;
    } else {maxIterIls = dimensao;}
    
    Solucao s;

    s = ILS (maxIter, maxIterIls, dimensao, matrizAdj);

    cout << "Valor depois do ILS: " << s.valorObj << endl;


    return 0;
}
