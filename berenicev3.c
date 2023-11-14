#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int codigo;
    char nome[25];
    float preco;
    int quantestoque;
    int quantvendida;
    int quantvendidacupom;
} estprod;

estprod *produto = NULL;
int contador = 0;

void submenuprodutos();
void submenuvendas();
void exibir();
void cadastrarproduto();
void atualizarproduto();
int verificacao(int codeverif);
void excluirproduto();
void salvarprodutos();
void lerprodutos();
void realizarvenda();
void pagamentoavista(float total);
void pagamentocartao(float total);
void cupomfiscal(float novototal);
void relatorio();

int main()
{
    int opc, continuar = 1;

    time_t timer;
    time(&timer);

    printf("BEM VINDO AO SISTEMA DE VENDAS - BERENICE V3 - %s", ctime(&timer));
    while (continuar)
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
            submenuprodutos();
            break;
        case 2:
            submenuvendas();
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
                salvarprodutos();
                continuar = 0;
                break;
            }
            else if (opc == 1)
            {
                printf("Saindo...\n");
                continuar = 0;
                break;
            }
            else
            {
                printf("Opcao invalida\n");
            }
        }
    }

    free(produto);

    return 0;
}

void submenuprodutos()
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
            exibir();
            break;
        case 2:
            cadastrarproduto();
            break;
        case 3:
            atualizarproduto();
            break;
        case 4:
            excluirproduto();
            break;
        case 5:
            salvarprodutos();
            break;
        case 6:
            lerprodutos();
            break;
        case 7:
            return;
        default:
            printf("Opcao invalida\n");
        }
    }
}

void submenuvendas()
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
            realizarvenda();
            break;
        case 2:
            relatorio();
            break;
        case 3:
            return;
        default:
            printf("Opcao invalida\n");
        }
    }
}

void cadastrarproduto()
{
    int verif, codeverif;
    printf("Digite o codigo do produto: ");
    scanf("%d", &codeverif);
    getchar();
    verif = verificacao(codeverif);
    printf("Verificacao: %d\n", verif);
    if (verif != -1)
    {
        printf("Produto com o mesmo código já existe.\n");
        return;
    }

    if (contador == 0)
    {
        produto = (estprod *)malloc((contador + 1) * sizeof(estprod));
    }
    else
    {
        produto = (estprod *)realloc(produto, (contador + 1) * sizeof(estprod));
    }

    printf("Codigo %i disponivel ", codeverif);
    produto[contador].codigo = codeverif;
    printf("\nDigite o nome do produto: ");
    gets(produto[contador].nome);
    fflush(stdin);
    printf("Digite o preco do produto: ");
    scanf("%f", &produto[contador].preco);
    printf("Digite a quantidade em estoque do produto: ");
    scanf("%d", &produto[contador].quantestoque);
    getchar();
    printf("Codigo: %d\n", produto[contador].codigo);
    printf("Nome: %s\n", produto[contador].nome);
    printf("Preco: %.2f\n", produto[contador].preco);
    printf("Estoque: %d\n", produto[contador].quantestoque);
    contador++;
}

void exibir()
{
    printf("\nPRODUTOS:");
    printf("\n--------------------------------------------------\n");
    for (int i = 0; i < contador; i++)
    {
        printf(" Cod %d | %s | R$ %.2f | Quant %i\n", produto[i].codigo, produto[i].nome, produto[i].preco, produto[i].quantestoque);
        printf("--------------------------------------------------\n");
    }
}

int verificacao(int codeverif)
{
    for (int i = 0; i < contador; i++)
    {
        if (codeverif == produto[i].codigo)
        {
            return i; // Retorna o indice do produto encontrado
        }
    }
    return -1; // Retorna -1 se o produto não for encontrado
}

