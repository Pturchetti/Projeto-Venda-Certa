#ifndef GERAL_MENU_H
#define GERAL_MENU_H

#include "lista_pedidos.h"
#include "fila_empacotamento.h"

void limpar_buffer(void);
void limpar_tela(void);
void pausar(void);

void cadastrar(void);
void cadastrar_pedido(Codigos *codigos, ListaPedidos *lista_pedidos,
                      Fila_Pacotes *fila);
void produtos(void);
void pedidos(ListaPedidos *lista_pedidos);

#endif