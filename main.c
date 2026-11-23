#include <stdio.h>
#include <stdlib.h>
#include "lista_pedidos.h"
#include "fila_empacotamento.h"
#include "geral_menu.h"
#include "cadastro.h"
#include "caminhoes.h"

int main(void) {
    int op = -1;

    Codigos *codigos = criar_codigos();
    if(codigos == NULL) return 1;
    ListaPedidos *lista_pedidos = criar_lista_pedidos();
    Fila_Pedidos *fila_pedidos_empacotar = criar_fila();
    Fila_caixas *fila_caixas = criar_fila_caixas();
    Catalogo *catalogo = criar_catalogo();

    if (lista_pedidos == NULL || fila_pedidos_empacotar == NULL || fila_caixas == NULL || catalogo == NULL) {
        printf("Não foi possível iniciar o sistema.\n");
        free(codigos);
        free(lista_pedidos);
        free(fila_pedidos_empacotar);
        free(fila_caixas);
        free(catalogo);
        return 1;
    }

    do {
        printf("=== VENDA CERTA ===\n\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Cadastrar Pedido\n");
        printf("3. Produtos\n");
        printf("4. Pedidos\n");
        printf("5. Ver fila\n");
        printf("6. Empacotar\n");
        printf("7. Ver caixas\n");
        printf("8. Despachar\n");
        printf("0. Encerrar\n\n");

        printf("Informe sua opcao: ");
        int leitura = scanf("%d", &op);
        if(leitura == EOF) break;
        if(leitura != 1)
        {
            limpar_buffer();
            printf("Opção inválida, digite um número!\n");
            continue;
        }

        // Remove o '\n' deixado pelo scanf
        limpar_buffer();

        switch (op) {
            case 1:
                cadastrar(catalogo);
                pausar();
                break;

            case 2:
                cadastrar_pedido(codigos,lista_pedidos,fila_pedidos_empacotar,catalogo);
                pausar();
                break;

            case 3:
                produtos(catalogo);
                pausar();
                break;
            
            case 4:
                pedidos(lista_pedidos, catalogo,fila_pedidos_empacotar);
                pausar();
                break;

            case 5:
                ver_fila(fila_pedidos_empacotar);
                pausar();
                break;

            case 6:
                empacotar(fila_pedidos_empacotar, fila_caixas,codigos);
                pausar();
                break;


            case 7:
                ver_caixas(fila_caixas,codigos);
                pausar();
                break;

            case 8:
                caminhoes(fila_caixas);
                pausar();
                break;
            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                pausar();
                break;
        }

    } while (op != 0);

    return 0;
}
// ADICIONAR O STATUS DE EMPACOTADO OU NÃO DOS PEDIDOS