
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "caixas.h"

Fila_caixas *criar_fila_caixas()
{
    Fila_caixas *fila = (Fila_caixas*)malloc(sizeof(Fila_caixas));

    if(fila == NULL) return NULL;

    fila->cabeca = NULL;
    fila->cauda = NULL;
    fila->tamanho = 0;

    return fila;
}

Caixa *criar_caixa()
{
    Caixa *caixa = (Caixa*)malloc(sizeof(Caixa));

    if(caixa == NULL)
    {
        printf("Não foi possível criar a caixa\n");
        return NULL;
    }

    caixa->codigo_entrega[0] = '\0';
    caixa->volume = 0;
    caixa->topo = NULL;
    caixa->prioridade = -1;

    return caixa;
}

No *inserir_na_caixa(No *produto_atual, Caixa *caixa)
{
    No *novo = (No*)malloc(sizeof(No));

    if(novo == NULL)
    {
        printf("Não foi possível inserir o produto na caixa\n");
        return NULL;
    }

    novo->codigo_produto = produto_atual->codigo_produto;
    novo->quantidade = 1;
    novo->volume = produto_atual->volume;

    novo->proximo = caixa->topo;
    caixa->topo = novo;
    caixa->volume += novo->volume;

    return novo;
}

No_caixa *inserir_fila_caixas(Caixa *caixa, Fila_caixas *fila_caixas)
{
    No_caixa *novo = (No_caixa*)malloc(sizeof(No_caixa));

    if(novo == NULL)
    {
        printf("Não foi possível inserir a caixa na fila de caixas\n");
        return NULL;
    }

    novo->caixa = caixa;
    novo->proximo = NULL;

    if(fila_caixas->cabeca == NULL)
    {
        fila_caixas->cabeca = novo;
        fila_caixas->cauda = novo;
    }
    else
    {
        No_caixa *atual = fila_caixas->cabeca;
        No_caixa *anterior = NULL;

        while(atual != NULL && atual->caixa->prioridade <= caixa->prioridade)
        {
            anterior = atual;
            atual = atual->proximo;
        }

        if(anterior == NULL)
        {
            novo->proximo = fila_caixas->cabeca;
            fila_caixas->cabeca = novo;
        }
        else
        {
            anterior->proximo = novo;
            novo->proximo = atual;
        }

        if(atual == NULL)
        {
            fila_caixas->cauda = novo;
        }
    }

    fila_caixas->tamanho++;

    return novo;
}

int empacotar_pedido(No_pedidos *pedido_atual,char *codigo_atual,int volume_maximo_caixa, Fila_caixas *fila_caixas, Codigos *codigos)
{
    if(pedido_atual == NULL || fila_caixas == NULL)return 0;

    Caixa *caixa = criar_caixa();

    if(caixa == NULL)return 0;

    No *produto_atual = pedido_atual->lista->primeiro;

    while(produto_atual != NULL)
    {
        int quantidade_restante = produto_atual->quantidade;

        while(quantidade_restante > 0)
        {
            if(caixa->volume + produto_atual->volume > volume_maximo_caixa)
            {
                strcpy(caixa->codigo_entrega, codigo_atual);
                caixa->prioridade = pedido_atual->dados->prioridade;
                caixa->codigo_caixa = ++codigos->ultimo_codigo_caixa;
                codigos->total_caixas++;
                No_caixa *inserir_fila = inserir_fila_caixas(caixa, fila_caixas);
                if(inserir_fila == NULL)
                    return 0;

                caixa = criar_caixa();

                if(caixa == NULL)
                    return 0;
            }
            else
            {
                No *inserir_produto = inserir_na_caixa(produto_atual, caixa);
                if(inserir_produto == NULL)return 0;

                quantidade_restante--;
            }
        }

        produto_atual = produto_atual->proximo;
    }

    if(caixa->topo != NULL)
    {
        strcpy(caixa->codigo_entrega, codigo_atual);
        caixa->prioridade = pedido_atual->dados->prioridade;
        caixa->codigo_caixa = ++codigos->ultimo_codigo_caixa;
        codigos->total_caixas++;
        No_caixa *inserir_fila = inserir_fila_caixas(caixa, fila_caixas);

        if( inserir_fila == NULL)return 0;
    }
    else
    {
        free(caixa);
    }

    return 1;
}

void empacotar(Fila_Pedidos *fila_pedidos, Fila_caixas *fila_caixas, Codigos *codigos)
{
    if(fila_pedidos == NULL || fila_caixas == NULL)
        return;

    char codigo_atual[10];
    int volume_maximo_caixa = 10;

    while(fila_pedidos->cabeca != NULL)
    {
        No_fila *remover = fila_pedidos->cabeca;
        No_pedidos *pedido_atual = remover->pedido;

        strcpy(codigo_atual, pedido_atual->dados->codigo_entrega);
        int empacotado = empacotar_pedido(pedido_atual, codigo_atual,volume_maximo_caixa, fila_caixas,codigos);
        if( empacotado == 0)
        {
            printf("Não foi possível concluir o empacotamento do pedido\n");
            return;
        }

        pedido_atual->dados->empacotado = 1;

        fila_pedidos->cabeca = remover->proximo;

        if(fila_pedidos->cabeca == NULL)
        {
            fila_pedidos->cauda = NULL;
        }

        fila_pedidos->tamanho--;

        free(remover);
    }
}

void ver_caixas(Fila_caixas *fila_caixas, Codigos codigos)
{
    if(fila_caixas->cabeca == NULL)
    {
        printf("NÃO EXISTEM CAIXAS PARA EXPEDIÇÃO\n");
        return;
    }

    No_caixa *atual = fila_caixas->cabeca;
    No *produto_atual;
    printf("TOTAL DE CAIXAS:%d\n",codigos.total_caixas);
    for(int i = 0; i < fila_caixas->tamanho; i++)
    {
        produto_atual = atual->caixa->topo;

        printf("CAIXA %d\n", i + 1);
        printf("Código de entrega: %s ||", atual->caixa->codigo_entrega);
        printf("Prioridade: %d ||", atual->caixa->prioridade);
        printf("Volume total: %d/10\n", atual->caixa->volume);

        printf("PRODUTOS NA CAIXA:\n");

        while(produto_atual != NULL)
        {
            printf("Código do produto: %d ||", produto_atual->codigo_produto);
            printf("Quantidade: %d ||", produto_atual->quantidade);
            printf("Volume: %d\n", produto_atual->volume);

            produto_atual = produto_atual->proximo;
        }

        printf("\n\n");
        atual = atual->proximo;
    }

    printf("Retornar?(s/n)\n");

    while(1)
    {
        char resposta;
        scanf(" %c", &resposta);

        if(resposta == 's')
        {
            return;
        }
        else if(resposta == 'n')
        {
            break;
        }
        else
        {
            printf("\nRESPOSTA INVÁLIDA\n");
        }
    }
}
