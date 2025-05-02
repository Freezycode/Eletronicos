#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eletronicos.h"

int main() {
    Produto produtos[512];
    int quantidade = 0;
    char nomeArquivoSaida[100];
    char opcao[10];

    FILE *arquivo = fopen("eletronicos.csv", "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo CSV");
        return 1;
    }

    char linha[256];
    fgets(linha, sizeof(linha), arquivo); 

    while (fgets(linha, sizeof(linha), arquivo)) {
        char *token = strtok(linha, ",");
        strcpy(produtos[quantidade].nome, token);

        token = strtok(NULL, ",");
        strcpy(produtos[quantidade].categoria, token);

        token = strtok(NULL, ",");
        produtos[quantidade].preco = atof(token);

        quantidade++;
    }

    fclose(arquivo);

    printf("Deseja ordenar por:\n");
    printf("Nome\n");
    printf("Categoria\n");
    printf("Preço\n");
    printf("Opção: ");
    fgets(opcao, sizeof(opcao), stdin);

    if (opcao[0] == '1') {
        ordenar_por_nome(produtos, quantidade);
    } else if (opcao[0] == '2') {
        ordenar_por_categoria(produtos, quantidade);
    } else if (opcao[0] == '3') {
        ordenar_por_preco(produtos, quantidade);
    } else {
        printf("Opção inválida.\n");
        return 1;
    }

    printf("Digite o nome do arquivo de saída (sem .csv): ");
    fgets(nomeArquivoSaida, sizeof(nomeArquivoSaida), stdin);
    nomeArquivoSaida[strcspn(nomeArquivoSaida, "\n")] = 0;
    strcat(nomeArquivoSaida, ".csv");

    FILE *saida = fopen(nomeArquivoSaida, "w");
    if (!saida) {
        perror("Erro ao criar o arquivo de saída");
        return 1;
    }

    fprintf(saida, "nome,categoria,preco\n");
    for (int i = 0; i < quantidade; i++) {
        fprintf(saida, "%s,%s,%.2f\n", produtos[i].nome, produtos[i].categoria, produtos[i].preco);
    }

    fclose(saida);
    printf("Arquivo '%s' gerado foi gerado\n", nomeArquivoSaida);
    return 0;
}
