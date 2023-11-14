#include <stdio.h>  // biblioteca para usar o printf()
#include <stdlib.h> // biblioteca para usar o malloc()
#include <string.h> // biblioteca para usar o strcpy()
#include <time.h>   // biblioteca para usar o time()

typedef struct
{
    int codigo;            // codigo do produto
    char nome[25];         // nome do produto
    float preco;           // preco do produto
    int quantestoque;      // quantidade em estoque
    int quantvendida;      // quantidade vendida para usar no relatorio
    int quantvendidacupom; // quantidade vendida para usar no cupom fiscal
} estprod;

estprod *produto = NULL; // estrutura de produtos
int contador = 0;        // contador de produtos

void submenuprodutos();            // submenu de produtos
void submenuvendas();              // submenu de vendas
void exibir();                     // exibir produtos
void cadastrarproduto();           // cadastrar produto
void atualizarproduto();           // atualizar produto - preco e estoque
int verificacao(int codeverif);    // verificacao de codigo, se encontrar retorna o indice, se nao, -1;
void excluirproduto();             // excluir produto
void salvarprodutos();             // salvar produtos em binario
void lerprodutos();                // ler produtos de binario
void realizarvenda();              // realizar venda
void pagamentoavista(float total); // pagamento avista
void pagamentocartao(float total); // pagamento cartao
void cupomfiscal(float novototal); // cupom fiscal
void relatorio();                  // relatorio
void salvarprodutostxt();          // salvar produtos em txt
void lerprodutostxt();             // ler produtos de txt

