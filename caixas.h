#ifndef CAIXAS_H
#define CAIXAS_H

#include "lista_pedidos.h"
#include "fila_empacotamento.h"

typedef struct Caixa{
    int codigo_entrega;
    int volume;
    No *topo;
}Caixa;

typedef struct No_caixa{
    Caixa *caixa;
    struct No_caixa *proximo;
}No_caixa;

typedef struct Fila_caixas{
    No_caixa *cabeca;
    No_caixa *cauda;
    int tamanho; 
}Fila_caixas;

Fila_caixas *criar_fila_caixas();
Caixa *criar_caixa();
void empacotar(Fila_Pedidos *fila_pedidos,Fila_caixas *fila_caixas);
#endif