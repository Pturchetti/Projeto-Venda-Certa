
#ifndef FILA_PEDIDOS_H
#define FILA_PEDIDOS_H

#include "lista_pedidos.h"



typedef struct No_fila{
   struct No_fila *proximo;
   No_pedidos *pedido;
}No_fila;

typedef struct Fila_Pacotes{
    No_fila *cabeca;
    No_fila *cauda;
    int tamanho;
}Fila_Pacotes;

Fila_Pacotes *criar_fila();

No_fila *inserir_fila_pedidos(No_pedidos *pedido,Fila_Pacotes *fila);

void ver_fila(Fila_Pacotes *fila);
#endif