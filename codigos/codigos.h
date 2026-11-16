
#ifndef CODIGOS_H
#define CODIGOS_H

typedef struct codigos Codigos;

Codigos *criar_codigos();

int obter_ultimo_codigo_pedido(Codigos *codigos);
int gerar_codigo_pedido(Codigos *codigos);

int obter_ultimo_codigo_caixa(Codigos *codigos);
int gerar_codigo_caixa(Codigos *codigos);

int obter_total_caixas(Codigos *codigos);
void incrementar_total_caixas(Codigos *codigos);

#endif
