
#include <stdio.h>
#include <stdlib.h>
#include "codigos.h"

struct codigos {
    int ultimo_codigo_pedido;
    int ultimo_codigo_caixa;
    int codigo_pedido_modificar;
    int total_caixas;
};

Codigos *criar_codigos()
{
    Codigos *codigos = (Codigos*)malloc(sizeof(Codigos));
    if(codigos == NULL)
    {
        printf("Não foi possível criar o controle de códigos!\n");
        return NULL;
    }

    codigos->ultimo_codigo_pedido = 0;
    codigos->ultimo_codigo_caixa = 0;
    codigos->codigo_pedido_modificar = -1;
    codigos->total_caixas = 0;

    return codigos;
}

int obter_ultimo_codigo_pedido(Codigos *codigos)
{
    return codigos->ultimo_codigo_pedido;
}

int gerar_codigo_pedido(Codigos *codigos)
{
    codigos->ultimo_codigo_pedido++;
    return codigos->ultimo_codigo_pedido;
}

int obter_ultimo_codigo_caixa(Codigos *codigos)
{
    return codigos->ultimo_codigo_caixa;
}

int gerar_codigo_caixa(Codigos *codigos)
{
    codigos->ultimo_codigo_caixa++;
    return codigos->ultimo_codigo_caixa;
}

int obter_total_caixas(Codigos *codigos)
{
    return codigos->total_caixas;
}

void incrementar_total_caixas(Codigos *codigos)
{
    codigos->total_caixas++;
}

int obter_codigo_pedido_modificar(Codigos *codigos)
{
    return codigos->codigo_pedido_modificar;
}

void alterar_codigo_pedido(Codigos *codigos, int codigo)
{
    codigos->codigo_pedido_modificar = codigo;
}

