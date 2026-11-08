#ifndef GERAL_MENU_H
#define GERAL_MENU_H

#include "lista_pedidos.h"
#include "fila_empacotamento.h"
#include "caixas.h"

void limpar_buffer(void);
void limpar_tela(void);
void pausar(void);

void cadastrar(Catalogo *catalogo);
void cadastrar_pedido(Codigos *codigos, ListaPedidos *lista_pedidos,Fila_Pedidos *fila,Catalogo *catalogo);
void produtos(Catalogo *Catalogo);
void pedidos(ListaPedidos *lista_pedidos);

#endif