int main() // funcao principal
{
    int opc, continuar = 1; // variaveis opc e continuar

    time_t timer; // variavel para armazenar o tempo
    time(&timer); // armazena o tempo

    printf("BEM VINDO AO SISTEMA DE VENDAS - BERENICE V3 - %s", ctime(&timer)); // imprime o tempo
    while (continuar)                                                           // loop para continuar o programa
    {
        printf("Escolha uma das opcoes abaixo:\n");
        printf("1 - Produtos\n");
        printf("2 - Vendas\n");
        printf("3 - Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opc);
        getchar();
        switch (opc)
        {
        case 1:
            submenuprodutos(); // chama o submenu de produtos
            break;
        case 2:
            submenuvendas(); // chama o submenu de vendas
            break;
        case 3:
            printf("Caso nao tenha salvo, gostaria de salvar tudo o que foi feito: \n");
            printf("1 - Nao\n");
            printf("2 - Sim\n");
            printf("Digite a opcao desejada: ");
            scanf("%d", &opc);
            getchar();
            if (opc == 2)
            {
                printf("Gostaria de salvar as alteracoes feitas em: \n");
                printf("1 - Binario\n");
                printf("2 - TXT\n");
                printf("Digite a opcao desejada: ");
                scanf("%d", &opc);
                getchar();
                if (opc == 1)
                {
                    salvarprodutos(); // salva os produtos em binario
                    printf("Produtos salvo com sucesso!\n");
                    printf("Saindo...\n"); // mensagem de saida
                }
                else if (opc == 2)
                {
                    salvarprodutostxt(); // salva os produtos em txt
                    printf("Produtos salvo com sucesso!\n");
                    printf("Saindo...\n"); // mensagem de saida
                }
                else
                {
                    printf("Opcao invalida\n");
                }
                continuar = 0; // para o loop
                break;         // para o switch
            }
            else if (opc == 1)
            {
                printf("Saindo...\n"); // mensagem de saida
                continuar = 0;         // para o loop
                break;                 // para o switch
            }
            else
            {
                printf("Opcao invalida\n");
            }
        }
    }

    free(produto); // libera a memoria alocada

    return 0; // retorna 0 para o programa
}

void submenuprodutos() // submenu de produtos
{
    int opc;  // variavel opc
    while (1) // loop para continuar o programa
    {
        printf("\nEscolha uma das opcoes abaixo:\n");
        printf("1 - Exibir\n");
        printf("2 - Cadastrar\n");
        printf("3 - Atualizar\n");
        printf("4 - Excluir\n");
        printf("5 - Salvar\n");
        printf("6 - Ler\n");
        printf("7 - Voltar\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opc);
        getchar();
        switch (opc)
        {
        case 1:
            exibir(); // chama a funcao exibir
            break;
        case 2:
            cadastrarproduto(); // chama a funcao cadastrar produto
            break;
        case 3:
            atualizarproduto(); // chama a funcao atualizar produto
            break;
        case 4:
            excluirproduto(); // chama a funcao excluir produto
            break;
        case 5:
            printf("Gostaria de salvar as alteracoes feitas em: \n");
            printf("1 - Binario\n");
            printf("2 - TXT\n");
            printf("Digite a opcao desejada: ");
            scanf("%d", &opc);
            getchar();   // limpa o buffer
            switch (opc) // switch para escolher o arquivo
            {
            case 1:
                salvarprodutos(); // chama a funcao salvar produtos em binario
                break;            // para o switch
            case 2:
                salvarprodutostxt();        // chama a funcao salvar produtos em txt
                break;                      // para o switch
                printf("Opcao invalida\n"); // mensagem de erro
                break;                      // para o switch
            }
            break;
        case 6:
            printf("Gostaria de ler o ultimo arquivo salvo em: \n");
            printf("1 - Binario\n");
            printf("2 - TXT\n");
            printf("Digite a opcao desejada: ");
            scanf("%d", &opc);
            getchar();   // limpa o buffer
            switch (opc) // switch para escolher o arquivo
            {
            case 1:
                lerprodutos(); // chama a funcao ler produtos em binario
                break;         // para o switch
            case 2:
                lerprodutostxt(); // chama a funcao ler produtos em txt
                break;            // para o switch
            default:
                printf("Opcao invalida\n"); // mensagem de erro
                break;
            }
        case 7:
            return; // retorna para o menu principal
        default:
            printf("Opcao invalida\n"); // mensagem de erro
        }
    }
}

void submenuvendas() // submenu de vendas
{
    int opc;  // variavel opc (opcao)
    while (1) // loop para continuar o programa
    {
        printf("Escolha uma das opcoes abaixo:\n");
        printf("1 - Realizar Venda\n");
        printf("2 - Relatorio de Vendas\n");
        printf("3 - Voltar\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opc); // le a opcao desejada
        getchar();         // limpa o buffer
        switch (opc)       // switch para escolher a opcao
        {
        case 1:
            realizarvenda(); // chama a funcao realizar venda
            break;           // para o switch
        case 2:
            relatorio(); // chama a funcao relatorio de vendas
            break;       // para o switch
        case 3:
            return; // retorna para o menu principal
        default:
            printf("Opcao invalida\n"); // mensagem de erro
        }
    }
}

void cadastrarproduto()
{
    int indice, codeverif = 0; // variaveis indice e codeverif
    do
    {
        if (codeverif == 0) // codigo for igual a zero, pergunta
        {
            printf("Digite o codigo do produto: ");
        }
        else if (codeverif < 0) // codigo for menor que zero, erro e pergunta
        {
            printf("Codigo negativo, informe um codigo positivo: ");
        }
        scanf("%d", &codeverif);
        getchar();

    } while (codeverif < 0); // loop para continuar o programa (enquanto codigo do produto for menor que 0 ficara no loop)

    indice = verificacao(codeverif); // chama a funcao verificacao e salva o retorno dela

    if (indice != -1) // se o retorno for diferente de -1
    {
        printf("Código já existente.\n");
        return; // retorna para o menu principal
    }

    if (contador == 0) // se o contador for igual a 0
    {
        produto = (estprod *)malloc((contador + 1) * sizeof(estprod)); // Faz a alocacao de memoria caso seja o primeiro produto
    }
    else
    {
        produto = (estprod *)realloc(produto, (contador + 1) * sizeof(estprod)); // Faz a realocacao de memoria para um bloco maior a cada produto cadastrado
    }

    printf("Codigo %i disponivel\n", codeverif); // imprime a mensagem dizendo que o codigo esta disponivel
    produto[contador].codigo = codeverif;        // recebe a posicao que ira ficar
    printf("Digite o nome do produto: ");
    gets(produto[contador].nome); // recebe o nome do produto
    fflush(stdin);                // Faz a limpeza do buffer
    do
    {
        if (produto[contador].preco < 0) // se o preco for menor que zero
        {
            printf("Preco incorreto, insira um valor positivo: ");
        }
        else
        {
            printf("Digite o preco do produto: ");
        }
        scanf("%f", &produto[contador].preco); // recebe o preco do produto
    } while (produto[contador].preco < 0);     // loop para continuar o programa (enquanto o preco do produto for menor que 0 ficara no loop))
    do
    {
        if (produto[contador].quantestoque < 0) // se o estoque for menor que zero
        {
            printf("Quantidade incorreto, insira um valor positivo: ");
        }
        else // se o estoque for maior que zero
        {
            printf("Digite a quantidade em estoque do produto: ");
        }
        scanf("%d", &produto[contador].quantestoque); // recebe a quantidade em estoque do produto
        getchar();
    } while (produto[contador].quantestoque < 0);            // limpa o buffer
    printf("\nCodigo: %d\n", produto[contador].codigo);      // imprime o codigo do produto
    printf("Nome: %s\n", produto[contador].nome);            // imprime o nome do produto
    printf("Preco: %.2f\n", produto[contador].preco);        // imprime o preco do produto
    printf("Estoque: %d\n", produto[contador].quantestoque); // imprime o estoque do produto
    contador++;                                              // incrementa o contador
}

void exibir() // funcao para exibir os produtos
{
    printf("\nPRODUTOS:");
    printf("\n--------------------------------------------------\n");
    for (int i = 0; i < contador; i++) // loop para percorrer o vetor de produtos
    {
        printf(" Cod %d | %s | R$ %.2f | Quant %i\n", produto[i].codigo, produto[i].nome, produto[i].preco, produto[i].quantestoque);
        // Faz a impressao de todos os produtos cadastrados
        printf("--------------------------------------------------\n");
    }
}

int verificacao(int codeverif) // funcao para verificar se o codigo ja existe
{
    for (int i = 0; i < contador; i++) // loop para percorrer o vetor de produtos
    {
        if (codeverif == produto[i].codigo) // se o codigo for igual ao codigo do produto
        {
            return i; // Retorna o indice do produto encontrado
        }
    }
    return -1; // Retorna -1 se o produto não for encontrado
}

void atualizarproduto() // funcao para atualizar os produtos
{
    int indice, codeverif, opc; // variaveis indice, codeverif e opc
    printf("Digite o codigo do produto: ");
    scanf("%d", &codeverif);             // le o codigo do produto
    getchar();                           // limpa o buffer
    indice = verificacao(codeverif);     // chama a funcao verificacao e salva o retorno dela
    if (indice == -1)                    // se o retorno for -1
    {
        printf("Produto nao encontrado.\n");
    }
    else // se o retorno for diferente de -1
    {
        printf("Produto: %s \n", produto[indice].nome);
        printf("Qual informacao gostaria de atualizar:\n");
        printf("1 - Preco\n");
        printf("2 - Estoque\n");
        printf("3 - Voltar\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opc); // le a opcao desejada
        getchar();
        switch (opc) // switch para escolher a opcao
        {
        case 1:
            printf(" Cod %d | %s | R$ %.2f | Quant %i\n", produto[indice].codigo, produto[indice].nome, produto[indice].preco, produto[indice].quantestoque);
            printf("Digite o novo preco: ");
            scanf("%f", &produto[indice].preco); // le o novo valor
            getchar();
            printf(" Cod %d | %s | R$ %.2f | Quant %i\n", produto[indice].codigo, produto[indice].nome, produto[indice].preco, produto[indice].quantestoque);
            break;
        case 2:
            printf(" Cod %d | %s | R$ %.2f | Quant %i\n", produto[indice].codigo, produto[indice].nome, produto[indice].preco, produto[indice].quantestoque);
            printf("Digite a nova quantidade em estoque: ");
            scanf("%d", &produto[indice].quantestoque); // le a nova quantidade em estoque
            getchar();
            printf(" Cod %d | %s | R$ %.2f | Quant %i\n", produto[indice].codigo, produto[indice].nome, produto[indice].preco, produto[indice].quantestoque);
            break;
        case 3:
            return; // retorna para o menu principal
            break;  // para o switch
        default:
            printf("Opcao invalida\n");
            break; // para o switch
        }
    }
}

void excluirproduto() // funcao para excluir os produtos
{
    int indice, codeverif, opc; // variaveis indice, codeverif e opc
    printf("Digite o codigo do produto: ");
    scanf("%d", &codeverif); // le o codigo do produto
    getchar();
    indice = verificacao(codeverif);     // chama a funcao verificacao e salva o retorno dela
    printf("Verificacao: %d\n", indice); // imprime o retorno da funcao
    if (indice == -1)                    // se o retorno for -1
    {
        printf("Produto nao encontrado.\n");
    }
    else
    {
        if (indice >= 0) // se o indice for maior ou igual a 0
        {
            printf("Cod %d | %s | R$ %.2f | Quant %i\n", produto[indice].codigo, produto[indice].nome, produto[indice].preco, produto[indice].quantestoque);
            printf("Deseja excluir este produto?\n");
            printf("1 - Sim\n");
            printf("2 - Nao\n");
            printf("Digite a opcao desejada: ");
            scanf("%d", &opc);
            getchar();    // limpa o buffer
            if (opc == 1) // se a opcao for 1
            {
                for (int i = indice; i < contador - 1; i++) // loop para percorrer o vetor de produtos
                {
                    produto[i] = produto[i + 1]; // copia o valor do produto seguinte para o produto atual
                }
                contador--;                                                          // decrementa o contador
                produto = (estprod *)realloc(produto, (contador) * sizeof(estprod)); // realoca o vetor de produtos
                printf("Produto excluido com sucesso.\n");
            }
            else if (opc == 2) // se a opcao for 2
            {
                return; // retorna para o menu principal
                printf("Produto nao excluido.\n");
            }
            else
            {
                printf("Opcao invalida\n");
            }
        }
    }
}

void salvarprodutos() // funcao para salvar os produtos
{
    FILE *fp;
    fp = fopen("produtos.bin", "wb"); // Abre o arquivo em modo de escrita binária

    if (fp == NULL) // se o arquivo nao for encontrado
    {
        printf("Erro ao abrir arquivo.\n");
    }
    else // se o arquivo for encontrado
    {
        fwrite(produto, sizeof(estprod), contador, fp);      // Escreve os dados da estrutura no arquivo binário
        printf("Arquivo produtos.bin salvo com sucesso.\n"); // imprime a mensagem de sucesso
        fclose(fp);                                          // fecha o arquivo
    }
}

void lerprodutos() // funcao para ler os produtos
{
    FILE *fp;                         // ponteiro para o arquivo
    fp = fopen("produtos.bin", "rb"); // Abre o arquivo em modo de leitura binária

    if (fp == NULL) // se o arquivo nao for encontrado
    {
        printf("Erro ao abrir arquivo.\n"); // imprime a mensagem de erro
        return;                             // retorna para o menu principal
    }
    else // se o arquivo for encontrado
    {
        printf("\nArquivo produtos.bin lido com sucesso.\n");
    }

    contador = 0; // zera o contador

    if (produto != NULL) // se o vetor de produtos nao for nulo
    {
        free(produto); // libera a memória do vetor de produtos
    }

    estprod temporaria; // Variável temporária para armazenar os dados lidos

    while (fread(&temporaria, sizeof(estprod), 1, fp) == 1) // Lê uma estrutura por vez
    {
        if (contador == 0) // se o contador for igual a 0
        {
            produto = (estprod *)malloc(sizeof(estprod)); // aloca memória para o vetor de produtos
        }
        else // se o contador for diferente de 0
        {
            produto = (estprod *)realloc(produto, (contador + 1) * sizeof(estprod)); // realoca o vetor de produtos
        }

        produto[contador] = temporaria; // copia os dados lidos para o vetor de produtos
        contador++;                     // incrementa o contador
    }
    fclose(fp); // fecha o arquivo
}

void realizarvenda() // funcao para realizar a venda
{
    int codeverif, indice, quantidade, formadepagamento; // variaveis inteiras
    float subtotal, total = 0;                           // variaveis float

    while (1) // loop infinito
    {
        printf("\n\nRealizar Venda [ 0 - FORMA DE PAGAMENTO]\n");
        exibir(); // Exibe os produtos disponíveis

        printf("Digite o código do produto (ou 0 para finalizar a venda): ");
        scanf("%d", &codeverif); // le o código do produto
        getchar();

        if (codeverif == 0) // se o código for igual a 0
        {
            if (total > 0) // se o total for maior que 0
            {
                break; // Sai do loop se o cliente pressionar '0' e houver produtos no carrinho
            }
            else // se o total for menor que 0
            {
                printf("\nCarrinho vazio. Adicione um produto\n");
                continue; // Continua o loop sem calcular o total
            }
        }
        else // se o código for diferente de 0
        {
            indice = verificacao(codeverif); // chama a funcao verificacao e salva o retorno dela

            if (indice == -1) // se o retorno for -1
            {
                printf("Produto não encontrado\n");
            }
            else // se o retorno for diferente de -1
            {
                printf("Digite a quantidade desejada: ");
                scanf("%d", &quantidade); // le a quantidade desejada
                getchar();

                if (quantidade <= produto[indice].quantestoque && quantidade > 0) // se a quantidade desejada for menor ou igual a quantidade em estoque e maior que 0
                {
                    subtotal = quantidade * produto[indice].preco;   // calcula o sub
                    total += subtotal;                               // soma o sub ao total
                    produto[indice].quantestoque -= quantidade;      // diminui a quantidade em estoque
                    produto[indice].quantvendida += quantidade;      // soma a quantidade vendida o relatorio
                    produto[indice].quantvendidacupom += quantidade; // soma a quantidade vendida para o cupom
                }
                else
                {
                    printf("Quantidade inserida é superior à quantidade disponível de %i unidades\n", produto[indice].quantestoque); // imprime a mensagem de erro
                }
            }
        }
    }

    if (total > 0) // se o total for maior que 0
    {
        do
        {
            printf("\n\nTotal da sua compra R$ %.2f \n\n", total); // imprime o total da compra
            printf("Escolha a forma de pagamento:\n");
            printf("1 - Dinheiro\n");
            printf("2 - Cartão\n");
            printf("Digite a opção desejada: ");
            scanf("%d", &formadepagamento); // le a forma de pagamento
            getchar();

            if (formadepagamento == 1) // se a forma de pagamento for 1
            {
                pagamentoavista(total); // chama a funcao de pagamento avista
            }
            else if (formadepagamento == 2) // se a forma de pagamento for 2
            {
                pagamentocartao(total); // chama a funcao de pagamento cartao
            }
        } while (formadepagamento != 1 && formadepagamento != 2); // loop infinito se for diferente de 1 e 2
    }
    else // se o total for menor que 0
    {
        printf("Nenhum produto adicionado ao carrinho. Venda cancelada.\n");
    }
}

void pagamentoavista(float total) // funcao para pagamento avista
{
    float valorrecebido, novototal, desconto, troco; // variaveis float

    printf("Insira o valor recebido: ");
    scanf("%f", &valorrecebido); // le o valor recebido
    getchar();                   // limpa o buffer

    while (valorrecebido < total || valorrecebido < 0) // loop infinito se o valor recebido for menor que o total ou menor que 0
    {
        printf("Valor invalido\n");
        printf("Insira o valor recebido: ");
        scanf("%f", &valorrecebido); // le o valor recebido
        getchar();                   // limpa o buffer
    }
    if (total > 1 && total <= 50) // se o total for maior que 1 e menor ou igual a 50
    {
        novototal = total - (total * 0.05);                                                      // calcula o novo total
        desconto = total * 0.05;                                                                 // calcula o desconto
        troco = valorrecebido - (total - desconto);                                              // calcula o troco
        printf("\nSeu troco com desconto e: %.2f\nSeu desconto foi de %.2f\n", troco, desconto); // imprime o troco e o desconto
        cupomfiscal(novototal);                                                                  // chama a funcao cupomfiscal
    }
    else if (total > 50 && total < 100) // se o total for maior que 50 e menor que 100
    {
        novototal = total - (total * 0.1);                                                       // calcula o novo total
        desconto = total * 0.10;                                                                 // calcula o desconto
        troco = valorrecebido - (total - desconto);                                              // calcula o troco
        printf("\nSeu troco com desconto e: %.2f\nSeu desconto foi de %.2f\n", troco, desconto); // imprime o troco e o desconto
        cupomfiscal(novototal);                                                                  // chama a funcao cupomfiscal
    }
    else if (total >= 100) // se o total for maior ou igual a 100
    {
        novototal = total - (total * 0.18);                                                      // calcula o novo total
        desconto = total * 0.18;                                                                 // calcula o desconto
        troco = valorrecebido - (total - desconto);                                              // calcula o troco
        printf("\nSeu troco com desconto e: %.2f\nSeu desconto foi de %.2f\n", troco, desconto); // imprime o troco e o desconto
        cupomfiscal(novototal);                                                                  // chama a funcao cupomfiscal
    }
    else // se o total for menor que 1
    {
        printf("\nEntrada inválida de valor recebido\n");
    }
}

void pagamentocartao(float total) // funcao para pagamento cartao
{

    int nparcelas;                        // variavel inteira
    float novototal, valor_parcela = 0.0; // variaveis float

    printf("Insira o numero das parcelas: ");
    scanf("%d", &nparcelas); // le o numero de parcelas
    getchar();               // limpa o buffer
    while (nparcelas <= 0)   // loop infinito se o numero de parcelas for menor que 0
    {
        printf("\nNumero de parcelas incorreta, tente novamente\n");

        printf("\nInsira o numero das parcelas: ");
        scanf("%d", &nparcelas); // le o numero de parcelas
        getchar();
    }

    if (nparcelas >= 1 && nparcelas <= 3) // se o numero de parcelas for maior ou igual a 1 e menor ou igual a 3
    {
        novototal = total + (total * 0.05);                                                                         // calcula o novo total
        valor_parcela = novototal / nparcelas;                                                                      // calcula o valor da parcela
        printf("\nO total com acrescimo 5%% e %.2f\nO valor de cada parcela e %.2f\n\n", novototal, valor_parcela); // imprime o novo total e o valor da parcela
        cupomfiscal(novototal);                                                                                     // chama a funcao cupomfiscal
    }
    else if (nparcelas > 3) // se o numero de parcelas for maior que 3
    {
        novototal = total + (total * 0.08);                                                                            // calcula o novo total
        valor_parcela = novototal / nparcelas;                                                                         // calcula o valor da parcela
        printf("\nO total com acrescimo de 8%% e %.2f\nO valor de cada parcela e %.2f\n\n", novototal, valor_parcela); // imprime o novo total e o valor da parcela
        cupomfiscal(novototal);                                                                                        // chama a funcao cupomfiscal
    }
}

void cupomfiscal(float novototal) // funcao para criar o cupom fiscal
{
    time_t rawtime;    // variavel time_t
    struct tm *info;   // struct tm
    char filename[50]; // variavel char
    char dataHora[20]; // variavel char

    time(&rawtime);             // pega a hora atual
    info = localtime(&rawtime); // armazena  a hora atual

    strftime(dataHora, sizeof(dataHora), "%Y-%m-%d_%H-%M-%S", info); // formata a data e hora

    sprintf(filename, "%s.txt", dataHora); // formata o nome do arquivo

    FILE *cupom;                  // variavel FILE apontando para cupom
    cupom = fopen(filename, "w"); // Abre o arquivo em modo de escrita de texto

    if (cupom == NULL) // se o arquivo for nulo
    {
        printf("Erro ao criar o arquivo do cupom fiscal.\n");
    }
    else // se o arquivo não for nulo
    {
        float itemtotal = 0, totalcupom = 0; // variaveis float

        fprintf(cupom, "--------------------------------------------------\n");
        fprintf(cupom, "                   CUPOM FISCAL:                      \n");
        fprintf(cupom, "--------------------------------------------------\n\n");

        for (int i = 0; i < contador; i++) // loop para percorrer o vetor de produtos
        {
            if (produto[i].quantvendidacupom > 0) // se a quantidade vendida for maior que 0
            {
                itemtotal = produto[i].quantvendidacupom * produto[i].preco; // calcula o item total
                fprintf(cupom, "%i - %s - %.2f - Quant %i - R$ %.2f\n", produto[i].codigo, produto[i].nome, produto[i].preco, produto[i].quantvendidacupom, itemtotal);
                totalcupom += itemtotal;          // soma o item total ao total do cupom
                produto[i].quantvendidacupom = 0; // zera a quantidade vendida
            }
        }

        fprintf(cupom, "\n--------------------------------------------------\n"); // salva no arquivo texto
        if (totalcupom - novototal > 0)                                           // se o valor for maior que zero e desconto
        {
            fprintf(cupom, "             Desconto: R$ %.2f                  \n", totalcupom - novototal); // desconto
        }
        else // se o valor for menor que zero e acrescimo
        {
            fprintf(cupom, "             Acrescimo: R$ %.2f                  \n", -(totalcupom - novototal)); // acrescimo
        }
        fprintf(cupom, "             Total do cupom: R$ %.2f                  \n", novototal); // salva no arquivo texto
        fprintf(cupom, "--------------------------------------------------\n");                // salva no arquivo texto

        fclose(cupom); // fecha o arquivo

        printf("Cupom fiscal salvo com sucesso no arquivo: %s\n", filename); // imprime o nome do arquivo

        FILE *cupomLeitura;                  // variavel FILE apontando para cupomleitura
        cupomLeitura = fopen(filename, "r"); // Abre o arquivo em modo de leitura de texto

        if (cupomLeitura == NULL) // se o arquivo for nulo
        {
            printf("Erro ao abrir o arquivo do cupom fiscal para leitura.\n");
        }
        else // se o arquivo não for nulo
        {
            char line[256];                                 // variavel char
            while (fgets(line, sizeof(line), cupomLeitura)) // armazena as linhas do arquivo
            {
                printf("%s", line); // imprime as linhas
            }
            fclose(cupomLeitura); // fecha o arquivo
        }
    }
}

void relatorio() // funcao para gerar o relatorio
{
    float totalvendido;
    time_t timer; // variavel para armazenar o tempo
    time(&timer); // armazena o tempo

    printf("\n--------------------------------------------------\n");
    printf("            RELATORIO DE ITENS VENDIDOS:              \n");
    printf("             %s", ctime(&timer)); // imprime o tempo
    printf("\n--------------------------------------------------\n\n");

    for (int i = 0; i < contador; i++) // loop para percorrer o vetor de produtos
    {
        if (produto[i].quantvendida > 0) // se a quantidade vendida for maior que 0
        {
            totalvendido += produto[i].quantvendida * produto[i].preco;                                                           // soma o valor total vendido
            printf("%i - %s - %.2f - Quant %i\n", produto[i].codigo, produto[i].nome, produto[i].preco, produto[i].quantvendida); // imprime o produto vendido
        }
    }
    printf("\n--------------------------------------------------\n");
    printf("               Total: R$ %.2f                  ", totalvendido); // imprime o total vendido
    printf("\n--------------------------------------------------\n");
}

void salvarprodutostxt() // funcao para salvar os produtos no arquivo txt
{
    FILE *fp;                        // variavel FILE apontando para fp
    fp = fopen("produtos.txt", "w"); // Abre o arquivo em modo de escrita de texto
    if (fp == NULL)                  // se o arquivo for nulo
    {
        printf("Erro ao abrir arquivo.\n");
    }
    else // se o arquivo não for nulo
    {
        for (int i = 0; i < contador; i++) // loop para percorrer o vetor de produtos
        {
            fprintf(fp, "%d\n%s\n%.2f\n%d\n%d\n%d\n\n", produto[i].codigo, produto[i].nome, produto[i].preco, produto[i].quantestoque, produto[i].quantvendida, produto[i].quantvendidacupom);
            // salva os dados no arquivo txt
        }
        printf("Arquivo salvo com sucesso.\n");
        fclose(fp); // fecha o arquivo
    }
}

void lerprodutostxt() // funcao para ler os produtos do arquivo txt
{
    FILE *fp;                        // variavel FILE apontando para fp
    fp = fopen("produtos.txt", "r"); // Abre o arquivo em modo de leitura de texto

    if (fp == NULL) // se o arquivo for nulo
    {
        printf("Erro ao abrir arquivo.\n");
        return;
    }
    else // se o arquivo não for nulo
    {
        printf("Arquivo aberto com sucesso.\n");
    }

    contador = 0; // zera o contador

    if (produto != NULL) // se o vetor de produtos for diferente de nulo
    {
        free(produto); // libera a memoria
    }

    estprod temporaria; // Variável temporária para armazenar os dados lidos

    while (fscanf(fp, "%d\n%s\n%f\n%d\n%d\n%d\n\n", &temporaria.codigo, temporaria.nome, &temporaria.preco, &temporaria.quantestoque, &temporaria.quantvendida, &temporaria.quantvendidacupom) == 6) // faz enquanto estiver lendo 5 valores
    {
        if (contador == 0) // se o contador for igual a zero
        {
            produto = (estprod *)malloc(sizeof(estprod)); // aloca memoria para o vetor de produtos
        }
        else
        {
            produto = (estprod *)realloc(produto, (contador + 1) * sizeof(estprod)); // Realoca a memoria para o vetor de produtos maior
        }

        produto[contador] = temporaria; // armazena os dados lidos no vetor de produtos
        contador++;                     // incrementa o contador
    }

    fclose(fp); // fecha o arquivo
}