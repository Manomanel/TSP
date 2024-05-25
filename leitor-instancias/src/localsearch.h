#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "solucao.h"

void swap (Solucao&, double** matrizAdj);
void reinsertion (Solucao&, double** matrizAdj, int);
void two_opt (Solucao&, double** matrizAdj);

#endif