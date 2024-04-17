#include <stdio.h>  // Biblioteca para entrada e saída, fornece funções como printf() e scanf().
#include <stdlib.h> // Biblioteca para alocação e liberação de memória dinâmica. Contém funções como malloc() e free().
#include <string.h> // Biblioteca para manipulação de strings, fornece funções para manipular e trabalhar com strings em C.
#include <time.h>   // Biblioteca para manipulação de tempo, como obter a data e a hora atual.


#ifndef FUNCAO_H_INCLUDED
#define FUNCAO_H_INCLUDED

// Definição da estrutura que representa um produto
typedef struct
{
    int codigo;            // Código do produto
    char nome[25];         // Nome do produto
    float preco;           // Preço do produto
    int quantestoque;      // Quantidade em estoque
    int quantvendida;      // Quantidade vendida para uso no relatório
    int quantvendidacupom; // Quantidade vendida para uso no cupom fiscal
} estprod;

// Declaração de funções
void submenuprodutos(estprod **produto, int *contador);              // Menu para operações relacionadas a produtos
void submenuvendas(estprod **produto, int *contador);                // Menu para operações relacionadas a vendas
void exibir(estprod **produto, int *contador);                       // Exibir a lista de produtos
void cadastrarproduto(estprod **produto, int *contador);             // Cadastrar um novo produto
void atualizarproduto(estprod **produto, int *contador);             // Atualizar informações de um produto (preço e estoque)
int verificacao(estprod **produto, int *contador, int codeverif);    // Verificar se um código de produto já existe
void excluirproduto(estprod **produto, int *contador);               // Excluir um produto da lista
void salvarprodutos(estprod **produto, int *contador);               // Salvar os produtos em formato binário
void lerprodutos(estprod **produto, int *contador);                  // Ler produtos do formato binário
void realizarvenda(estprod **produto, int *contador);                // Realizar uma venda
void pagamentoavista(estprod **produto, int *contador, float total); // Processar pagamento à vista
void pagamentocartao(estprod **produto, int *contador, float total); // Processar pagamento com cartão
void cupomfiscal(estprod **produto, int *contador, float novototal); // Gerar um cupom fiscal
void relatorio(estprod **produto, int *contador);                    // Gerar um relatório de vendas
void bubblesort(estprod **produto, int *contador);

#endif // FUNCAO_H_INCLUDED