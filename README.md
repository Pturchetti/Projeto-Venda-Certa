# Venda Certa

Sistema de simulação de gerenciamento de produtos, pedidos, empacotamento e expedição, desenvolvido em linguagem C para a disciplina de Estruturas de Dados.

O projeto integra diferentes estruturas de dados em um fluxo de atendimento: cadastro de produtos no catálogo, reserva de estoque nos pedidos, fechamento, empacotamento em caixas e carregamento de caminhões.

## Funcionalidades

- **Catálogo de produtos:** cadastro com código único, busca, listagem em ordem de código, edição de nome e estoque e remoção na BST. Na edição, Enter mantém o nome anterior.
- **Controle de estoque:** reserva de unidades ao inserir produtos nos pedidos, ajuste pela diferença ao modificar quantidades e devolução ao remover itens ou pedidos abertos, quando o produto ainda existe no catálogo.
- **Pedidos:** cadastro com código de entrega e prioridade; consulta ao histórico; edição de quantidades e remoção de itens enquanto abertos. Inserir novamente um produto já presente permite modificar o item existente.
- **Fechamento:** pedidos podem ser fechados no cadastro ou posteriormente. Apenas pedidos abertos e ainda não empacotados podem ser removidos. Remover o último item também remove o pedido aberto.
- **Empacotamento:** processamento dos pedidos fechados na ordem FIFO e distribuição das unidades em caixas de volume máximo 10. O histórico dos pedidos permanece disponível após o empacotamento e a expedição.
- **Prioridade de entrega:** caixas ordenadas por modalidade expressa, rápida e normal; dentro da mesma prioridade, a ordem de chegada é preservada.
- **Expedição:** cinco docas recebem caminhões de capacidades 30, 50 ou 80, com tamanhos sorteados. Cada caixa é carregada na primeira doca em que couber. Caminhões cheios saem imediatamente; se nenhuma doca comportar a próxima caixa, sai o caminhão com maior percentual de ocupação. Ao terminar a fila, saem os caminhões que ainda possuem carga.

## Estruturas de dados utilizadas

| Estrutura | Aplicação |
| --- | --- |
| Árvore de busca binária (BST) | Catálogo organizado pelo código do produto. |
| Listas simplesmente encadeadas | Histórico de pedidos e itens de cada pedido. |
| Fila FIFO | Pedidos fechados aguardando empacotamento. |
| Pilhas LIFO | Unidades de produtos armazenadas nas caixas. |
| Fila de prioridade estável | Caixas aguardando expedição, respeitando prioridade e ordem de chegada. |
| Vetores | Capacidades e espaço disponível nas cinco docas. |

A BST utiliza inserção comum, sem balanceamento automático. A ordem de cadastro influencia seu formato.

## Organização dos módulos

```text
.
├── main.c
├── Makefile
├── README.md
├── entradas_treino_50_produtos_10_pedidos.txt
├── cadastro/
├── lista_produtos/
├── lista_pedidos/
├── fila_empacotamento/
├── caixas/
├── caminhoes/
├── geral_menu/
└── codigos/
```

Cada módulo possui os arquivos `.c` e `.h` correspondentes:

- `cadastro`: catálogo de produtos e operações da BST.
- `lista_produtos`: lista de itens e reserva inicial de estoque.
- `lista_pedidos`: dados, histórico, alterações, remoções e fechamento dos pedidos.
- `fila_empacotamento`: fila FIFO de pedidos fechados.
- `caixas`: empilhamento, empacotamento e fila de prioridade das caixas.
- `caminhoes`: simulação das docas, carregamento e expedição.
- `geral_menu`: menus e integração das operações.
- `codigos`: geração dos identificadores de pedidos e caixas e contagem de caixas concluídas.

O `main.c` e o `Makefile` ficam na raiz. Os arquivos `.o` e `.d` são gerados junto aos fontes durante a compilação; os `.d` registram as dependências dos cabeçalhos para recompilar os módulos afetados.

## Compilação

O ambiente de execução documentado é Linux. São necessários GCC com suporte a C11 e GNU Make. A execução com dados de treinamento também utiliza Bash e os comandos `cat` e `stdbuf`, do GNU Coreutils.

Na pasta principal do projeto, execute:

```bash
make
```

O executável gerado é `venda_certa`.

Para recompilar do zero:

```bash
make clean && make
```

## Execução

### Iniciar sem dados

```bash
./venda_certa
```

O programa apresenta um menu para cadastrar produtos e pedidos, consultar e modificar os registros, empacotar e despachar as caixas.

### Iniciar com dados de treinamento

O arquivo `entradas_treino_50_produtos_10_pedidos.txt` cadastra **50 produtos com nomes identificáveis e 10 pedidos**, sendo **4 abertos e 6 fechados**. Os produtos são inseridos em uma ordem que distribui os nós entre os dois lados da BST. O arquivo também consulta os produtos, os pedidos e a FIFO, retornando ao menu principal sem empacotar ou despachar.

Execute no Bash, a partir da pasta principal:

```bash
{ cat entradas_treino_50_produtos_10_pedidos.txt; cat; } | stdbuf -o0 ./venda_certa
```

O primeiro `cat` fornece as entradas do arquivo; o segundo mantém a entrada aberta para continuar utilizando o menu pelo terminal. O `stdbuf -o0` faz as mensagens aparecerem imediatamente, evitando que avisos para digitar opções fiquem retidos no buffer de saída.

Para encerrar toda essa execução, use `Ctrl+C`. Se escolher a opção `0` do programa e o terminal continuar aguardando, use `Ctrl+D` para encerrar também o segundo `cat`.

Os dados ficam apenas em memória. Encerrar o programa descarta a sessão; executar o comando novamente carrega os dados de treinamento em uma nova sessão.

## Limpeza dos arquivos compilados

```bash
make clean
```

Esse comando remove o executável e os arquivos `.o` e `.d`, preservando os fontes e o arquivo de treinamento.

## Limites e escopo

- Interface de terminal, sem persistência em arquivo ou banco de dados.
- Nomes de produtos com até 79 bytes e códigos de entrega com até 99 bytes; caracteres acentuados podem ocupar mais de um byte em UTF-8.
- Volume individual dos produtos entre 1 e 10; caixas com capacidade 10.
- A edição do estoque no catálogo define a quantidade disponível naquele momento.
- Os itens dos pedidos guardam cópias do nome e do volume do produto. Alterações posteriores no catálogo não reescrevem esses registros.
- Há validações nos fluxos revisados, mas o programa não oferece tratamento completo de entradas inválidas em todos os menus. Nos demais campos, utilize os tipos e opções solicitados.
- A simulação não gerencia frota, rotas ou persistência de caminhões entre operações de expedição.

## Contexto acadêmico

Trabalho acadêmico desenvolvido individualmente para a disciplina de Estruturas de Dados, no curso de Engenharia de Computação da Universidade Federal de Santa Maria. O objetivo é aplicar operações de busca, inserção, remoção e ordenação e integrar listas, árvores, filas, pilhas e vetores em uma simulação.

## Autoria

**Desenvolvedor:** Pedro Nunes Turchetti\
**Curso:** Engenharia de Computação\
**Instituição:** Universidade Federal de Santa Maria (UFSM)
