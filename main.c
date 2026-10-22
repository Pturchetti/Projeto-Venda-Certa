#include <stdio.h>
#include "lista_pedidos.h"
#include "fila_empacotamento.h"
#include "geral_menu.h"

int main(void) {
    int op;
    Codigos codigos;
    codigos.ultimo_codigo_pedido = 0;
    ListaPedidos *lista_pedidos = criar_lista_pedidos();
    Fila_Pacotes *fila_pedidos_empacotar = criar_fila();

    if (lista_pedidos == NULL) {
        printf("Não foi possível criar a lista de pedidos.\n");
        return 1;
    }

    do {
        printf("=== VENDA CERTA ===\n\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Cadastrar Pedido\n");
        printf("3. Produtos\n");
        printf("4. Pedidos\n");
        printf("5. Ver fila\n");
        printf("0. Encerrar\n\n");

        printf("Informe sua opcao: ");
        scanf("%d", &op);

        // Remove o '\n' deixado pelo scanf
        limpar_buffer();

        switch (op) {
            case 1:
                cadastrar();
                pausar();
                break;

            case 2:
                cadastrar_pedido(&codigos,lista_pedidos,fila_pedidos_empacotar);
                pausar();
                break;

            case 3:
                produtos();
                pausar();
                break;
            
            case 4:
                pedidos(lista_pedidos);
                pausar();
                break;

            case 5:
                ver_fila(fila_pedidos_empacotar);
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