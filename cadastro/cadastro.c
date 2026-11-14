
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastro.h"

void limpar_b() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


typedef struct No_catalogo{
    Produto produto;
    struct No_catalogo *esquerda;
    struct No_catalogo *direita;
} No_catalogo;

typedef struct Catalogo{
    No_catalogo *raiz;
    int tamanho;
} Catalogo;


Catalogo *criar_catalogo()
{
    Catalogo *catalogo = (Catalogo*) malloc(sizeof(Catalogo));
    if(catalogo == NULL)
    {
        printf("Não foi possível criar o catálogo!\n");
        return NULL;
    }

    catalogo->raiz = NULL;
    catalogo->tamanho = 0;

    return catalogo;
}

No_catalogo *inserir_no_catalogo(Produto produto, Catalogo *catalogo)
{
    No_catalogo *novo = (No_catalogo*)malloc(sizeof(No_catalogo));
    if(novo == NULL)
    {
        printf("Não foi possível cadastrar o produto!\n");
        return NULL;
    }

    novo->produto = produto;
    novo->direita = NULL;
    novo->esquerda = NULL;


    if(catalogo->raiz == NULL)
    {
        catalogo->raiz = novo;
        catalogo->tamanho++;
        printf("Produto cadastrado!\n");
        return novo;
    }
    else
    {
        No_catalogo *atual = catalogo->raiz;
        int direita = 0;
        int esquerda = 0;
        while(1)
        {
            if(produto.codigo > atual->produto.codigo)
            {
                if(atual->direita == NULL)
                {
                    direita = 1;
                    break;
                }
                atual = atual->direita;
            }

            else
            {
                if(atual->esquerda == NULL)
                {
                    esquerda = 1;
                    break;
                }
                atual = atual->esquerda;
            }
        }
        if(direita == 1)
        {
            atual->direita = novo;
            catalogo->tamanho++;
        }
        else
        {
            atual->esquerda = novo;
            catalogo->tamanho++;
        }
        printf("Produto cadastrado!\n");
        return novo;
    }
}

Produto *buscar_produto(No_catalogo *atual, int codigo)
{
    if(atual == NULL)
    {
        return NULL;
    }
    if(atual->produto.codigo == codigo)
    {
        return &atual->produto;
    }
    if(atual->produto.codigo > codigo)
    {
        return buscar_produto(atual->esquerda,codigo);
    }
    else return buscar_produto(atual->direita,codigo);
}


void cadastrar_produto(Catalogo *catalogo)
{
    Produto produto;

    printf("Digite o código do produto:\n");
    while(1)
    {
        int codigo;
        scanf("%d", &codigo);
        produto.codigo = codigo;
        No_catalogo *comeco = catalogo->raiz;
        Produto *busca = buscar_produto(comeco,codigo);
        if(busca != NULL)
        {
            printf("Já existe um produto com esse código, digite novamente:\n");
            limpar_b();
        }
        else break;
    }

    limpar_b();
    printf("\n");

    printf("Insira o nome do produto:\n");
    fgets(produto.nome,sizeof(produto.nome),stdin);
    produto.nome[strcspn(produto.nome, "\n")] = '\0';

    printf("\n");

    printf("Insira o volume do produto:\n");
    scanf("%d",&produto.volume);

    printf("\n");

    printf("Insira a quantidade do produto:\n");
    scanf("%d",&produto.quantidade);

    if(produto.volume<1 || produto.volume >10 || produto.quantidade<1)
    {
        printf("Volume ou quantidade errados!\n");
        return;
    }

    inserir_no_catalogo(produto,catalogo);

    limpar_b();
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
    Produto *produto;
    while(1)
    {
        int codigo;
        scanf("%d", &codigo);
        No_catalogo *comeco = catalogo->raiz;
        produto = buscar_produto(comeco,codigo);
        if(produto == NULL)
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

    produto->quantidade = nova_quantidade;

    printf("PRODUTO ALTERADO COM SUCESSO!\n");
}

void remover_produto(Catalogo *catalogo)
{
    printf("Digite o código do produto que deseja remover:\n");
    int codigo_produto;
    scanf("%d", &codigo_produto);

    Produto *produto;
    produto = buscar_produto(catalogo->raiz,codigo_produto);

    if(produto == NULL)
    {
        printf("produto não encontrado!\n");
        return;
    }
    printf("deseja realmente remover o produto %s?(s/n)",produto->nome);

    while(1)
    {
        char resposta;
        scanf(" %c", &resposta);
        if(resposta == 's') break;
        else if (resposta == 'n') return;
        else printf("Resposta inválida!\n");
    }

    No_catalogo *atual = catalogo->raiz;
    No_catalogo *anterior = NULL;
    while(atual->produto.codigo != produto->codigo)
    {
        if(produto->codigo>atual->produto.codigo)
        {
            anterior=atual;
            atual = atual->direita;
        }
        else
        {
            anterior=atual;
            atual=atual->esquerda;
        }
    }


    if(atual->esquerda == NULL && atual->direita == NULL)remover_folha(atual,anterior,catalogo);

    else if((atual->direita == NULL && atual->esquerda !=NULL)|| (atual->direita !=NULL && atual->esquerda == NULL))remover_pai_solo(atual,anterior,catalogo);

    else remover_pai_dois_filhos(atual,anterior,catalogo);
}

void remover_folha(No_catalogo *atual, No_catalogo *anterior,Catalogo *catalago)
{
    No_catalogo *remover = NULL;
    remover = atual;
    if(anterior == NULL) catalago->raiz = NULL;
    else if(atual == anterior->direita) anterior->direita = NULL;
    else anterior->esquerda = NULL;

    catalago->tamanho--;
    free(remover);
}

void remover_pai_solo(No_catalogo *atual, No_catalogo *anterior,Catalogo *catalago)
{
    No_catalogo *remover = NULL;
    if(anterior == NULL)
    {
        if(atual->direita != NULL) catalago->raiz = atual->direita;
        else catalago->raiz = atual->esquerda;

        free(atual);
        catalago->tamanho--;
    }
    else
    {
        if(atual->direita != NULL)
        {
            remover = atual;
            if(atual == anterior->direita) anterior->direita = atual->direita;
            else anterior->esquerda = atual->direita;

            free(remover);
            catalago->tamanho--;
        }
        else
        {
            remover = atual;
            if(atual==anterior->direita) anterior->direita = atual->esquerda;
            else anterior->esquerda = atual->esquerda;

            free(remover);
            catalago->tamanho--;
        }
    }
}

void remover_pai_dois_filhos(No_catalogo *atual, No_catalogo *anterior,Catalogo *catalago)
{
    No_catalogo *troca = atual;
    anterior = troca;
    atual = atual->direita;
    while(atual->esquerda != NULL)
    {
        anterior = atual;
        atual = atual->esquerda;
    }
    troca->produto.codigo = atual->produto.codigo;
    strcpy(troca->produto.nome,atual->produto.nome);
    troca->produto.quantidade = atual->produto.quantidade;
    troca->produto.volume = atual->produto.volume;

    if(atual->direita == NULL) remover_folha(atual,anterior,catalago);
    else remover_pai_solo(atual,anterior,catalago);
}


No_catalogo *raiz(Catalogo *catalogo)
{
    return catalogo->raiz;
}