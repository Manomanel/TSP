#include <iostream>
#include <vector>
#include <ctime>

#include "Data.h"
#include "solucao.h"
#include "construcao.h"

using namespace std;

int main(int argc, char** argv) {

    srand(time(NULL));

    auto data = Data(argc, argv[1]);
    data.read();
    int dimensao = data.getDimension();
    double **matrizAdj = data.getMatrixCost();

    Solucao s;

    s = criarSolucao(matrizAdj, dimensao);
/*
    cout << "Dimension: " << dimensao << endl;
    cout << "DistanceMatrix: " << endl;
    data.printMatrixDist();

    cout << "Exemplo de Solucao s = ";
    double cost = 0.0;
    for (int i = 1; i < dimensao; i++) {
        cout << i << " -> ";
        cost += data.getDistance(i, i+1);
    }
    cost += data.getDistance(dimensao, 1);
    cout << dimensao << " -> " << 1 << endl;
    cout << "Custo de S: " << cost << endl;
*/
    return 0;
}
