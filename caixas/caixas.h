#ifndef CAIXAS_H
#define CAIXAS_H

#include "lista_pedidos.h"
#include "fila_empacotamento.h"
#include "lista_produtos.h"
#include "codigos.h"

typedef struct Caixa {
    int codigo_caixa;
    char codigo_entrega[100];
    int volume;
    int prioridade;
    No *topo;
} Caixa;

typedef struct No_caixa{
    Caixa *caixa;
    struct No_caixa *proximo;
}No_caixa;

typedef struct Fila_caixas{
    No_caixa *cabeca;
    No_caixa *cauda;
    int tamanho; 
}Fila_caixas;

Fila_caixas *criar_fila_caixas();
Caixa *criar_caixa();
No_caixa *inserir_fila_caixas(Caixa *caixa, Fila_caixas *fila_caixas);
No *inserir_na_caixa(No *produto_atual, Caixa *caixa);
int empacotar_pedido(No_pedidos *pedido_atual,char *codigo_atual,int volume_maximo_caixa, Fila_caixas *fila_caixas, Codigos *codigos);
void empacotar(Fila_Pedidos *fila_pedidos,Fila_caixas *fila_caixas, Codigos *codigos);
void ver_caixas(Fila_caixas *fila_caixas, Codigos *codigos);
void desempilhar(Caixa *caixa);
#endif
