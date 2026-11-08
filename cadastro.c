#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastro.h"

void limpar_b() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


Catalogo *criar_catalogo()
{
    Catalogo *catalogo = (Catalogo*) malloc(sizeof(Catalogo));
    if(catalogo == NULL) return NULL;

    catalogo->raiz = NULL;
    catalogo->tamanho = 0;

    return catalogo;
}
No_catalogo *inserir_no_catalogo(Produto produto, Catalogo *catalogo)
{
    No_catalogo *novo = (No_catalogo*)malloc(sizeof(No_catalogo));
    if(novo == NULL) return NULL;

    novo->produto = produto;
    novo->direita = NULL;
    novo->esquerda = NULL;


    if(catalogo->raiz == NULL)
    {
        catalogo->raiz = novo;
        catalogo->tamanho++;
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
        return novo;
    }
}
Produto buscar_produto(No_catalogo *atual, int codigo)
{
    if(atual == NULL)
    {
        Produto produto = {0};
        produto.codigo = -1;
        return produto;
    }
    if(atual->produto.codigo == codigo)
    {
        return atual->produto;
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
        Produto busca = buscar_produto(comeco,codigo);
        if(busca.codigo !=-1)
        {
            printf("Já existe um produto com esse código, digite novamente:\n");
            limpar_b();
        }
        else break;
    }

    limpar_b();
    printf("\n");

    printf("INSIRA O NOME DO PRODUTO:\n");
    fgets(produto.nome,sizeof(produto.nome),stdin);
    produto.nome[strcspn(produto.nome, "\n")] = '\0';

    printf("\n");

    printf("INSIRA O VOLUME DO PRODUTO:\n");
    scanf("%d",&produto.volume);

    printf("\n");

    printf("INSIRA A QUANTIDADE DO PRODUTO:\n");
    scanf("%d",&produto.quantidade);
    
    if(produto.volume<=0 || produto.quantidade<0)
    {
        printf("Volume ou quantidade errados!\n");
        return;
    }

    inserir_no_catalogo(produto,catalogo);

    
    limpar_b();
}