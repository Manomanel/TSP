#include <iostream>

#include "Data.h"
#include "solucao.h"

using namespace std;

int main(int argc, char** argv) {

    auto data = Data(argc, argv[1]);
    data.read();
    int dimensao = data.getDimension();

    cout << "Dimension: " << dimensao << endl;
    cout << "DistanceMatrix: " << endl;
    data.printMatrixDist();

    //double matrizAdj[dimensao][dimensao];
    //matrizAdj = data.getMatrixCost();
    double **costMatrix = data.getMatrixCost();

    cout << "Exemplo de Solucao s = ";
    double cost = 0.0;
    for (int i = 1; i < dimensao; i++) {
        cout << i << " -> ";
        cost += data.getDistance(i, i+1);
    }
    cost += data.getDistance(dimensao, 1);
    cout << dimensao << " -> " << 1 << endl;
    cout << "Custo de S: " << cost << endl;

    return 0;
}
