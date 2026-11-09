#ifndef CADASTRO_H
#define CADASTRO_H


typedef struct Produto{
    int codigo;
    char nome[80];
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

void ver_produtos(No_catalogo *comeco);

void modificar_produtos(Catalogo *catalogo);

void remover_produto(Catalogo *catalago);
void remover_folha(No_catalogo *atual, No_catalogo *anterior,Catalogo *catalago);
void remover_pai_solo(No_catalogo *atual, No_catalogo *anterior,Catalogo *catalago);
void remover_pai_dois_filhos(No_catalogo *atual, No_catalogo *anterior,Catalogo *catalago);

#endif