
#include <stdio.h>
#include <stdlib.h>
#include "lista_produtos.h"
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

void cadastrar(Catalogo *catalogo) {
    printf("Cadastrar produto...\n");

    int cadastro = 1;
    while(cadastro == 1)
    {
        cadastrar_produto(catalogo);
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

void cadastrar_pedido(Codigos *codigos, ListaPedidos *lista_pedidos, Fila_Pedidos *fila, Catalogo *catalogo)
{
    printf("Cadastrar pedido...\n");

    ListaProdutos *lista = criar_lista_produtos();

    if(lista == NULL)
    {
        printf("Não foi possível criar o pedido.\n");
        return;
    }

    int pedido = 1;

    while(pedido == 1)
    {
        printf("Digite o código do produto:\n");
        Produto *produto;

        while(1)
        {
            int codigo;
            scanf("%d", &codigo);
            No_catalogo *comeco = raiz(catalogo);
            produto = buscar_produto(comeco,codigo);

            if(produto == NULL)
            {
                printf("Não existe um produto com esse código, digite novamente:\n");
            }
            else break;
        }

        if(buscar_produto_pedido(lista,produto) == 1)
        {
            modificar_pedidos(lista,produto);
        }
        else inserir_produtos(lista,produto);

        printf("DESEJA INSERIR MAIS PRODUTOS NO PEDIDO? (s/n)\n");

        while(1)
        {
            char resposta;
            scanf(" %c", &resposta);

            if(resposta == 's')
            {
                break;
            }
            else if(resposta == 'n')
            {
                pedido = 0;
                break;
            }
            else
            {
                printf("RESPOSTA INVÁLIDA\n");
            }
        }
    }

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

    while(1)
    {
        char resposta;
        scanf(" %c", &resposta);

        if(resposta == 's')
        {
            inserir_lista_pedidos(lista,dados,lista_pedidos);

            if(consultar_status_pedido(dados) == 1) inserir_fila_pedidos(lista_pedidos->ultimo,fila);

            cadastrar_pedido(codigos,lista_pedidos,fila,catalogo);
            break;
        }
        else if(resposta == 'n')
        {
            inserir_lista_pedidos(lista,dados,lista_pedidos);

            if(consultar_status_pedido(dados) == 1) inserir_fila_pedidos(lista_pedidos->ultimo,fila);

            break;
        }
        else
        {
            printf("RESPOSTA INVÁLIDA\n");
        }
    }
}

void produtos(Catalogo *catalogo)
{
    int op;
    do
    {
        printf("=== PRODUTOS ==\n\n");
        printf("1. Ver produtos\n");
        printf("2. Modificar produtos\n");
        printf("3. Remover produtos\n");
        printf("0. Voltar\n");

        printf("Digite sua opção: ");
        scanf("%d", &op);
        limpar_buffer();

        switch(op)
        {
            case 1:
                ver_produtos(raiz(catalogo));
                pausar();
                break;
            case 2:
                modificar_produtos(catalogo);
                pausar();
                break;
            case 3:
                remover_produto(catalogo);
                pausar();
                break;
            case 0:
                return;
            default:
                printf("Opcao invalida!\n");
                pausar();
                break;
        }
    }while(op != 0);
}

void selecionar_pedido_modificar(ListaPedidos *lista_pedidos, Catalogo *catalogo)
{
    printf("Digite o código do pedido que deseja alterar:\n");

    int codigo;
    scanf("%d", &codigo);

    No_pedidos *atual = lista_pedidos->primeiro;

    while(atual != NULL)
    {
        if(consultar_codigo_pedido(atual->dados) == codigo) break;
        atual = atual->proximo;
    }

    if(atual == NULL)
    {
        printf("Não existe um pedido com esse código!\n");
        return;
    }

    if(consultar_status_pedido(atual->dados) == 1 || consultar_empacotado_pedido(atual->dados) == 1)
    {
        printf("Não é possível modificar um pedido fechado ou já empacotado!\n");
        return;
    }

    No *atual_produto = atual->lista->primeiro;

    while(atual_produto != NULL)
    {
        printf("Código produto:%d || quantidade produto: %d\n",atual_produto->codigo_produto,atual_produto->quantidade);
        atual_produto = atual_produto->proximo;
    }

    printf("Digite o código do produto que deseja alterar a quantidade:\n");

    int codigo_produto;
    scanf("%d", &codigo_produto);

    atual_produto = atual->lista->primeiro;

    while(atual_produto != NULL)
    {
        if(atual_produto->codigo_produto == codigo_produto) break;
        atual_produto = atual_produto->proximo;
    }

    if(atual_produto == NULL)
    {
        printf("Não existe um produto com esse código no pedido!\n");
        return;
    }

    Produto *produto = buscar_produto(raiz(catalogo),codigo_produto);

    if(produto == NULL)
    {
        printf("Produto não encontrado no catálogo!\n");
        return;
    }

    modificar_pedidos(atual->lista,produto);
}

void pedidos(ListaPedidos *lista_pedidos, Catalogo *catalogo,Fila_Pedidos *fila)
{
    int op;

    if(lista_pedidos->primeiro == NULL)
    {
        printf("AINDA NÃO EXISTEM PEDIDOS\n");
        return;
    }

    do
    {
        printf("=== PEDIDOS ==\n\n");
        printf("1. Ver pedidos\n");
        printf("2. Modificar pedidos\n");
        printf("3. Fechar Pedidos\n");
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
            case 2:
                selecionar_pedido_modificar(lista_pedidos,catalogo);
                pausar();
                break;
            case 3:
                fechar_pedidos(lista_pedidos,fila);
                pausar();
                break;
            case 0:
                return;
            default:
                printf("Opcao invalida!\n");
                pausar();
                break;
        }
    }while(op != 0);
}
