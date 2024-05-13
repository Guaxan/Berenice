# Sistema de Vendas - Berenice V3

Este é um sistema de vendas desenvolvido em C. Ele permite cadastrar produtos, realizar vendas, gerar relatórios de vendas e emitir cupons fiscais.

## Visão Geral

O sistema é composto por três arquivos principais:

1. `main.c`: Este arquivo contém a função principal (`main`) do programa. Ele é responsável por apresentar um menu para o usuário e chamar as funções apropriadas com base na opção selecionada.

2. `funcoes.c`: Neste arquivo estão definidas todas as funções relacionadas às operações de produtos e vendas. Isso inclui funções para cadastrar, exibir, atualizar e excluir produtos, realizar vendas, processar pagamentos, gerar relatórios e cupons fiscais, entre outras operações.

3. `cabecalho.h`: O arquivo de cabeçalho contém a definição da estrutura `estprod` para representar os produtos, bem como a declaração de todas as funções presentes em `funcoes.c`. Ele é incluído em `main.c` e `funcoes.c` para garantir que todas as funções e estruturas sejam conhecidas em ambos os arquivos.

## Compilação e Execução

Para compilar e executar o programa, você pode usar um compilador C compatível, como GCC. Aqui está um exemplo de como compilar o programa:

gcc main.c funcoes.c -o sistema_vendas

Isso irá compilar os arquivos `main.c` e `funcoes.c` e gerar um executável chamado `sistema_vendas`. Em seguida, você pode executar o programa usando o seguinte comando:

./sistema_vendas

## Tecnologias Utilizadas

- Linguagem de Programação: C
- Bibliotecas: Standard C Library (stdio.h, stdlib.h, string.h, time.h)