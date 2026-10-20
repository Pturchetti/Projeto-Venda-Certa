#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "lista_pedidos.h"

void limpar() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

ListaPedidos *criar_lista_pedidos()
{
    ListaPedidos *lista = (ListaPedidos*) malloc(sizeof(ListaPedidos));

    if(lista == NULL) return NULL;

    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tamanho = 0;

    return lista;
}

No_pedidos *inserir_lista_pedidos(ListaProdutos *lista, dados_pedido *dados, ListaPedidos *lista_pedidos)
{
    No_pedidos *novo = (No_pedidos*) malloc(sizeof(No_pedidos));
    if(novo == NULL)
    {
        printf("NÃO FOI POSSÍVEL REGISTRAR O PEDIDO.\n");
        for(int i = 0; i < lista->tamanho; i++)
        {
            No *remover = lista->primeiro;
            lista->primeiro = lista->primeiro->proximo;
            free(remover);
        }
        free(lista);
        free(dados);
        return NULL;
    }

    novo->dados = dados;
    novo->lista = lista;
    novo->proximo = NULL;

    if(lista_pedidos->primeiro == NULL)
    {
        lista_pedidos->primeiro = novo;
        lista_pedidos->ultimo = novo;
        lista_pedidos->tamanho++;
    }
    else
    {
        lista_pedidos->ultimo->proximo = novo;
        lista_pedidos->ultimo = novo;
        lista_pedidos->tamanho++;
    }
    return novo;
}

dados_pedido *registrar_dados(Codigos *codigos)
{
    dados_pedido *dados = (dados_pedido*) malloc(sizeof(dados_pedido));
    if (dados == NULL) return NULL;

    dados->codigo_pedido = ++codigos->ultimo_codigo_pedido;


    printf("DIGITE O CÓDIGO DE ENTREGA: ");
    limpar();
    fgets(dados->codigo_entrega,10,stdin);

    printf("DESEJA FECHAR O PEDIDO?(s/n)\n");
    while(1)
    {
        char resposta;
        scanf(" %c", &resposta);
        if(resposta == 's')
        {
            dados->status = 1;
            break;
        }
        else if(resposta == 'n')
        {
            dados->status = 0;
            break;
        }
        else printf("\nRESPOSTA INVÁLIDA\n");
    }
    return dados;
}

void ver_pedidos(ListaPedidos *lista_pedidos)
{
    No_pedidos *atual;
    No *produto_atual;
    atual = lista_pedidos->primeiro;
    for(int i = 0;i<lista_pedidos->tamanho;i++)
    {
        produto_atual = atual->lista->primeiro;

        printf("Código de entrega: %s || Código do pedido: %d ||",atual->dados->codigo_entrega,atual->dados->codigo_pedido);
        if(atual->dados->status == 1)printf("FECHADO\n");
        else printf("EM ABERTO\n");
        for(int j = 0;j<atual->lista->tamanho;j++)
        {
            printf("Código do produto: %d ||", produto_atual->codigo_produto);
            printf("Quantidade: %d ||",produto_atual->quantidade);
            printf("Volume total: %d\n",produto_atual->volume_total);
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
        else printf("\nRESPOSTA INVÁLIDA\n");
    }
}