
#include <stdio.h>
#include <stdlib.h>
#include "fila_empacotamento.h"
#include "lista_pedidos.h"

Fila_Pedidos *criar_fila()
{
    Fila_Pedidos *fila = (Fila_Pedidos*) malloc(sizeof(Fila_Pedidos));
    if(fila == NULL)
    {
        printf("Não foi possível criar a fila de empacotamento!\n");
        return NULL;
    }

    fila->cabeca = NULL;
    fila->cauda = NULL;
    fila->tamanho = 0;

    return fila;
}

No_fila *inserir_fila_pedidos(No_pedidos *pedido,Fila_Pedidos *fila)
{
    No_fila *novo = (No_fila*) malloc(sizeof(No_fila));
    if(novo == NULL)
    {
        printf("Não foi possível inserir o pedido na fila de empacotamento!\n");
        return NULL;
    }


    novo->proximo = NULL;
    novo->pedido = pedido;
    
    if(fila->cabeca == NULL)
    {
        fila->cabeca = novo;
        fila->cauda = novo;
        fila->tamanho++;
        return novo;
    }
    else
    {
        fila->cauda->proximo = novo;
        fila->cauda = novo;
        fila->tamanho++;
        return novo;
    }

}

void ver_fila(Fila_Pedidos *fila)
{
    if(fila->cabeca == NULL)
    {
        printf("\nAinda não existe uma fila de pedidos para empacotamento\n");
        return;
    }
    No_fila *atual;
    atual = fila->cabeca;

    for(int i = 0;i<fila->tamanho;i++)
    {
        printf("Pedido Número:%d\n",atual->pedido->dados->codigo_pedido);
        atual = atual->proximo;
    }
}