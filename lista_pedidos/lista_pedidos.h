#ifndef LISTA_PEDIDOS_H
#define LISTA_PEDIDOS_H

#include "lista_produtos.h"
#include "codigos.h"

typedef struct Fila_Pedidos Fila_Pedidos;

typedef struct dados_pedido dados_pedido;

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

void modificar_pedidos(ListaProdutos *lista, Produto *produto);

void fechar_pedidos(ListaPedidos *lista_pedidos,Fila_Pedidos *fila);

int consultar_codigo_pedido(dados_pedido *dados);
int consultar_prioridade_pedido(dados_pedido *dados);
int consultar_status_pedido(dados_pedido *dados);
int consultar_empacotado_pedido(dados_pedido *dados);
char *consultar_codigo_entrega(dados_pedido *dados);

void alterar_status_pedido(dados_pedido *dados, int status);
void alterar_empacotado_pedido(dados_pedido *dados, int empacotado);

#endif