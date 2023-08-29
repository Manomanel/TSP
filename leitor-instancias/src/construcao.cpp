#include <iostream>
#include <vector>
#include <ctime>

#include "construcao.h"
#include "solucao.h"

void prepararSolucao (Solucao &s, std::vector<int> &candidatos, double **matrizAdj, int dimensao);

Solucao criarSolucao (double **matrizAdj, int dimensao)
{
    Solucao s;
    std::vector<int> candidatos;
    for (int i = 2; i <= dimensao; i++)
    {
        candidatos.push_back(i);
    }
    prepararSolucao(s, candidatos, matrizAdj, dimensao);

    return s;
}

void prepararSolucao (Solucao &s, std::vector<int> &candidatos, double **matrizAdj, int dimensao)
{
    s.sequencia.push_back(1);

    for (int i = 0; i < 3; i++)
    {
        int rnd = rand() % candidatos.size();
        s.sequencia.push_back(candidatos[rnd]);
        candidatos.erase(candidatos.begin()+rnd);
    }
    s.sequencia.push_back(1);
    calcularValorObj(s, matrizAdj);
    std::cout << s.valorObj;

}