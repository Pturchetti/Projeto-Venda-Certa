#ifndef CADASTRO_H
#define CADASTRO_H


typedef struct Produto{
    int codigo;
    char nome[80];
    int volume;
    int quantidade;
} Produto;


typedef struct No_catalogo No_catalogo;

typedef struct Catalogo Catalogo;

void cadastrar_produto(Catalogo *catalogo);

Catalogo *criar_catalogo();
No_catalogo *inserir_no_catalogo(Produto produto, Catalogo *catalogo);
Produto *buscar_produto(No_catalogo *atual, int codigo);


void ver_produtos(No_catalogo *comeco);

void modificar_produtos(Catalogo *catalogo);

No_catalogo *raiz(Catalogo *catalogo);

void remover_produto(Catalogo *catalago);
void remover_folha(No_catalogo *atual, No_catalogo *anterior,Catalogo *catalago);
void remover_pai_solo(No_catalogo *atual, No_catalogo *anterior,Catalogo *catalago);
void remover_pai_dois_filhos(No_catalogo *atual, No_catalogo *anterior,Catalogo *catalago);

#endif