#include <iostream>
#include <vector>
#include <iterator>
#include <limits>

typedef struct Solucao{
    std::vector<int> sequencia;
    double valorObj;
} Solucao;

void exibirSolucao(Solucao &s)
{
    for(int i = 0; i < s.sequencia.size() - 1; i++)
        std::cout << s.sequencia[i] << " -> ";
    std::cout << s.sequencia.back() << std::endl;
}

double matrizAdj[6][6] = {{0,245,174,118,59,129}, 
                          {245, 0, 250, 226, 186, 147},
                          {174, 250, 0, 274, 169, 114},
                          {118, 226,274,0,190,185},
                          {59,186,169,190,0,87},
                          {129,147,114,185,87,0}};

void calcularValorObj(Solucao &s)
{
    s.valorObj = 0;
    for(int i = 0; i < s.sequencia.size() - 1; i++)
        s.valorObj += matrizAdj[s.sequencia[i] - 1][s.sequencia[i+1] - 1];
}

int main(){

    Solucao s;
    std::vector<int> candidatos;

    for(int i = 0; i < (sizeof(matrizAdj)/sizeof(matrizAdj[0])); i++){
        candidatos.push_back(i);
    }

    candidatos.erase(candidatos.begin());

    std::vector<int>::iterator it;
    s.sequencia.push_back(1);

    double menor;
    int count = candidatos.size();

    for (int j = 0; j < count; j++)
    {
        menor = std::numeric_limits<double>::infinity();
        for (int i = 0; i < candidatos.size(); i++)
        {
            //std::cout << matrizAdj[s.sequencia.back()-1][candidatos[i]] << std::endl;
            if (matrizAdj[s.sequencia.back()-1][candidatos[i]] < menor)
            {
                menor = matrizAdj[s.sequencia.back()-1][candidatos[i]];
                it = candidatos.begin() + i;
            }
        }
        s.sequencia.push_back(*it+1);
        candidatos.erase(it);
        exibirSolucao(s);
    }
    s.sequencia.push_back(1);

    exibirSolucao(s);
    calcularValorObj(s);
    std::cout << s.valorObj << "\n";

    return 0;
}