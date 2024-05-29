#include <iostream>
#include <vector>
#include <ctime>
#include <limits>

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

    //inicio do ILS
    Solucao bestOfAll;
    bestOfAll.valorObj = std::numeric_limits<double>::max();

    for (int i = 0; i < maxIter; i++){
        Solucao s = criarSolucao(matrizAdj, dimensao);
        Solucao best = s;

        int iterIls = 0;

        while (iterIls <= maxIterIls){
            rvnd(s, matrizAdj);
            if (s.valorObj < best.valorObj){
                best = s;
                iterIls = 0;
            }
            s = best;
            perturbacao(s, matrizAdj);
            iterIls++;
        }
        if (best.valorObj < bestOfAll.valorObj){
            bestOfAll = best;
        }
    }
    
    cout << "Valor depois do ILS: " << bestOfAll.valorObj << endl;

    return 0;
}