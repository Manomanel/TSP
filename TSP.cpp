#include <iostream>
#include <vector>

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

    Solucao s2;

    std::vector<int> candidatos;

    for(int i = 1; i <= 6; i++)
    {
        candidatos.push_back(i);
    }

    std::vector<int>::iterator it;
 
    candidatos.erase(candidatos.begin());

    s2.sequencia.push_back(1);
    int count;

    double menor;

    for (int j = 0; j < 5; j++)
    {
        menor = 99999;
        for (count = 0; count < candidatos.size(); count++)
        {
            std::cout << matrizAdj[s2.sequencia.back()-1][candidatos[count]-1] << std::endl;
            if (matrizAdj[s2.sequencia.back()-1][candidatos[count]-1] < menor)
            {
                menor = matrizAdj[s2.sequencia.back()-1][candidatos[count]-1];
                it = candidatos.begin() + count;
                //teste = candidatos[count];
                std::cout << "Entrei " << std::endl;
            }
        }
        //std::cout << "sou o teste " << candidatos[teste] << std::endl;
        s2.sequencia.push_back(*it);
        candidatos.erase(it);
        for (int i = 0; i < candidatos.size(); i++)
        {
            std::cout << candidatos[i] << " oia so essa piranha" << std::endl;
        }
        
        exibirSolucao(s2);
    }
    
    s2.sequencia.push_back(1);

    exibirSolucao(s2);
    calcularValorObj(s2);
    std::cout << s2.valorObj << "\n";

    return 0;
}