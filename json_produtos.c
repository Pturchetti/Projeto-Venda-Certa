#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "json_produtos.h"

#define MAX_ARQUIVO 1000000

static void ignorar_espacos(const char **p)
{
    while (isspace((unsigned char)**p))
        (*p)++;
}

static int esperar(const char **p, char caractere)
{
    ignorar_espacos(p);

    if (**p != caractere)
        return 0;

    (*p)++;
    return 1;
}

static int ler_string(
    const char **p,
    char *destino,
    size_t capacidade
)
{
    ignorar_espacos(p);

    if (**p != '"')
        return 0;

    (*p)++;

    size_t i = 0;

    while (**p != '\0' && **p != '"') {
        unsigned char c = (unsigned char)**p;
        (*p)++;

        if (c == '\\') {
            c = (unsigned char)**p;

            if (c == '\0')
                return 0;

            (*p)++;

            switch (c) {
                case '"':  c = '"';  break;
                case '\\': c = '\\'; break;
                case '/':  c = '/';  break;
                case 'n':  c = '\n'; break;
                case 'r':  c = '\r'; break;
                case 't':  c = '\t'; break;
                case 'b':  c = '\b'; break;
                case 'f':  c = '\f'; break;
                default: return 0;
            }
        } else if (c < 32) {
            return 0;
        }

        if (i + 1 >= capacidade)
            return 0;

        destino[i++] = (char)c;
    }

    if (**p != '"')
        return 0;

    (*p)++;
    destino[i] = '\0';

    return 1;
}

static int ler_inteiro(const char **p, int *valor)
{
    ignorar_espacos(p);

    char *fim;
    long numero = strtol(*p, &fim, 10);

    if (fim == *p || numero < INT_MIN || numero > INT_MAX)
        return 0;

    *valor = (int)numero;
    *p = fim;

    return 1;
}

static int ler_produto(const char **p, Produto *produto)
{
    int codigo_lido = 0;
    int nome_lido = 0;
    int volume_lido = 0;
    int quantidade_lida = 0;

    if (!esperar(p, '{'))
        return 0;

    ignorar_espacos(p);

    if (**p == '}')
        return 0;

    while (1) {
        char chave[32];

        if (!ler_string(p, chave, sizeof(chave)))
            return 0;

        if (!esperar(p, ':'))
            return 0;

        if (strcmp(chave, "codigo") == 0) {
            if (codigo_lido ||
                !ler_inteiro(p, &produto->codigo))
                return 0;

            codigo_lido = 1;

        } else if (strcmp(chave, "nome") == 0) {
            if (nome_lido ||
                !ler_string(p, produto->nome,
                            sizeof(produto->nome)))
                return 0;

            nome_lido = 1;

        } else if (strcmp(chave, "volume") == 0) {
            if (volume_lido ||
                !ler_inteiro(p, &produto->volume))
                return 0;

            volume_lido = 1;

        } else if (strcmp(chave, "quantidade") == 0) {
            if (quantidade_lida ||
                !ler_inteiro(p, &produto->quantidade))
                return 0;

            quantidade_lida = 1;

        } else {
            return 0;
        }

        ignorar_espacos(p);

        if (**p == '}') {
            (*p)++;
            break;
        }

        if (!esperar(p, ','))
            return 0;
    }

    return codigo_lido && nome_lido &&
           volume_lido && quantidade_lida &&
           produto->codigo > 0 &&
           produto->nome[0] != '\0' &&
           produto->volume > 0 &&
           produto->quantidade >= 0;
}

int json_produtos_carregar(
    const char *caminho,
    Produto **produtos,
    int *quantidade
)
{
    if (caminho == NULL || produtos == NULL ||
        quantidade == NULL)
        return 0;

    *produtos = NULL;
    *quantidade = 0;

    FILE *arquivo = fopen(caminho, "rb");

    if (arquivo == NULL)
        return 0;

    if (fseek(arquivo, 0, SEEK_END) != 0) {
        fclose(arquivo);
        return 0;
    }

    long tamanho = ftell(arquivo);

    if (tamanho < 0 || tamanho > MAX_ARQUIVO) {
        fclose(arquivo);
        return 0;
    }

    rewind(arquivo);

    char *conteudo = malloc((size_t)tamanho + 1);

    if (conteudo == NULL) {
        fclose(arquivo);
        return 0;
    }

    size_t lidos = fread(conteudo, 1, (size_t)tamanho, arquivo);
    int erro = ferror(arquivo);
    fclose(arquivo);

    if (erro || lidos != (size_t)tamanho) {
        free(conteudo);
        return 0;
    }

    conteudo[lidos] = '\0';

    const char *p = conteudo;
    Produto *vetor = NULL;
    int total = 0;

    int valido = esperar(&p, '[');

    if (valido) {
        ignorar_espacos(&p);

        while (*p != ']') {
            Produto produto;

            if (*p == '\0' || !ler_produto(&p, &produto)) {
                valido = 0;
                break;
            }

            for (int i = 0; i < total; i++) {
                if (vetor[i].codigo == produto.codigo) {
                    valido = 0;
                    break;
                }
            }

            if (!valido)
                break;

            if (total >= (int)(MAX_ARQUIVO / sizeof(Produto))) {
                valido = 0;
                break;
            }

            Produto *novo = realloc(
                vetor, (size_t)(total + 1) * sizeof(Produto)
            );

            if (novo == NULL) {
                valido = 0;
                break;
            }

            vetor = novo;
            vetor[total++] = produto;

            ignorar_espacos(&p);

            if (*p == ']')
                break;

            if (!esperar(&p, ',')) {
                valido = 0;
                break;
            }
        }

        if (valido)
            valido = esperar(&p, ']');
    }

    ignorar_espacos(&p);

    if (*p != '\0')
        valido = 0;

    free(conteudo);

    if (!valido) {
        free(vetor);
        return 0;
    }

    *produtos = vetor;
    *quantidade = total;

    return 1;
}

