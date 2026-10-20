
#include <stdio.h>
#include <stdlib.h>
#include "fila_empacotamento.h"

Fila_Pacotes *criar_fila()
{
    Fila_Pacotes *fila = (Fila_Pacotes*) malloc(sizeof(Fila_Pacotes));
    if(fila == NULL) return NULL;

    fila->cabeca = NULL;
    fila->cauda = NULL;
    fila->tamanho = 0;

    return fila;
}

No_fila *inserir_fila_pedidos(No_pedidos *pedido,Fila_Pacotes *fila)
{
    No_fila *novo = (No_fila*) malloc(sizeof(No_fila));
    if(novo == NULL) return NULL;


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

void ver_fila(Fila_Pacotes *fila)
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