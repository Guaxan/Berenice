#include "cabecalho.h"

void submenuprodutos(estprod **produto, int *contador)
{
    int opc;
    while (1)
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
            exibir(produto, contador);
            break;
        case 2:
            cadastrarproduto(produto, contador);
            break;
        case 3:
            atualizarproduto(produto, contador);
            break;
        case 4:
            excluirproduto(produto, contador);
            break;
        case 5:
            salvarprodutos(produto, contador);
            break;
        case 6:
            lerprodutos(produto, contador);
            break;
        case 7:
            return;
        default:
            printf("Opcao invalida\n");
        }
    }
}

void submenuvendas(estprod **produto, int *contador)
{
    int opc;
    while (1)
    {
        printf("Escolha uma das opcoes abaixo:\n");
        printf("1 - Realizar Venda\n");
        printf("2 - Relatorio de Vendas\n");
        printf("3 - Voltar\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opc);
        getchar();
        switch (opc)
        {
        case 1:
            realizarvenda(produto, contador);
            break;
        case 2:
            relatorio(produto, contador);
            break;

        case 3:
            return;
        default:
            printf("Opcao invalida\n");
        }
    }
}

void cadastrarproduto(estprod **produto, int *contador)
{
    int indice, codeverif = 0;

    do
    {
        if (codeverif == 0)
        {
            printf("Digite o codigo do produto: ");
        }
        else if (codeverif < 0)
        {
            printf("Codigo negativo, informe um codigo positivo: ");
        }
        scanf("%d", &codeverif);
        getchar();

    } while (codeverif < 0);

    indice = verificacao(produto, contador, codeverif);

    if (indice != -1)
    {
        printf("Código já existente.\n");
        return;
    }

    if (*contador == 0)
    {
        *produto = (estprod *)malloc((*contador + 1) * sizeof(estprod));
    }
    else
    {
        *produto = (estprod *)realloc(*produto, (*contador + 1) * sizeof(estprod));
    }

    printf("Codigo %i disponivel", codeverif);
    (*produto)[*contador].codigo = codeverif;

    printf("\nDigite o nome do produto: ");
    fgets((*produto)[*contador].nome, 25, stdin);
    (*produto)[*contador].nome[strcspn((*produto)[*contador].nome, "\n")] = '\0';

    do
    {
        if ((*produto)[*contador].preco < 0)
        {
            printf("Preco incorreto, insira um valor positivo: ");
        }
        else
        {
            printf("Digite o preco do produto: ");
        }
        scanf("%f", &(*produto)[*contador].preco);
        getchar();
    } while ((*produto)[*contador].preco < 0);

    do
    {
        if ((*produto)[*contador].quantestoque < 0)
        {
            printf("Quantidade incorreta, insira um valor positivo: ");
        }
        else
        {
            printf("Digite a quantidade em estoque do produto: ");
        }
        scanf("%d", &(*produto)[*contador].quantestoque);
        getchar();
    } while ((*produto)[*contador].quantestoque < 0);

    (*produto)[*contador].quantvendida = 0;
    (*produto)[*contador].quantvendidacupom = 0;

    printf("\nCodigo: %d\n", (*produto)[*contador].codigo);
    printf("Nome: %s\n", (*produto)[*contador].nome);
    printf("Preco: %.2f\n", (*produto)[*contador].preco);
    printf("Estoque: %d\n", (*produto)[*contador].quantestoque);
    (*contador)++;
    bubblesort(produto, contador);
}


void exibir(estprod **produto, int *contador)
{
    printf("\nPRODUTOS:");
    printf("\n--------------------------------------------------\n");

    for (int i = 0; i < *contador; i++)
    {
        printf(" Cod %d | %s | R$ %.2f | Quant %i\n", (*produto)[i].codigo, (*produto)[i].nome, (*produto)[i].preco, (*produto)[i].quantestoque);
        printf("--------------------------------------------------\n");
    }
}

int verificacao(estprod **produto, int *contador, int codeverif)
{
    for (int i = 0; i < *contador; i++)
    {
        if (codeverif == (*produto)[i].codigo)
        {
            return i;
        }
    }
    return -1;
}

void atualizarproduto(estprod **produto, int *contador)
{
    int indice, codeverif, opc;

    printf("Digite o código do produto: ");
    scanf("%d", &codeverif);
    getchar();

    indice = verificacao(produto, contador, codeverif);

    if (indice == -1)
    {
        printf("Produto não encontrado.\n");
    }
    else
    {
        printf("Produto: %s \n", (*produto)[indice].nome);
        printf("Qual informação você gostaria de atualizar:\n");
        printf("1 - Preço\n");
        printf("2 - Estoque\n");
        printf("3 - Voltar\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opc);
        getchar();

        switch (opc)
        {
        case 1:
            printf(" Cod %d | %s | R$ %.2f | Quant %i\n", (*produto)[indice].codigo, (*produto)[indice].nome, (*produto)[indice].preco, (*produto)[indice].quantestoque);
            printf("Digite o novo preço: ");
            scanf("%f", &(*produto)[indice].preco);
            getchar();
            printf(" Cod %d | %s | R$ %.2f | Quant %i\n", (*produto)[indice].codigo, (*produto)[indice].nome, (*produto)[indice].preco, (*produto)[indice].quantestoque);
            break;

        case 2:
            printf(" Cod %d | %s | R$ %.2f | Quant %i\n", (*produto)[indice].codigo, (*produto)[indice].nome, (*produto)[indice].preco, (*produto)[indice].quantestoque);
            printf("Digite a nova quantidade em estoque: ");
            scanf("%d", &(*produto)[indice].quantestoque);
            getchar();
            printf(" Cod %d | %s | R$ %.2f | Quant %i\n", (*produto)[indice].codigo, (*produto)[indice].nome, (*produto)[indice].preco, (*produto)[indice].quantestoque);
            break;

        case 3:
            return;
            break;

        default:
            printf("Opção inválida\n");
            break;
        }
    }
}

void excluirproduto(estprod **produto, int *contador)
{
    int indice, codeverif, opc;

    printf("Digite o código do produto: ");
    scanf("%d", &codeverif);
    getchar();

    indice = verificacao(produto, contador, codeverif);

    if (indice == -1)
    {
        printf("Produto não encontrado.\n");
    }
    else
    {
        if (indice >= 0)
        {
            printf("Cod %d | %s | R$ %.2f | Quant %i\n", (*produto)[indice].codigo, (*produto)[indice].nome, (*produto)[indice].preco, (*produto)[indice].quantestoque);
            printf("Deseja excluir este produto?\n");
            printf("1 - Sim\n");
            printf("2 - Não\n");
            printf("Digite a opção desejada: ");
            scanf("%d", &opc);
            getchar();

            if (opc == 1)
            {
                for (int i = indice; i < *contador - 1; i++)
                {
                    (*produto)[i] = (*produto)[i + 1];
                }

                (*contador)--;
                *produto = (estprod *)realloc(*produto, (*contador) * sizeof(estprod));

                printf("Produto excluído com sucesso.\n");
            }
            else if (opc == 2)
            {
                printf("Produto não excluído.\n");
                return;
            }
            else
            {
                printf("Opção inválida\n");
            }
        }
    }
}

void salvarprodutos(estprod **produto, int *contador)
{
    FILE *fp;
    fp = fopen("produtos.bin", "wb");

    if (fp == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
    }
    else
    {
        fwrite(*produto, sizeof(estprod), *contador, fp);
        printf("\nArquivo produtos.bin salvo com sucesso.\n");
        fclose(fp);
    }
}

void lerprodutos(estprod **produto, int *contador)
{
    FILE *fp;
    fp = fopen("produtos.bin", "rb");

    if (fp == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        return;
    }
    else
    {
        printf("\nArquivo produtos.bin lido com sucesso.\n");
    }

    *contador = 0; // Zera o contador

    if (*produto != NULL)
    {
        free(*produto);
    }

    estprod temporaria;

    while (fread(&temporaria, sizeof(estprod), 1, fp) == 1)
    {
        if (*contador == 0)
        {
            *produto = (estprod *)malloc(sizeof(estprod));
        }
        else
        {
            *produto = (estprod *)realloc(*produto, (*contador + 1) * sizeof(estprod));
        }

        (*produto)[*contador] = temporaria;
        (*contador)++;
    }
    fclose(fp);
}

void realizarvenda(estprod **produto, int *contador) // funcao para realizar a venda
{
    int codeverif, indice, quantidade, formadepagamento; // variaveis inteiras
    float subtotal, total = 0;                           // variaveis float

    while (1) // loop infinito
    {
        printf("\n\nRealizar Venda [ 0 - FORMA DE PAGAMENTO]\n");
        exibir(produto, contador); // Exibe os produtos disponíveis

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
            indice = verificacao(produto, contador, codeverif);

            if (indice == -1) // se o retorno for -1
            {
                printf("Produto não encontrado\n");
            }
            else // se o retorno for diferente de -1
            {
                printf("Digite a quantidade desejada: ");
                scanf("%d", &quantidade); // le a quantidade desejada
                getchar();

                if (quantidade <= produto[indice]->quantestoque && quantidade > 0) // se a quantidade desejada for menor ou igual a quantidade em estoque e maior que 0
                {
                    produto[indice]->quantvendida = 0;
                    subtotal = quantidade * produto[indice]->preco;   // calcula o sub
                    total += subtotal;                                // soma o sub ao total
                    produto[indice]->quantestoque -= quantidade;      // diminui a quantidade em estoque
                    produto[indice]->quantvendida += quantidade;      // soma a quantidade vendida o relatorio
                    produto[indice]->quantvendidacupom += quantidade; // soma a quantidade vendida para o cupom
                }
                else
                {
                    printf("Quantidade inserida é superior à quantidade disponível de %i unidades\n", produto[indice]->quantestoque); // imprime a mensagem de erro
                }
            }
        }
    }

    if (total > 0)
    {
        do
        {
            printf("Escolha a forma de pagamento:\n");
            printf("1 - Dinheiro\n");
            printf("2 - Cartão\n");
            printf("Digite a opção desejada: ");
            scanf("%d", &formadepagamento);
            getchar();

            if (formadepagamento == 1)
            {
                pagamentoavista(produto, contador, total);
            }
            else if (formadepagamento == 2)
            {
                pagamentocartao(produto, contador, total);
            }
        } while (formadepagamento != 1 && formadepagamento != 2);
    }
    else
    {
        printf("Nenhum produto adicionado ao carrinho. Venda cancelada.\n");
    }
}

void pagamentoavista(estprod **produto, int *contador, float total)
{
    float valorrecebido, novototal, desconto, troco; // variaveis float

    if (total > 1 && total <= 50) // se o total for maior que 1 e menor ou igual a 50
    {
        novototal = total - (total * 0.05);                                                      // calcula o novo total
        desconto = total * 0.05;                                                                 // calcula o desconto
    }
    else if (total > 50 && total < 100) // se o total for maior que 50 e menor que 100
    {
        novototal = total - (total * 0.1);                                                       // calcula o novo total
        desconto = total * 0.10;                                                                 // calcula o desconto
    }
    else if (total >= 100) // se o total for maior ou igual a 100
    {
        novototal = total - (total * 0.18);                                                      // calcula o novo total
        desconto = total * 0.18;                                                                 // calcula o desconto
    }
    else // se o total for menor que 1
    {
        printf("\nEntrada inválida de valor recebido\n");
    }
    printf("O total da sua compra com desconto de %.2f ficou R$ %.2f\n", desconto, novototal);
    printf("Insira o valor recebido: ");
    scanf("%f", &valorrecebido); // le o valor recebido
    getchar();                   // limpa o buffer
    troco = valorrecebido - (total - desconto);                                              // calcula o troco
    printf("\nSeu troco com desconto e: %.2f\nSeu desconto foi de %.2f\n", troco, desconto); // imprime o troco e o desconto
    cupomfiscal(produto, contador, novototal);                                               // chama a funcao cupomfiscal

    while (valorrecebido < total || valorrecebido < 0) // loop infinito se o valor recebido for menor que o total ou menor que 0
    {
        printf("Valor invalido\n");
        printf("Insira o valor recebido: ");
        scanf("%f", &valorrecebido); // le o valor recebido
        getchar();                   // limpa o buffer
    }
    
}

void pagamentocartao(estprod **produto, int *contador, float total)
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
        cupomfiscal(produto, contador, novototal);                                                                  // chama a funcao cupomfiscal
    }
    else if (nparcelas > 3) // se o numero de parcelas for maior que 3
    {
        novototal = total + (total * 0.08);                                                                            // calcula o novo total
        valor_parcela = novototal / nparcelas;                                                                         // calcula o valor da parcela
        printf("\nO total com acrescimo de 8%% e %.2f\nO valor de cada parcela e %.2f\n\n", novototal, valor_parcela); // imprime o novo total e o valor da parcela
        cupomfiscal(produto, contador, novototal);                                                                     // chama a funcao cupomfiscal
    }
}

