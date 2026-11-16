# Venda Certa

Projeto desenvolvido em linguagem C para a disciplina de Estruturas de Dados.

## Organização dos arquivos

O projeto foi dividido em módulos, cada um com sua própria pasta, contendo os arquivos `.c` e `.h` correspondentes.

Os arquivos `.o` são gerados nessas mesmas pastas durante a compilação. O arquivo `main.c` e o `Makefile` permanecem na pasta principal.

## Compilação e execução

Para compilar o projeto, execute no terminal, a partir da pasta principal:
```
make
```

Para executar o programa com os dados de treinamento (50 produtos e 10 pedidos) e continuar utilizando o menu interativamente:
```bash
{ cat entradas_treino_50_produtos_10_pedidos.txt; cat; } | stdbuf -o0 ./venda_certa
```

O primeiro `cat` fornece os dados de treinamento ao programa. O segundo permite continuar digitando comandos normalmente após o cadastro automático.

O `stdbuf -o0` faz as mensagens aparecerem imediatamente, evitando que os avisos para digitar uma opção fiquem retidos no buffer de saída.

Para executar o programa sem os dados de treinamento:
```
./venda_certa
```

**Observação:** os comandos apresentados utilizam a sintaxe do Bash e devem ser executados na pasta principal do projeto.
