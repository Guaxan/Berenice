#include "cabecalho.h"

// Função principal
int main()
{
    int opc, continuar = 1; // Variáveis opc e continuar para controle do menu principal
    estprod *produto = NULL; // Ponteiro para a estrutura de produtos esta apontado para nulo
    int contador = 0;        // Contador de produtos

    time_t timer; // Variável para armazenar o tempo
    time(&timer); // Obter a hora atual

    printf("BEM VINDO AO SISTEMA DE VENDAS - BERENICE V3 - %s", ctime(&timer)); // Imprimir a hora atual
    while (continuar)                                                           // Loop para manter o programa em execução
    {
        printf("Escolha uma das opções abaixo:\n");
        printf("1 - Produtos\n");
        printf("2 - Vendas\n");
        printf("3 - Sair\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opc);
        getchar(); // Limpar o buffer de entrada

        switch (opc) // Switch para escolher a opção desejada
        {
        case 1:
            submenuprodutos(&produto, &contador); // Chamar o submenu de produtos
            break;
        case 2:
            submenuvendas(&produto, &contador); // Chamar o submenu de vendas
            break;
        case 3:
            printf("Caso não tenha salvo, gostaria de salvar tudo o que foi feito: \n");
            printf("1 - Não\n");
            printf("2 - Sim\n");
            printf("Digite a opção desejada: ");
            scanf("%d", &opc);
            getchar();
            if (opc == 2)
            {
                salvarprodutos(&produto, &contador); // Salvar os produtos em formato binário
                printf("Produtos salvos com sucesso!\n");
                printf("Saindo...\n"); // Mensagem de saída
                continuar = 0; // Parar o loop
                break;         // Sair do switch
            }
            else if (opc == 1)
            {
                printf("Saindo...\n"); // Mensagem de saída
                continuar = 0;         // Parar o loop
                break;                 // Sair do switch
            }
            else
            {
                printf("Opção inválida\n");
            }
        }
    }

    free(produto); // Liberar a memória alocada

    return 0; // Retornar 0 para o encerramento do programa
}

