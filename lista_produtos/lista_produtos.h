#ifndef LISTA_PRODUTOS_H
#define LISTA_PRODUTOS_H
#include "cadastro.h"




typedef struct No{
    struct No *proximo;
    int codigo_produto;
    int quantidade;
    int volume;
}No;

typedef struct  ListaProdutos{
    No *primeiro;
    No *ultimo;
    int tamanho;
}ListaProdutos;

ListaProdutos *criar_lista_produtos();

No *inserir_produtos(ListaProdutos *lista, Produto *produto);

int buscar_produto_pedido(ListaProdutos *lista, Produto *produto);


#endif