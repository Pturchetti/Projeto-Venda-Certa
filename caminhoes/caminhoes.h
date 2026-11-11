#ifndef CAMINHOES_H
#define CAMINHOES_H

#include "caixas.h"

void sorteio_caminhoes(int docas[],int docas_original[]);
void caminhoes(Fila_caixas *fila_caixas);
void remover_caixa(Fila_caixas *fila_caixas);
int sorteio_caminhao();

#endif