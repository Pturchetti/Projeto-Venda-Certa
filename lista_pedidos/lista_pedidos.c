#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "lista_pedidos.h"
#include "fila_empacotamento.h"

void limpar() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

typedef struct dados_pedido{
    int codigo_pedido;
    char codigo_entrega[100];
    int status;
    int empacotado;
    int prioridade;
}dados_pedido;


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

    dados->codigo_pedido = gerar_codigo_pedido(codigos);
    dados->empacotado = 0;

    printf("DIGITE O CÓDIGO DE ENTREGA: ");
    limpar();
    fgets(dados->codigo_entrega,100,stdin);


    printf("Digite a prioridade do pedido\n");
    printf("Expresso - 1\n");
    printf("Rápido - 2\n");
    printf("Normal - 3\n");
    while(1)
    {
        scanf("%d", &dados->prioridade);
        if(dados->prioridade != 1 && dados->prioridade != 2 && dados->prioridade !=3)
        {
            printf("Opção inválida,digite novamente\n");
        }
        else break;
    }
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

        printf("Código de entrega: %s Código do pedido: %d ||",atual->dados->codigo_entrega,atual->dados->codigo_pedido);
        if(atual->dados->status == 1)printf("FECHADO ||");
        else printf("EM ABERTO ||");

        if(atual->dados->empacotado == 1)printf("EMPACOTADO\n");
        else printf("NÃO EMPACOTADO\n");
        
        for(int j = 0;j<atual->lista->tamanho;j++)
        {
            printf("Código do produto: %d ||", produto_atual->codigo_produto);
            printf("Nome: %s ||", produto_atual->nome);
            printf("Quantidade: %d ||",produto_atual->quantidade);
            printf("Volume do produto: %d\n",produto_atual->volume);
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

void modificar_pedidos(ListaProdutos *lista, Produto *produto)
{
    if(lista == NULL || produto == NULL)
    {
        printf("Não foi possível acessar os dados para modificar o pedido!\n");
        return;
    }

    No *atual_produto = lista->primeiro;

    while(atual_produto != NULL)
    {
        if(atual_produto->codigo_produto == produto->codigo) break;
        atual_produto = atual_produto->proximo;
    }

    if(atual_produto == NULL)
    {
        printf("Produto não encontrado no pedido!\n");
        return;
    }
    printf("Deseja alterar a quantidade ou remover o produto?\n");
    printf("1 - Nova quantidade\n");
    printf("2 - Remover produto\n");

    int resposta;
    while(1)
    {
        if(scanf("%d", &resposta) != 1)
        {
            limpar();
            printf("Opção inválida, digite novamente:\n");
            continue;
        }
        if(resposta == 1)
        {
            break;
        }
        else if(resposta == 2)
        {
            remover_produto_pedido(lista,atual_produto,produto);
            return;
        }
        else printf("Opção inválida, digite novamente:\n");
    }
    printf("Digite a nova quantidade:\n");

    int nova_quantidade;

    while(1)
    {
        scanf("%d", &nova_quantidade);

        if(nova_quantidade < 1 || nova_quantidade > produto->quantidade + atual_produto->quantidade)
        {
            printf("Quantidade superior ao estoque ou insuficiente! Digite novamente\n");
        }
        else
        {
            produto->quantidade = produto->quantidade + atual_produto->quantidade - nova_quantidade;
            atual_produto->quantidade = nova_quantidade;

            printf("Quantidade do produto alterada com sucesso!\n");
            break;
        }
    }
}

void fechar_pedidos(ListaPedidos *lista_pedidos,Fila_Pedidos *fila)
{
    No_pedidos *atual = lista_pedidos->primeiro;
    int pedidos_abertos = 0;
    while(atual != NULL)
    {
        if(atual->dados->status == 0)
        {
            pedidos_abertos++;
            printf("Código entrega: %s || Código Pedido: %d || Prioridade: %d || Status: %d\n",atual->dados->codigo_entrega,atual->dados->codigo_pedido,atual->dados->prioridade,atual->dados->status);
        }
        atual = atual->proximo;
    }

    if(pedidos_abertos == 0)
    {
        printf("Não há pedidos em aberto\n");
        return;
    }
    printf("Digite o código do pedido que deseja alterar, caso não deseje alterar nenhum digite -1:\n");
    int resposta;
    while(1)
    {
        scanf("%d", &resposta);
        atual = lista_pedidos->primeiro;
        while(atual !=NULL)
        {
            if(resposta == -1) return;
            else if(atual->dados->codigo_pedido == resposta && atual->dados->status == 0)
            {
                atual->dados->status = 1;
                if(inserir_fila_pedidos(atual, fila) == NULL)
                {
                    atual->dados->status = 0;
                    printf("Não foi possível fechar o pedido!\n");
                    return;
                }
                return;
            }
            atual = atual->proximo;
        }
        printf("Pedido não encontrado ou não existente, digite novamente:\n");
    }
}


void remover_produto_pedido(ListaProdutos *lista,No *produto_atual, Produto *Produto_arvore)
{
    if(lista == NULL || produto_atual == NULL || Produto_arvore == NULL)
    {
        printf("Não foi possível acessar os dados para remover o produto!\n");
        return;
    }
    No *atual = lista->primeiro;
    No *anterior = NULL;
    while(atual != NULL && atual !=produto_atual)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if(atual == NULL)
    {
        printf("Produto não encontrado no pedido!\n");
        return;
    }

    No *remover = atual;

    if(anterior == NULL)
    {
        lista->primeiro = atual->proximo;
        Produto_arvore->quantidade+=atual->quantidade;
        lista->tamanho--;
    }
    else
    {
        anterior->proximo = atual->proximo;
        Produto_arvore->quantidade+=atual->quantidade;
        lista->tamanho--;
    }
    if(atual == lista->ultimo) lista->ultimo = anterior;
    free(remover);


}

void remover_pedido(No_pedidos *pedido, ListaPedidos *lista_pedidos, Catalogo *catalogo)
{
    if(pedido == NULL || lista_pedidos == NULL || catalogo == NULL)
    {
        printf("Não foi possível acessar os dados para remover o pedido!\n");
        return;
    }
    No_pedidos *atual = lista_pedidos->primeiro;
    No_pedidos *anterior = NULL;

    while(atual != NULL && atual !=pedido)
    {
        anterior = atual;
        atual = atual->proximo;
    }


    if(atual == NULL)
    {
        printf("Pedido não encontrado!\n");
        return;
    }
    if(atual->dados->status != 0 || atual->dados->empacotado != 0)
    {
        printf("Não é possível remover um pedido fechado ou já empacotado!\n");
        return;
    }
    if(atual == lista_pedidos->ultimo) lista_pedidos->ultimo = anterior;

    No_pedidos *remover = atual;
    if(atual->lista->tamanho == 0)
    {
        if(anterior == NULL)
        {
            lista_pedidos->primeiro = atual->proximo;
            lista_pedidos->tamanho--;
            free(remover->lista);
            free(remover->dados);
            free(remover);
        }
        else
        {
            anterior->proximo = atual->proximo;
            lista_pedidos->tamanho--;
            free(remover->lista);
            free(remover->dados);
            free(remover);
        }
    }
    else
    {
        No *produto_atual = atual->lista->primeiro;
        while(atual->lista->tamanho !=0)
        {
            Produto *produto_catalogo = buscar_produto(raiz(catalogo),produto_atual->codigo_produto);

            if(produto_catalogo != NULL)
            {
                produto_catalogo->quantidade+=produto_atual->quantidade;
            }
            No *produto_remover = produto_atual;
            produto_atual = produto_atual->proximo;
            free(produto_remover);
            atual->lista->tamanho--;
        }
        if(anterior == NULL)
        {
            lista_pedidos->primeiro = atual->proximo;
            lista_pedidos->tamanho--;
            free(remover->lista);
            free(remover->dados);
            free(remover);
        }
        else
        {
            anterior->proximo = atual->proximo;
            lista_pedidos->tamanho--;
            free(remover->lista);
            free(remover->dados);
            free(remover);
        }

    }
    if(lista_pedidos->tamanho == 0)
    {
        lista_pedidos->primeiro = NULL;
        lista_pedidos->ultimo = NULL;
    }
}


int consultar_codigo_pedido(dados_pedido *dados)
{
    return dados->codigo_pedido;
}

int consultar_prioridade_pedido(dados_pedido *dados)
{
    return dados->prioridade;
}

int consultar_status_pedido(dados_pedido *dados)
{
    return dados->status;
}

int consultar_empacotado_pedido(dados_pedido *dados)
{
    return dados->empacotado;
}

void alterar_status_pedido(dados_pedido *dados, int status)
{
    dados->status = status;
}

void alterar_empacotado_pedido(dados_pedido *dados, int empacotado)
{
    dados->empacotado = empacotado;
}

char *consultar_codigo_entrega(dados_pedido *dados)
{
    return dados->codigo_entrega;
}