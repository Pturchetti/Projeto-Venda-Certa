#ifndef LISTA_PEDIDOS_H
#define LISTA_PEDIDOS_H

#include "lista_produtos.h"

typedef struct No_pedidos{
    struct No_pedidos *proximo;
    ListaProdutos *lista;
    dados_pedido *dados; 
}No_pedidos;

typedef struct ListaPedidos{
    No_pedidos *primeiro;
    No_pedidos *ultimo;
    int tamanho;
}ListaPedidos;


ListaPedidos *criar_lista_pedidos();
No_pedidos *inserir_lista_pedidos(ListaProdutos *lista, dados_pedido *dados, ListaPedidos *lista_pedidos);

void ver_pedidos(ListaPedidos *lista_pedidos);

#endif