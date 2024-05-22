#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>//find e sort

#include "Data.h"
#include "construcao.h"
#include "solucao.h"

void bestImprovement (Solucao &s, double **matrizAdj)
{
    double bestDelta = 0; //melhor valor encontrado para o movimento
    int best_i, best_j; //posições usadas

    for (int i = 1; i < s.sequencia.size() - 1; i++){
        int vi = s.sequencia[i]-1;
        int vi_prev = s.sequencia[i-1]-1;
        int vi_next = s.sequencia[i+1]-1;
        for (int j = i + 1; j < s.sequencia.size() - 1; j++){
            int vj = s.sequencia[j]-1;
            int vj_prev = s.sequencia[j-1]-1;
            int vj_next = s.sequencia[j+1]-1;
            
            double delta = 0;
            if (i+1 == j){
                delta = - matrizAdj[vi_prev][vi] + matrizAdj[vi_prev][vj] - matrizAdj[vj][vj_next] + matrizAdj[vi][vj_next];
            } else {
                delta = - matrizAdj[vi_prev][vi] - matrizAdj[vi][vi_next] + matrizAdj[vi_prev][vj]
                               + matrizAdj[vj][vi_next] - matrizAdj[vj_prev][vj] - matrizAdj[vj][vj_next]
                               + matrizAdj[vj_prev][vi] + matrizAdj[vi][vj_next];
            }

            if (delta < bestDelta){
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }
    
    if(bestDelta < 0){
        std::swap(s.sequencia[best_i], s.sequencia[best_j]);
        s.valorObj = s.valorObj + bestDelta;
    }
}