#ifndef PERTURBACAO_H
#define PERTURBACAO_H

#include "solucao.h"

Solucao perturbacao(Solucao&, double** matrizAdj);
Solucao ILS(int maxIter, int maxIterIls, int dimensao, double** matrizAdj);

#endif