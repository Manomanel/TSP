#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>//reverse

#include "Data.h"
#include "construcao.h"
#include "solucao.h"

bool swap (Solucao &s, double **matrizAdj)
{
    double best_delta = 0; //melhor valor encontrado para o movimento
    int best_i, best_j; //posições usadas

    for (size_t i = 1; i < s.sequencia.size() - 1; i++){
        int vi = s.sequencia[i]-1;
        int vi_prev = s.sequencia[i-1]-1;
        int vi_next = s.sequencia[i+1]-1;
        for (size_t j = i + 1; j < s.sequencia.size() - 1; j++){
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

            if (delta < best_delta){
                best_delta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }
    
    if(best_delta < 0){
        std::swap(s.sequencia[best_i], s.sequencia[best_j]);
        s.valorObj += best_delta;
        return true;
    }
    return false;
}

bool reinsertion (Solucao &s, double **matrizAdj, int choice)
{
    double best_delta = 0;
    int best_i, best_j;

    for (size_t i = 1; i < s.sequencia.size() - 1; i++){
        if ((choice >= 2 && i == s.sequencia.size() - 2) || (choice == 3 && s.sequencia.size() - 3))continue;
        int vi = s.sequencia[i]-1;
        int vi_prev = s.sequencia[i-1]-1;
        int vi_last = s.sequencia[i+choice-1]-1;
        int vi_next = s.sequencia[i+choice]-1;

       for (size_t j = 1; j < s.sequencia.size() - 1; j++){
            if (j == i-1 || j == i || (j == i+1 && choice >= 2) || (j == i+2 && choice == 3))continue;

            int vj = s.sequencia[j]-1;
            int vj_next = s.sequencia[j+1]-1;

            double delta = 0;
            delta = - matrizAdj[vi_prev][vi] - matrizAdj[vi_last][vi_next] - matrizAdj[vj][vj_next]
                    + matrizAdj[vi_prev][vi_next] + matrizAdj[vj][vi] + matrizAdj[vi_last][vj_next];

            if (delta < best_delta){
                best_delta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if(best_delta < 0){
        for (int n = 0; n < choice; n++){
            if (best_i < best_j){
                s.sequencia.insert(s.sequencia.begin() + best_j+1, s.sequencia[best_i]);
                s.sequencia.erase(s.sequencia.begin() + best_i);
            } else {
                int teste = s.sequencia[best_i + n];
                s.sequencia.erase(s.sequencia.begin() + best_i + n);
                s.sequencia.insert(s.sequencia.begin() + best_j+1 + n, teste);
            }
        }
        s.valorObj += best_delta;
        return true;
    }
    return false;
}

bool two_opt (Solucao &s, double **matrizAdj)
{
    double best_delta = 0;
    int best_i, best_j;

    for (size_t i = 1; i < s.sequencia.size() - 1; i++){
        int vi = s.sequencia[i]-1;
        int vi_next = s.sequencia[i+1]-1;
        for (size_t j = i+2; j < s.sequencia.size() - 1; j++){
            int vj = s.sequencia[j]-1;
            int vj_prev = s.sequencia[j-1]-1;

            double delta = 0;
            delta = - matrizAdj[vi][vi_next] - matrizAdj[vj_prev][vj] 
                    + matrizAdj[vi][vj_prev] + matrizAdj[vi_next][vj];

            if(delta < best_delta){
                best_delta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if(best_delta < 0){
        std::reverse(s.sequencia.begin()+best_i+1, s.sequencia.begin()+best_j);
        s.valorObj += best_delta;
        return true;
    }
    return false;
}

void rvnd (Solucao &s, double **matrizAdj)
{

    std::vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    while (NL.empty() == false)
    {
        int n = rand() % NL.size();
        switch (NL[n])
        {
        case 1:
            improved = swap(s, matrizAdj);
            break;
        case 2:
            improved = reinsertion(s, matrizAdj, 1);
            break;
        case 3:
            improved = reinsertion(s, matrizAdj, 2);
            break;
        case 4:
            improved = reinsertion(s, matrizAdj, 3);
            break;
        case 5:
            improved = two_opt(s, matrizAdj);
            break;
        }
        if (improved)
            NL = {1, 2, 3, 4, 5};
        else
            NL.erase(NL.begin() + n);
    }
}