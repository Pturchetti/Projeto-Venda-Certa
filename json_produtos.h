
#ifndef JSON_PRODUTOS_H
#define JSON_PRODUTOS_H

#include <stddef.h>
#include "cadastro.h"

int json_produtos_carregar(
    const char *caminho,
    Produto **produtos,
    int *quantidade
);

int json_produtos_salvar(
    const char *caminho,
    const Produto produtos[],
    int quantidade
);

int json_produto_adicionar(Produto produto);


int json_produto_proximo_codigo(void);


#endif