void cupomfiscal(estprod **produto, int *contador, float novototal)
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

        for (int i = 0; i < *contador; i++) // loop para percorrer o vetor de produtos
        {
            if (produto[i]->quantvendidacupom > 0) // se a quantidade vendida for maior que 0
            {
                itemtotal = produto[i]->quantvendidacupom * produto[i]->preco; // calcula o item total
                fprintf(cupom, "%i - %s - %.2f - Quant %i - R$ %.2f\n", produto[i]->codigo, produto[i]->nome, produto[i]->preco, produto[i]->quantvendidacupom, itemtotal);
                totalcupom += itemtotal;           // soma o item total ao total do cupom
                produto[i]->quantvendidacupom = 0; // zera a quantidade vendida
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

void relatorio(estprod **produto, int *contador)
{
    float totalvendido = 0.0;
    estprod *itensrelatorio = NULL;
    
    for(int i = 0; i < *contador; i++){
        itensrelatorio[*contador] = *produto[*contador];
        printf("%i - %s - %.2f - Quant %i\n", itensrelatorio[i].codigo, itensrelatorio[i].nome, itensrelatorio[i].preco, itensrelatorio[i].quantvendida); // imprime o produto vendido
    }
    
        
    /*time_t timer; // variável para armazenar o tempo
    time(&timer); // armazena o tempo
    

    printf("\n--------------------------------------------------\n");
    printf("            RELATORIO DE ITENS VENDIDOS:              \n");
    printf("             %s", ctime(&timer)); // imprime o tempo
    printf("\n--------------------------------------------------\n\n");

    for (int i = 0; i < *contador; i++) // loop para percorrer o vetor de produtos
    {
        if (produto[i]->quantvendida > 0) // se a quantidade vendida for maior que 0
        {
            totalvendido += produto[i]->quantvendida * produto[i]->preco;                                                             // soma o valor total vendido
            printf("%i - %s - %.2f - Quant %i\n", produto[i]->codigo, produto[i]->nome, produto[i]->preco, produto[i]->quantvendida); // imprime o produto vendido
        }
    }

    printf("\n--------------------------------------------------\n");
    printf("               Total: R$ %.2f                  ", totalvendido); // imprime o total vendido
    printf("\n--------------------------------------------------\n");*/
}

void bubblesort(estprod **produto, int *contador)
{
    estprod aux;
    for (int i = 0; i < *contador - 1; i++)
    {
        for (int j = i; j < *contador; j++)
        {
            if ((*produto)[i].codigo > (*produto)[j].codigo)
            {
                aux = (*produto)[i];
                (*produto)[i] = (*produto)[j];
                (*produto)[j] = aux;
            }
        }
    }
}