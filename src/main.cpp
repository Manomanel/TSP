#include <iostream>
#include <vector>
#include <ctime>
#include <limits>
#include <chrono>
#include <iomanip>

#include "Data.h"
#include "solucao.h"
#include "construcao.h"
#include "localsearch.h"
#include "perturbacao.h"

using namespace std;

int main(int argc, char** argv) {

    const std::clock_t c_start = std::clock();
    srand(time(NULL));

    auto data = Data(argc, argv[1]);
    data.read();
    int dimensao = data.getDimension();
    double **matrizAdj = data.getMatrixCost();
    int maxIterIls, maxIter = 50;
    if (dimensao >= 150){
        maxIterIls = dimensao/2;
    } else {maxIterIls = dimensao;}

    float avarageScore = 0;
    for (int a = 0; a < 10; a++){
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
        avarageScore += bestOfAll.valorObj;
    }
    avarageScore /= 10;
    const std::clock_t c_end = std::clock(); 
    cout << "Valor medio do ILS: " << avarageScore << endl;

    std::cout << std::fixed << std::setprecision(2) << "Tempo medio do uso da CPU: "
              << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC / 10<< "ms\n";
              
    return 0;
}