int json_produtos_salvar(
    const char *caminho,
    const Produto produtos[],
    int quantidade
)
{
    if (caminho == NULL || quantidade < 0 ||
        (quantidade > 0 && produtos == NULL))
        return 0;

    FILE *arquivo = fopen(caminho, "w");

    if (arquivo == NULL)
        return 0;

    int valido = fprintf(arquivo, "[\n") >= 0;

    for (int i = 0; valido && i < quantidade; i++) {
        if (produtos[i].codigo <= 0 ||
            produtos[i].nome[0] == '\0' ||
            produtos[i].volume <= 0 ||
            produtos[i].quantidade < 0) {
            valido = 0;
            break;
        }

        if (fprintf(arquivo,
                    "  {\n"
                    "    \"codigo\": %d,\n"
                    "    \"nome\": \"",
                    produtos[i].codigo) < 0) {
            valido = 0;
            break;
        }

        for (size_t j = 0;
             produtos[i].nome[j] != '\0'; j++) {
            unsigned char c =
                (unsigned char)produtos[i].nome[j];

            if (c == '"' || c == '\\') {
                if (fputc('\\', arquivo) == EOF) {
                    valido = 0;
                    break;
                }

                if (fputc(c, arquivo) == EOF) {
                    valido = 0;
                    break;
                }
            } else if (c == '\n') {
                if (fputs("\\n", arquivo) == EOF)
                    valido = 0;
            } else if (c == '\r') {
                if (fputs("\\r", arquivo) == EOF)
                    valido = 0;
            } else if (c == '\t') {
                if (fputs("\\t", arquivo) == EOF)
                    valido = 0;
            } else if (c < 32) {
                valido = 0;
                break;
            } else {
                if (fputc(c, arquivo) == EOF)
                    valido = 0;
            }

            if (!valido)
                break;
        }

        if (!valido)
            break;

        if (fprintf(arquivo,
                    "\",\n"
                    "    \"volume\": %d,\n"
                    "    \"quantidade\": %d\n"
                    "  }%s\n",
                    produtos[i].volume,
                    produtos[i].quantidade,
                    i + 1 < quantidade ? "," : "") < 0) {
            valido = 0;
        }
    }

    if (valido && fprintf(arquivo, "]\n") < 0)
        valido = 0;

    if (fclose(arquivo) != 0)
        valido = 0;

    return valido;
}

int json_produto_adicionar(Produto produto)
{
    Produto *produtos = NULL;
    int quantidade = 0;

    if (!json_produtos_carregar(
            "produtos.json", &produtos, &quantidade)) {
        return 0;
    }

    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == produto.codigo) {
            free(produtos);
            return 0;
        }
    }

    Produto *novo = realloc(
        produtos, (size_t)(quantidade + 1) * sizeof(Produto));

    if (novo == NULL) {
        free(produtos);
        return 0;
    }

    produtos = novo;
    produtos[quantidade] = produto;
    quantidade++;

    int sucesso = json_produtos_salvar(
        "produtos.json", produtos, quantidade);

    free(produtos);
    return sucesso;
}

int json_produto_proximo_codigo(void)
{
    Produto *produtos = NULL;
    int quantidade = 0;

    if (!json_produtos_carregar(
            "produtos.json", &produtos, &quantidade)) {
        return -1;
    }

    int maior_codigo = 0;

    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].codigo > maior_codigo) {
            maior_codigo = produtos[i].codigo;
        }
    }

    free(produtos);

    if (maior_codigo == INT_MAX) {
        return -1;
    }

    return maior_codigo + 1;
}