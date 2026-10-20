#ifndef LISTA_PEDIDOS_H
#define LISTA_PEDIDOS_H

#include "lista_produtos.h"



typedef struct dados_pedido{
    int codigo_pedido;
    char codigo_entrega[10];
    int status;
}dados_pedido;

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

dados_pedido *registrar_dados(Codigos *codigos);

void ver_pedidos(ListaPedidos *lista_pedidos);

#endif