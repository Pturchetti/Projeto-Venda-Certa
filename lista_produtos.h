#ifndef LISTA_PRODUTOS_H
#define LISTA_PRODUTOS_H
#include "cadastro.h"
#include "json_produtos.h"


typedef struct codigos {
    int ultimo_codigo_pedido;
} Codigos;



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

No *inserir_produtos(ListaProdutos *lista, Produto produto);

Produto buscar_produto(Produto catalogo[], int tamanho);

void ver_produtos(Produto catalogo[],int tamanho);

void modificar_produtos(Produto catalogo[],int tamanho);
#endif