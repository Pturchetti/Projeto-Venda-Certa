#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastro.h"
#include "json_produtos.h"

void limpar_b() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void cadastrar_produto()
{
    Produto produto;

    produto.codigo = json_produto_proximo_codigo();

    if (produto.codigo == -1)
    {
        printf("Erro ao gerar o código do produto.\n");
        return;
    }
    
    printf("\n");

    printf("INSIRA O NOME DO PRODUTO:\n");
    fgets(produto.nome,sizeof(produto.nome),stdin);
    produto.nome[strcspn(produto.nome, "\n")] = '\0';

    printf("\n");

    printf("INSIRA O VOLUME DO PRODUTO:\n");
    scanf("%d",&produto.volume);

    printf("\n");

    printf("INSIRA A QUANTIDADE DO PRODUTO:\n");
    scanf("%d",&produto.quantidade);
    
    if(produto.volume<=0 || produto.quantidade<0)
    {
        printf("Volume ou quantidade errados!\n");
        return;
    }


    if (json_produto_adicionar(produto)) {
    printf("Produto cadastrado com sucesso!\n");
    }
    else
    {
        printf("Erro ao cadastrar o produto.\n");
    }
    limpar_b();
}