void atualizarproduto()
{
    int indice, codeverif, opc;
    printf("Digite o codigo do produto: ");
    scanf("%d", &codeverif);
    getchar();
    indice = verificacao(codeverif);
    printf("Verificacao: %d\n", indice);
    if (indice == -1)
    {
        printf("Produto nao encontrado.\n");
    }
    else
    {
        printf("Qual informacao gostaria de atualizar:\n");
        printf("1 - Preco\n");
        printf("2 - Estoque\n");
        printf("3 - Voltar\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opc);
        getchar();
        switch (opc)
        {
        case 1:
            printf(" Cod %d | %s | R$ %.2f | Quant %i\n", produto[indice].codigo, produto[indice].nome, produto[indice].preco, produto[indice].quantestoque);
            printf("Digite o novo preco: ");
            scanf("%f", &produto[indice].preco);
            getchar();
            printf(" Cod %d | %s | R$ %.2f | Quant %i\n", produto[indice].codigo, produto[indice].nome, produto[indice].preco, produto[indice].quantestoque);
            break;
        case 2:
            printf(" Cod %d | %s | R$ %.2f | Quant %i\n", produto[indice].codigo, produto[indice].nome, produto[indice].preco, produto[indice].quantestoque);
            printf("Digite a nova quantidade em estoque: ");
            scanf("%d", &produto[indice].quantestoque);
            getchar();
            printf(" Cod %d | %s | R$ %.2f | Quant %i\n", produto[indice].codigo, produto[indice].nome, produto[indice].preco, produto[indice].quantestoque);
            break;
        case 3:
            return;
            break;
        default:
            printf("Opcao invalida\n");
            break;
        }
    }
}

void excluirproduto()
{
    int indice, codeverif, opc;
    printf("Digite o codigo do produto: ");
    scanf("%d", &codeverif);
    getchar();
    indice = verificacao(codeverif);
    printf("Verificacao: %d\n", indice);
    if (indice == -1)
    {
        printf("Produto nao encontrado.\n");
    }
    else
    {
        if (indice >= 0)
        {
            printf("Cod %d | %s | R$ %.2f | Quant %i\n", produto[indice].codigo, produto[indice].nome, produto[indice].preco, produto[indice].quantestoque);
            printf("Deseja excluir este produto?\n");
            printf("1 - Sim\n");
            printf("2 - Nao\n");
            printf("Digite a opcao desejada: ");
            scanf("%d", &opc);
            getchar();
            if (opc == 1)
            {
                for (int i = indice; i < contador - 1; i++)
                {
                    produto[i] = produto[i + 1];
                }
                contador--;
                produto = (estprod *)realloc(produto, (contador) * sizeof(estprod));
                printf("Produto excluido com sucesso.\n");
            }
            else if (opc == 2)
            {
                return;
                printf("Produto nao excluido.\n");
            }
            else
            {
                printf("Opcao invalida\n");
            }
        }
    }
}

void salvarprodutos()
{
    FILE *fp;
    fp = fopen("produtos.txt", "w");
    if (fp == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
    }
    else
    {
        for (int i = 0; i < contador; i++)
        {
            fprintf(fp, "%d\n%s\n%.2f\n%d\n%d\n%d\n\n", produto[i].codigo, produto[i].nome, produto[i].preco, produto[i].quantestoque, produto[i].quantvendida, produto[i].quantvendidacupom);
        }
        printf("Arquivo salvo com sucesso.\n");
        fclose(fp);
    }
}

void lerprodutos()
{
    FILE *fp;
    fp = fopen("produtos.txt", "r");

    if (fp == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    contador = 0;

    if (produto != NULL)
    {
        free(produto);
    }

    estprod temporaria; // Variável temporária para armazenar os dados lidos

    while (fscanf(fp, "%d\n%s\n%f\n%d\n%d\n%d\n\n", &temporaria.codigo, temporaria.nome, &temporaria.preco, &temporaria.quantestoque, &temporaria.quantvendida, &temporaria.quantvendidacupom) == 6) // faz enquanto estiver lendo 5 valores
    {
        if (contador == 0)
        {
            produto = (estprod *)malloc(sizeof(estprod));
        }
        else
        {
            produto = (estprod *)realloc(produto, (contador + 1) * sizeof(estprod));
        }

        produto[contador] = temporaria;
        contador++;
    }

    fclose(fp);
}

void realizarvenda()
{
    int codeverif, indice, quantidade, formadepagamento;
    int continuar = 1;
    float subtotal, total;

    while (continuar)
    {

        printf("\n\nRealizar Venda [ 0 - FORMA DE PAGAMENTO]\n"); // 0 para ir para forma de pagamento
        exibir();
        printf("Digite o codigo do produto: ");
        scanf("%d", &codeverif);
        getchar();
        if (codeverif == 0)
        {
            continuar = 1;
        }
        else
        {
            indice = verificacao(codeverif);
            printf("Verificacao: %d\n", indice);
            printf("Selecionou o item: %s\n", produto[indice].nome);
            if (indice == -1)
            {
                printf("Produto nao encontrado\n");
                return;
            }
            else
            {
                printf("Digite a quantidade desejada: ");
                scanf("%d", &quantidade);
                getchar;
                if (quantidade <= produto[indice].quantestoque && quantidade > 0)
                {
                    subtotal = quantidade * produto[indice].preco;
                    total += subtotal;
                    produto[indice].quantestoque -= quantidade;
                    produto[indice].quantvendida += quantidade;
                    produto[indice].quantvendidacupom += quantidade;
                }
            }
            printf("total: %.2f\n", total);
            do
            {
                printf("Escolha a forma de pagamento:\n");
                printf("1 - Dinheiro\n");
                printf("2 - Cartao\n");
                printf("Digite a opcao desejada: ");
                scanf("%d", &formadepagamento);
                getchar();
                if (formadepagamento == 1)
                {
                    pagamentoavista(total);
                }
                else if (formadepagamento == 2)
                {
                    pagamentocartao(total);
                }
            } while (formadepagamento != 1 && formadepagamento != 2 && formadepagamento);
        }
        else
        {
            printf("Quantidade inserida superior a quantidade disponivel de %i unidades\n", produto[indice].quantestoque);
        }
    }
}

void pagamentoavista(float total)
{
    float valorrecebido, novototal, desconto, troco;

    printf("Insira o valor recebido: ");
    scanf("%f", &valorrecebido);
    getchar();

    while (valorrecebido < total || valorrecebido < 0)
    {
        printf("Valor invalido\n");
        printf("Insira o valor recebido: ");
        scanf("%f", &valorrecebido);
        getchar();
    }
    if (total > 1 && total <= 50)
    {
        novototal = total - (total * 0.05);
        desconto = total * 0.05;
        troco = valorrecebido - (total - desconto);
        printf("\nSeu troco com desconto e: %.2f\nSeu desconto foi de %.2f\n", troco, desconto);
        cupomfiscal(novototal);
    }
    else if (total > 50 && total < 100)
    {
        novototal = total - (total * 0.1);
        desconto = total * 0.10;
        troco = valorrecebido - (total - desconto);
        printf("\nSeu troco com desconto e: %.2f\nSeu desconto foi de %.2f\n", troco, desconto);
        cupomfiscal(novototal);
    }
    else if (total >= 100)
    {
        novototal = total - (total * 0.18);
        desconto = total * 0.18;
        troco = valorrecebido - (total - desconto);
        printf("\nSeu troco com desconto e: %.2f\nSeu desconto foi de %.2f\n", troco, desconto);
        cupomfiscal(novototal);
    }
    else
    {
        printf("\nEntrada inválida de valor recebido\n");
    }
}

void pagamentocartao(float total)
{

    int nparcelas;
    float novototal, valor_parcela = 0.0;

    printf("Insira o numero das parcelas: ");
    scanf("%d", &nparcelas);
    getchar();
    while (nparcelas <= 0)
    {
        printf("\nNumero de parcelas incorreta, tente novamente\n");

        printf("\nInsira o numero das parcelas: ");
        scanf("%d", &nparcelas);
        getchar();
    }

    if (nparcelas >= 1 && nparcelas <= 3)
    {
        novototal = total + (total * 0.05);
        valor_parcela = novototal / nparcelas;
        printf("\nO total com acrescimo 5%% e %.2f\nO valor de cada parcela e %.2f\n\n", novototal, valor_parcela);
        cupomfiscal(novototal);
    }
    else if (nparcelas > 3)
    {
        novototal = total + (total * 0.08);
        valor_parcela = novototal / nparcelas;
        printf("\nO total com acrescimo de 8%% e %.2f\nO valor de cada parcela e %.2f\n\n", novototal, valor_parcela);
        cupomfiscal(novototal);
    }
}

void cupomfiscal(float novototal)
{
    float itemtotal = 0, totalcupom;
    printf("\n--------------------------------------------------\n");
    printf("                   CUPOM FISCAL:                      ");
    printf("\n--------------------------------------------------\n\n");

    for (int i = 0; i < contador; i++)
    {
        if (produto[i].quantvendidacupom > 0)
        {
            totalcupom += itemtotal = produto[i].quantvendidacupom * produto[i].preco;
            printf("%i - %s - %.2f - Quant %i - R$ %.2f\n", produto[i].codigo, produto[i].nome, produto[i].preco, produto[i].quantvendidacupom, itemtotal);
            produto[i].quantvendidacupom = 0;
        }
    }

    printf("\n--------------------------------------------------\n");
    printf("             Desconto: R$ %.2f                  \n", totalcupom - novototal);
    printf("             Total do cupom: R$ %.2f                  ", novototal);
    printf("\n--------------------------------------------------\n");
}

void relatorio()
{
    float totalvendido;
    printf("\n--------------------------------------------------\n");
    printf("            RELATORIO DE ITENS VENDIDOS:              ");
    printf("\n--------------------------------------------------\n\n");

    for (int i = 0; i < contador; i++)
    {
        if (produto[i].quantvendida > 0)
        {
            totalvendido += produto[i].quantvendida * produto[i].preco;
            printf("%i - %s - %.2f - Quant %i\n", produto[i].codigo, produto[i].nome, produto[i].preco, produto[i].quantvendida);
        }
    }
    printf("\n--------------------------------------------------\n");
    printf("             Total: R$ %.2f                  ", totalvendido);
    printf("\n--------------------------------------------------\n");
}