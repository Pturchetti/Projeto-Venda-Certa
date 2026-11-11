
#ifndef FILA_PEDIDOS_H
#define FILA_PEDIDOS_H

typedef struct No_pedidos No_pedidos;


typedef struct No_fila{
   struct No_fila *proximo;
   No_pedidos *pedido;
}No_fila;

typedef struct Fila_Pedidos{
    No_fila *cabeca;
    No_fila *cauda;
    int tamanho;
}Fila_Pedidos;

Fila_Pedidos *criar_fila();

No_fila *inserir_fila_pedidos(No_pedidos *pedido,Fila_Pedidos *fila);

void ver_fila(Fila_Pedidos *fila);
#endif