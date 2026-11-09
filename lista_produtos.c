#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "lista_produtos.h"


ListaProdutos *criar_lista_produtos()
{
    ListaProdutos *lista = (ListaProdutos*) malloc(sizeof(ListaProdutos));
    if(lista == NULL) return NULL;

    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tamanho = 0;

    return lista;
}




No *inserir_produtos(ListaProdutos *lista, Produto produto)
{
    if(produto.quantidade == 0)
    {
        printf("PRODUTO SEM ESTOQUE!\n");
        return NULL;
    }

    printf("\nCÓDIGO DO PRODUTO: %d\n", produto.codigo);
    printf("\nNOME DO PRODUTO: %s\n", produto.nome);
    printf("\nQUANTIDADE DISPONÍVEL DO PRODUTO: %d\n", produto.quantidade);
    printf("\nVOLUME DO PRODUTO: %d\n", produto.volume);

    No *novo = (No*) malloc(sizeof(No));

    if(novo == NULL)
    {
        printf("OCORREU UM ERRO, TENTE NOVAMENTE MAIS TARDE!\n");
        return NULL;
    }

    novo->codigo_produto = produto.codigo;
    printf("DIGITE A QUANTIDADE QUE VOCÊ DESEJA:");
    int quantidade;
    printf("\n");

    while(1)
    {
    scanf("%d", &quantidade);
    if(quantidade>produto.quantidade || quantidade<1)
    {
        printf("QUANTIDADE INVÁLIDA OU SEM ESTOQUE, DIGITE NOVAMENTE:\n");
    }
    else break;
    }
    novo->quantidade = quantidade;
    novo->volume = produto.volume;
    novo->proximo = NULL;

    if(lista->primeiro == NULL)
    {
        lista->primeiro = novo;
        lista->ultimo = novo;
        lista->tamanho++;
    }
    else
    {
        lista->ultimo->proximo = novo;
        lista->ultimo = novo;
        lista->tamanho++;
    }
    return novo;
}


