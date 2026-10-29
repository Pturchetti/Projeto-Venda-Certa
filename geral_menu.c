#include <stdio.h>
#include <stdlib.h>
#include "lista_produtos.h"
#include "json_produtos.h"
#include "cadastro.h"
#include "lista_pedidos.h"
#include "fila_empacotamento.h"

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limpar_tela() {
    printf("\033[H\033[2J");
}

void pausar() {
    printf("\nPressione [Enter] para continuar...");
    getchar();
    limpar_tela();
}

void cadastrar() {
    printf("Cadastrar produto...\n");

    int cadastro = 1;
    while(cadastro == 1)
    {
        cadastrar_produto();
        while(1)
        {

            printf("\n Deseja cadastrar mais um produto(s/n)");

            char resposta; 
            scanf(" %c", &resposta);

            if(resposta == 's')
            {
                limpar_buffer();
                break;
            }
            else if(resposta == 'n')
            {
                cadastro = 0;
                break;
            }
            else printf("RESPOSTA INVÁLIDA\n");

        }
    }
}

void cadastrar_pedido(Codigos *codigos, ListaPedidos *lista_pedidos, Fila_Pedidos *fila) {
    printf("Cadastrar pedido...\n");

    ListaProdutos *lista = criar_lista_produtos();

    if (lista == NULL) {
        printf("Não foi possível criar o pedido.\n");
        return;
    }

    Produto *catalogo = NULL;
    int tamanho_catalogo = 0;

    if (!json_produtos_carregar("produtos.json", &catalogo, &tamanho_catalogo)) {
        printf("Não foi possível carregar os produtos.\n");
        free(lista);
        return;
    }

    int pedido = 1;

    while (pedido == 1) {
        Produto produto = buscar_produto(catalogo, tamanho_catalogo);
        
        if(produto.codigo == -1)
        {
            printf("INSERÇÃO DE PRODUTO CANCELADA!\n");
            pedido = 0;
            break;
        }

        inserir_produtos(lista, produto);

        printf("DESEJA INSERIR MAIS PRODUTOS NO PEDIDO? (s/n)\n");

        while (1) {
            char resposta;
            scanf(" %c", &resposta);

            if (resposta == 's') {
                break;
            } else if (resposta == 'n') {
                pedido = 0;
                break;
            } else {
                printf("RESPOSTA INVÁLIDA\n");
            }
        }
    }

    free(catalogo);

    if(lista->tamanho == 0)
    {
        free(lista);
        return;
    }

    dados_pedido *dados = registrar_dados(codigos);
    if(dados == NULL)
    {
        printf("NÃO FOI POSSIVEL SALVAR OS DADOS, TENTE NOVAMENTE MAIS TARDE\n");
        for(int i = 0;i<lista->tamanho;i++)
        {
            No *remover = lista->primeiro;
            lista->primeiro = lista->primeiro->proximo;
            free(remover);
        }
        free(lista);
        return;
    }

    printf("DESEJA REGISTRAR UM NOVO PEDIDO? (s/n)\n");

    while (1) {
        char resposta;
        scanf(" %c", &resposta);

        if (resposta == 's') {
            inserir_lista_pedidos(lista, dados,lista_pedidos);

            if(dados->status == 1) inserir_fila_pedidos(lista_pedidos->ultimo,fila);

            cadastrar_pedido(codigos, lista_pedidos,fila);
            break;
        } else if (resposta == 'n') {
            inserir_lista_pedidos(lista, dados,lista_pedidos);

            if(dados->status == 1) inserir_fila_pedidos(lista_pedidos->ultimo,fila);

            break;
        } 
        else {
            printf("RESPOSTA INVÁLIDA\n");
        }
    }
}




void produtos()
{
    Produto *catalogo = NULL;
    int tamanho_catalogo = 0;
    int op;


    if (!json_produtos_carregar("produtos.json", &catalogo, &tamanho_catalogo)) {
        printf("Não foi possível carregar os produtos.\n");
        return;
    }

    do{
        printf("=== PRODUTOS ==\n\n");
        printf("1. Ver produtos\n");
        printf("2. Modificar produtos\n");
        printf("0. Voltar\n");

        printf("Digite sua opção: ");
        scanf("%d", &op);
        limpar_buffer();
        switch(op)
        {
            case 1:
                ver_produtos(catalogo,tamanho_catalogo);
                pausar();
                break;
            case 2:
                modificar_produtos(catalogo,tamanho_catalogo);
                pausar();
                break;
            case 0:
                free(catalogo);
                return;
            default:
                printf("Opcao invalida!\n");
                pausar();
                break;
        }
    }while(op !=0);

}


void pedidos(ListaPedidos *lista_pedidos)
{
    int op;
    if(lista_pedidos->primeiro == NULL)
    {
        printf("AINDA NÃO EXISTEM PEDIDOS\n");
        return;
    }
    do{
        printf("=== PEDIDOS ==\n\n");
        printf("1. Ver pedidos\n");
        printf("2. Modificar pedidos\n");
        printf("0. Voltar\n");

        printf("Digite sua opção: ");
        scanf("%d", &op);
        limpar_buffer();
        switch(op)
        {
            case 1:
                ver_pedidos(lista_pedidos);
                pausar();
                break;
            /* 
            case 2:
                modificar_pedidos(lista_pedidos);
                pausar();
                break;*/
            case 0:
                return;
            default:
                printf("Opcao invalida!\n");
                pausar();
                break;
        }
    }while(op !=0);

}