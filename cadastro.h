#ifndef CADASTRO_H
#define CADASTRO_H

#define PRODUTO_NOME_MAX 80

typedef struct {
    int codigo;
    char nome[PRODUTO_NOME_MAX];
    int volume;
    int quantidade;
} Produto;

void cadastrar_produto();
#endif