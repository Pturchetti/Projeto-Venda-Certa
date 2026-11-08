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
        printf("QUANTIDADE INVÁLIDA, DIGITE NOVAMENTE:\n");
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



void ver_produtos(No_catalogo *comeco)
{
    if(comeco == NULL) return;
    if(comeco->esquerda !=NULL) ver_produtos(comeco->esquerda);
    printf("Código: %d || Nome: %s || quantidade: %d || Volume : %d\n",comeco->produto.codigo,comeco->produto.nome,comeco->produto.quantidade,comeco->produto.volume);

    if(comeco->direita != NULL) ver_produtos(comeco->direita);
}

void modificar_produtos(Catalogo *catalogo)
{
    printf("Digite o código do produto:\n");
    Produto produto;
    while(1)
    {
        int codigo;
        scanf("%d", &codigo);
        No_catalogo *comeco = catalogo->raiz;
        produto = buscar_produto(comeco,codigo);
        if(produto.codigo ==-1)
        {
            printf("Não existe um produto com esse código, digite novamente:\n");
        }
        else break;
    }

    printf("DIGITE A NOVA QUANTIDADE DO PRODUTO:");
    int nova_quantidade;
    while(1)
    {
        scanf("%d", &nova_quantidade);
        if(nova_quantidade < 0)
        {
            printf("QUANTIDADE INVÁLIDA, DIGITE NOVAMENTE\n");
        }
        else break;
    }


    No_catalogo *atual = catalogo->raiz;

    while(atual != NULL)
    {
        if(atual->produto.codigo == produto.codigo)
        {
            atual->produto.quantidade = nova_quantidade;
            break;
        }
        else if(produto.codigo < atual->produto.codigo)
        {
            atual = atual->esquerda;
        }
        else
        {
            atual = atual->direita;
        }
    }
    printf("PRODUTO ALTERADO COM SUCESSO!\n");
}