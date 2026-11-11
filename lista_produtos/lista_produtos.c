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




No *inserir_produtos(ListaProdutos *lista, Produto *produto)
{
    if(produto->quantidade == 0)
    {
        printf("Produto sem estoque!\n");
        return NULL;
    }

    printf("\nCódigo do produto: %d\n", produto->codigo);
    printf("\nNome do produto: %s\n", produto->nome);
    printf("\nQuantidade disponível do produto: %d\n", produto->quantidade);
    printf("\nVolume do produto: %d\n", produto->volume);

    No *novo = (No*) malloc(sizeof(No));

    if(novo == NULL)
    {
        printf("Ocorreu um erro, tente novamente mais tarde!\n");
        return NULL;
    }

    novo->codigo_produto = produto->codigo;
    strcpy(novo->nome, produto->nome);
    printf("Digite a quantidade que você deseja\n:");
    int quantidade;
    printf("\n");

    while(1)
    {
        scanf("%d", &quantidade);
        if(quantidade>produto->quantidade || quantidade<1)
        {
            printf("Quantidade inválida ou sem estoque:\n");
        }
        else break;
    }
    produto->quantidade-=quantidade;
    novo->quantidade = quantidade;
    novo->volume = produto->volume;
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

int buscar_produto_pedido(ListaProdutos *lista, Produto *produto)
{
    No *atual = lista->primeiro;
    for(int i =0;i<lista->tamanho;i++)
    {
        if(atual->codigo_produto == produto->codigo) return 1;
        atual = atual->proximo;
    }
    return 0;
}
