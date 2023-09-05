#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

#include "Data.h"
#include "construcao.h"
#include "solucao.h"

#define alpha = 0.25

typedef struct insercao {
    int verticeSelecionado;
    int verticeRemovido;
    double custoInsecao;
} insercao;

void prepararSolucao (Solucao &s, std::vector<int> &candidatos, double **matrizAdj, int dimensao);
void criarInsercoes (Solucao &s, std::vector<int> &candidatos, double **matrizAdj, std::vector<insercao> &lista);
void ordenarLista (std::vector<insercao> &lista);

Solucao criarSolucao (double **matrizAdj, int dimensao)
{
    Solucao s;
    std::vector<int> candidatos;
    for (int i = 2; i <= dimensao; i++)
    {
        candidatos.push_back(i);
    }
    prepararSolucao(s, candidatos, matrizAdj, dimensao);
    exibirSolucao(s);
    std::vector<insercao> lista;
    
    while (!candidatos.empty())
    {
        lista.clear();
        criarInsercoes(s, candidatos, matrizAdj, lista);
        for (size_t i = 0; i < lista.size(); i++)
        {
            cout << "custo insercao: " << lista[i].custoInsecao << "  e vertice removido: " << lista[i].verticeRemovido << endl;
        }
        cout << "novo loop" << endl;
    }
    calcularValorObj(s, matrizAdj);
    std::cout << s.valorObj << endl;
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
}

void criarInsercoes (Solucao &s, std::vector<int> &candidatos, double **matrizAdj, std::vector<insercao> &lista)
{
    double distAtual, distNova;    
    
    for (int i = 0; i < s.sequencia.size()-1; i++)//cada vertice de S'
    {
        for (size_t j = 0; j < candidatos.size(); j++)//para cada candidato
        {
        insercao kkk;
        kkk.verticeSelecionado = candidatos[j];
        int elemento = candidatos[j];
        distAtual = matrizAdj[s.sequencia[i]-1][s.sequencia[i+1]-1];

        distNova = matrizAdj[s.sequencia[i]-1][elemento-1] + matrizAdj[elemento-1][s.sequencia[i+1]-1];

        kkk.custoInsecao = distNova - distAtual;
        kkk.verticeRemovido = i+1;
        lista.push_back(kkk);
        }

    }
    ordenarLista(lista);
    s.sequencia.emplace(s.sequencia.begin()+lista.begin()->verticeRemovido, lista.begin()->verticeSelecionado);
    auto iter = std::find(candidatos.begin(), candidatos.end(), lista.begin()->verticeSelecionado);
    candidatos.erase(iter);
}

void ordenarLista (std::vector<insercao> &lista)
{
    std::sort(lista.begin(), lista.end(), [](const insercao& a, const insercao& b) {
    return a.custoInsecao < b.custoInsecao;
    });
}