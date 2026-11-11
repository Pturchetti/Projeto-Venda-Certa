
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "caixas.h"

Fila_caixas *criar_fila_caixas()
{
    Fila_caixas *fila = (Fila_caixas*)malloc(sizeof(Fila_caixas));

    if(fila == NULL)
    {
        printf("Não foi possível criar a fila de caixas!\n");
        return NULL;
    }

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
    strcpy(novo->nome, produto_atual->nome);
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
            No *inserir_produto = inserir_na_caixa(produto_atual, caixa);
            if(inserir_produto == NULL) return 0;

            quantidade_restante--;

            if(caixa->volume > volume_maximo_caixa)
            {
                desempilhar(caixa);
                quantidade_restante++;

                strcpy(caixa->codigo_entrega, codigo_atual);
                caixa->prioridade = consultar_prioridade_pedido(pedido_atual->dados);
                caixa->codigo_caixa = gerar_codigo_caixa(codigos);
                incrementar_total_caixas(codigos);

                No_caixa *inserir_fila = inserir_fila_caixas(caixa, fila_caixas);
                if(inserir_fila == NULL) return 0;

                caixa = criar_caixa();
                if(caixa == NULL) return 0;
            }
        }

        produto_atual = produto_atual->proximo;
    }

    if(caixa->topo != NULL)
    {
        strcpy(caixa->codigo_entrega, codigo_atual);
        caixa->prioridade = consultar_prioridade_pedido(pedido_atual->dados);
        caixa->codigo_caixa = gerar_codigo_caixa(codigos);
        incrementar_total_caixas(codigos);

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
    {
        printf("Não foi possível acessar as filas para empacotar os pedidos!\n");
        return;
    }

    char codigo_atual[100];
    int volume_maximo_caixa = 10;

    while(fila_pedidos->cabeca != NULL)
    {
        No_fila *remover = fila_pedidos->cabeca;
        No_pedidos *pedido_atual = remover->pedido;

        strcpy(codigo_atual, consultar_codigo_entrega(pedido_atual->dados));
        int empacotado = empacotar_pedido(pedido_atual, codigo_atual,volume_maximo_caixa, fila_caixas,codigos);
        if( empacotado == 0)
        {
            printf("Não foi possível concluir o empacotamento do pedido\n");
            return;
        }

        alterar_empacotado_pedido(pedido_atual->dados,1);

        fila_pedidos->cabeca = remover->proximo;

        if(fila_pedidos->cabeca == NULL)
        {
            fila_pedidos->cauda = NULL;
        }

        fila_pedidos->tamanho--;

        free(remover);
    }

    printf("Todas as caixas foram empacotadas!\n");
}

void ver_caixas(Fila_caixas *fila_caixas, Codigos *codigos)
{
    if(fila_caixas->cabeca == NULL)
    {
        printf("NÃO EXISTEM CAIXAS PARA EXPEDIÇÃO\n");
        return;
    }

    No_caixa *atual = fila_caixas->cabeca;
    No *produto_atual;
    No *produto_anterior;
    printf("TOTAL DE CAIXAS:%d\n",obter_total_caixas(codigos));
    for(int i = 0; i < fila_caixas->tamanho; i++)
    {
        produto_atual = atual->caixa->topo;
        produto_anterior = NULL;
        int quantidade = 1;
        printf("CAIXA %d\n", i + 1);
        printf("Código de entrega: %s ||", atual->caixa->codigo_entrega);
        printf("Prioridade: %d ||", atual->caixa->prioridade);
        printf("Volume total: %d/10\n", atual->caixa->volume);

        printf("PRODUTOS NA CAIXA:\n");

        while(produto_atual != NULL)
        {
            if(produto_anterior != NULL && produto_atual->codigo_produto == produto_anterior->codigo_produto)
            {
                quantidade++;
            }
            else
            {
                if(produto_anterior != NULL)
                {
                    printf("Código do produto: %d ||", produto_anterior->codigo_produto);
                    printf("Nome: %s ||", produto_anterior->nome);
                    printf("Quantidade: %d ||", quantidade);
                    printf("Volume individual: %d\n", produto_anterior->volume);
                }
                quantidade = 1;
            }

            produto_anterior = produto_atual;
            produto_atual = produto_atual->proximo;
        }

        if(produto_anterior != NULL)
        {
            printf("Código do produto: %d ||", produto_anterior->codigo_produto);
            printf("Nome: %s ||", produto_anterior->nome);
            printf("Quantidade: %d ||", quantidade);
            printf("Volume individual: %d\n", produto_anterior->volume);
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
void desempilhar(Caixa *caixa)
{
    No *remover = caixa->topo;

    caixa->topo = caixa->topo->proximo;
    caixa->volume -= remover->volume;

    free(remover);

}
