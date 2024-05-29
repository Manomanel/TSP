#include <iostream>
#include <vector>
#include <ctime>
#include <limits>

#include "Data.h"
#include "construcao.h"
#include "localsearch.h"
#include "solucao.h"

Solucao perturbacao (Solucao &s, double** matrizAdj)
{
    int pos_i, pos_j, tam_i, tam_j;
    int tam_max = ceil(s.sequencia.size() / 10);

    tam_i = rand() % (tam_max-2)+2;
    tam_j = rand() % (tam_max-2)+2;
    pos_i = rand() % (s.sequencia.size()-tam_i-1) + 1;

    do{
        pos_j = rand() % (s.sequencia.size()-tam_j-1) + 1;
    } while (!(pos_j + tam_j < pos_i) && !(pos_j > pos_i + tam_i));

    //int delta = - matrizAdj[pos_i-1][pos_i] - matrizAdj[pos_i+tam_i-1][pos_i+tam_i] - matrizAdj[pos_j-1][pos_j] - matrizAdj[pos_j+tam_j-1][pos_j+tam_j]
    //            + matrizAdj[pos_i-1][pos_j] + matrizAdj[pos_i+tam_i-1][pos_j+tam_j] + matrizAdj[pos_j-1][pos_i] + matrizAdj[pos_j+tam_j-1][pos_i+tam_i];
    //s.valorObj = s.valorObj + delta;

    std::vector<int> aux;

    if (pos_i < pos_j){
        //colocar no vetor auxiliar os valores de J
        for (int j = 0; j < tam_j; j++){
            aux.push_back(s.sequencia[pos_j]);
            s.sequencia.erase(s.sequencia.begin()+pos_j);
        }

        //colocar na posicao de J os valores de I
        for (int i = 0; i < tam_i; i++){
            s.sequencia.insert(s.sequencia.begin()+pos_j, s.sequencia[pos_i]);
            s.sequencia.erase(s.sequencia.begin()+pos_i);
        }
        //insere os valores do vetor aux na solucao na posicao I
        while (!aux.empty()){
            s.sequencia.insert(s.sequencia.begin()+pos_i, aux.back());
            aux.pop_back();
        }
        
    } else { //para casos em que o vetor J vem antes de I
        for (int i = 0; i < tam_i; i++){
            aux.push_back(s.sequencia[pos_i]);
            s.sequencia.erase(s.sequencia.begin()+pos_i);
        }

        for (int j = 0; j < tam_j; j++){
            s.sequencia.insert(s.sequencia.begin()+pos_i, s.sequencia[pos_j]);
            s.sequencia.erase(s.sequencia.begin()+pos_j);
        }

        while (!aux.empty()){
            s.sequencia.insert(s.sequencia.begin()+pos_j, aux.back());
            aux.pop_back();
        }
    }

    calcularValorObj(s, matrizAdj);

    return s;
}

Solucao ILS(int maxIter, int maxIterIls, int dimensao, double** matrizAdj){
    
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
            //s = perturbacao(best, matrizAdj);
            iterIls++;
        }
        if (best.valorObj < bestOfAll.valorObj){
            bestOfAll = best;
        }
    }
    
    return bestOfAll;
}