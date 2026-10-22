
#include "caixas.h"

Fila_caixas *criar_fila_caixas()
{
    Fila_caixas *fila = (Fila_caixas*) malloc(sizeof(Fila_caixas));
    if(fila == NULL) return NULL;

    fila->cabeca = NULL;
    fila->cauda = NULL;
    fila->tamanho = 0;

    return fila;
}

Caixa *criar_caixa()
{
    Caixa *caixa = (Caixa*)malloc(sizeof(Caixa));
    if(caixa == NULL)
    {
        printf("Não foi possível criar a caixa\n");
        return NULL;
    }
    caixa->volume = 0;
    caixa->topo = NULL;
    return caixa;
}




No *inserir_na_caixa(No *produto_atual, Caixa *caixa)
{
    No *novo = (No*)malloc(sizeof(No));
    if(novo==NULL)
    {
        printf("Não foi possivel inserir o produto na caixa");
        return NULL;
    }

    novo->codigo_produto=produto_atual->codigo_produto;
    novo->quantidade = 1;
    novo->volume = produto_atual->volume;


    if(caixa->topo == NULL)
    {
        caixa->topo = novo;
        caixa->topo->proximo = NULL;
        caixa->volume+=novo->volume;
    }
    else
    {
        No *topo_antigo = caixa->topo;
        caixa->topo = novo;
        caixa->topo->proximo = topo_antigo;
        caixa->volume+=novo->volume;
    }

    produto_atual->quantidade-=1;
    return novo;
}

No_caixa *inserir_fila_caixas(Caixa *caixa, Fila_caixas *fila_caixas)
{
    No_caixa *novo = (No_caixa*)malloc(sizeof(No_caixa));

    if(novo== NULL)
    {
        printf("Não foi possivel inserir a caixa na fila de caixas");
        return NULL;
    }

    novo->caixa = caixa;
    novo->proximo = NULL;

    if(fila_caixas->cabeca == NULL)
    {
        fila_caixas->cabeca = novo;
        fila_caixas->cauda =novo;
        fila_caixas->tamanho++;
    }
    else
    {
        fila_caixas->cauda->proximo = novo;
        fila_caixas->cauda = novo;
        fila_caixas->tamanho++;
    }
    return novo;
}


void empacotar(Fila_Pedidos *fila_pedidos,Fila_caixas *fila_caixas)
{

    int codigo_atual;
    int volume_maximo_caixa = 10;

    No_pedidos *pedido_atual = fila_pedidos->cabeca->pedido;
    No *produto_atual = pedido_atual->lista->primeiro;
    while(fila_pedidos->cabeca !=NULL)
    {
        codigo_atual = pedido_atual->dados->codigo_entrega;
        Caixa *caixa = criar_caixa();

        while(pedido_atual != NULL)
        {
            if(caixa->volume+produto_atual->volume>volume_maximo_caixa)
            {
                caixa->codigo_entrega = codigo_atual;
                Caixa *nova_caixa = criar_caixa();
                inserir_fila_caixas(caixa,fila_caixas);
                caixa = nova_caixa;
            }
            else if(produto_atual->quantidade!=0)
            {
                inserir_na_caixa(produto_atual,caixa);
            }
            else
            {
                produto_atual = produto_atual->proximo;
            }

            if(produto_atual == NULL)
            {
                caixa->codigo_entrega = codigo_atual;
                Caixa *nova_caixa = criar_caixa();
                inserir_fila_caixas(caixa,fila_caixas);
                caixa = nova_caixa;
                pedido_atual = pedido_atual->proximo;
                produto_atual = pedido_atual->lista->primeiro;               
            }
        }
    }
}
