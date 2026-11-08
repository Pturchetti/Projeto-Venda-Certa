#ifndef CADASTRO_H
#define CADASTRO_H

#define PRODUTO_NOME_MAX 80

typedef struct {
    int codigo;
    char nome[PRODUTO_NOME_MAX];
    int volume;
    int quantidade;
} Produto;


typedef struct No_catalogo{
    Produto produto;
    struct No_catalogo *esquerda;
    struct No_catalogo *direita;
}No_catalogo;

typedef struct Catalogo{
    No_catalogo *raiz;
    int tamanho;
}Catalogo;


void cadastrar_produto(Catalogo *catalogo);

Catalogo *criar_catalogo();
Produto buscar_produto(No_catalogo *atual, int codigo);
No_catalogo *inserir_no_catalogo(Produto produto, Catalogo *catalogo);


#endif