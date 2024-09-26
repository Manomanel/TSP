#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "solucao.h"

bool swap (Solucao&, double** matrizAdj);
bool reinsertion (Solucao&, double** matrizAdj, int);
bool two_opt (Solucao&, double** matrizAdj);
bool rvnd (Solucao&, double** matrizAdj);

#endif