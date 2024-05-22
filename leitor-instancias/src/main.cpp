#include <iostream>
#include <vector>
#include <ctime>

#include "Data.h"
#include "solucao.h"
#include "construcao.h"
#include "localsearch.h"

using namespace std;

int main(int argc, char** argv) {

    srand(time(NULL));

    auto data = Data(argc, argv[1]);
    data.read();
    int dimensao = data.getDimension();
    double **matrizAdj = data.getMatrixCost();

    Solucao s;
    s = criarSolucao(matrizAdj, dimensao);
    exibirSolucao(s);
    calcularValorObj(s, matrizAdj);
    cout << "Valor antes do swap: " << s.valorObj << endl;

    bestImprovement(s, matrizAdj);
    cout << "Valor depois do swap: " << s.valorObj << endl;

    return 0;
}
