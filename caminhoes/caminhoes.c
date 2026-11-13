#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "caminhoes.h"

void sorteio_caminhoes(int docas[],int docas_original[])
{
    int capacidade_caminhoes[3] = {30,50,80};
    for(int i = 0;i<5;i++)
    {
        int sorteio = capacidade_caminhoes[rand() % 3];
        docas[i] = sorteio;
        docas_original[i] = sorteio;
    }
}


int sorteio_caminhao()
{
    int capacidade_caminhoes[3] = {30,50,80};
    int sorteio = capacidade_caminhoes[rand() % 3];

    return sorteio;
}

void remover_caixa(Fila_caixas *fila_caixas)
{
    No_caixa *remover = fila_caixas->cabeca;

    fila_caixas->cabeca = remover->proximo;

    if(fila_caixas->cabeca == NULL)
    {
        fila_caixas->cauda = NULL;
    }
    No *atual_produto = remover->caixa->topo;
    while(atual_produto != NULL)
    {
        No *remover_produto = atual_produto;
        atual_produto = atual_produto->proximo;
        free(remover_produto);
    }
    free(remover->caixa);
    free(remover);
    fila_caixas->tamanho--;
}
void caminhoes(Fila_caixas *fila_caixas)
{

    if(fila_caixas == NULL)
    {
        printf("Não foi possível acessar a fila de caixas!\n");
        return;
    }
    if(fila_caixas->cabeca == NULL)
    {
        printf("Ainda não existem caixas para serem empacotadas!\n");
        return;
    }
    int docas[5] = {0};
    int docas_original[5] = {0};
    sorteio_caminhoes(docas,docas_original);
    No_caixa *atual = fila_caixas->cabeca;
    int i = 0;
    
    while(atual != NULL)
    {
        if(i>4)
        {
            i=0;
            float maior = (float)docas[0] / docas_original[0];
            int indice = 0;
            for(int j = 1;j<5;j++)
            {
                if(((float)docas[j] / docas_original[j]) < maior)
                {
                    maior = (float)docas[j] / docas_original[j];
                    indice = j;
                }
            }
            printf("Caminhão da doca %d saiu para liberar espaço para novos pacotes\n", indice + 1);
            docas[indice] = sorteio_caminhao();
            docas_original[indice] = docas[indice];
        }
        if(atual->caixa->volume<=docas[i])
        {
            docas[i] -=atual->caixa->volume;
            atual= atual->proximo;
            remover_caixa(fila_caixas);
            if(docas[i] == 0)
            {
                printf("Caminhão da doca %d saiu cheio\n", i + 1);
                docas[i] = sorteio_caminhao();
                docas_original[i] = docas[i];
            }
            i=0;
        }
        else i++;

    }

    fila_caixas->cabeca = NULL;
    fila_caixas->cauda = NULL;

    for(int i = 0;i<5;i++)
    {
        if(docas[i]<docas_original[i])printf("O caminhão número %d de capacidade máxima %d saiu com volume ocupado de %d\n",i+1,docas_original[i],docas_original[i]-docas[i]);
    }
    printf("todas as caixas da fila de caixas foram para os caminhões, os caminhões citados saíram para entrega\n");
}