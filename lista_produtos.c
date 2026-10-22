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


Produto buscar_produto(Produto catalogo[], int tamanho)
{
    printf("QUANTIDADE DE PRODUTOS DIFERENTES NO CATÁLOGO:%d\n", tamanho);
    while(1)
    {
        printf("DIGITE O CODIGO DO PRODUTO QUE QUER BUSCAR(1 a %d)\n",tamanho);

        int codigo;
        scanf("%d", &codigo);

        for(int i = 0;i<tamanho;i++)
        {
            if(catalogo[i].codigo == codigo)
            {
                return catalogo[i];
            }
        }

        printf("PRODUTO NÃO ENCONTRADO!\n");
        while(1)
        {
            printf("DESEJA PROCURAR NOVAMENTE?(s/n)");
            char resposta;
            scanf(" %c",&resposta);

            if(resposta== 's')
            {
                break;
            }
            else if(resposta == 'n')
            {
                Produto cancelado = {0};
                cancelado.codigo = -1;
                return cancelado;
            }
            else printf("RESPOSTA INVÁLIDA\n");
        }
    }
}


No *inserir_produtos(ListaProdutos *lista, Produto produto)
{
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



void ver_produtos(Produto catalogo[],int tamanho)
{
    for(int i =0;i<tamanho;i++)
    {
        printf("Código: %d || Nome: %s || Volume: %d || Quantidade: %d\n",catalogo[i].codigo,catalogo[i].nome,catalogo[i].volume,catalogo[i].quantidade);
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

void modificar_produtos(Produto catalogo[], int tamanho)
{
    Produto produto = buscar_produto(catalogo, tamanho);
    if(produto.codigo == -1)
    {
        printf("MODIFICAÇÃO DE PRODUTO CANCELADA!\n");
        return;
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

    for(int i = 0; i < tamanho; i++)
    {
        if(produto.codigo == catalogo[i].codigo)
        {
            catalogo[i].quantidade = nova_quantidade;
            break;
        }
    }

    if(!json_produtos_salvar("produtos.json", catalogo, tamanho))
    {
        printf("NÃO FOI POSSÍVEL SALVAR AS ALTERAÇÕES NO JSON.\n");
        return;
    }

    printf("PRODUTO ALTERADO COM SUCESSO!\n");
}