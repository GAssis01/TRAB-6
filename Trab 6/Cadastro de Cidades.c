#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "cidades.txt"
#define TEMP "temp.txt"

typedef struct {
    int codigo;
    char nome[50];
    char estado[30];
    int populacao;
} Cidade;

void incluirCidade() {
    Cidade cidade;
    FILE *arquivo = fopen(ARQUIVO, "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o código da cidade: ");
    scanf("%d", &cidade.codigo);
    getchar(); // Limpar o buffer
    printf("Digite o nome da cidade: ");
    fgets(cidade.nome, sizeof(cidade.nome), stdin);
    cidade.nome[strcspn(cidade.nome, "\n")] = '\0';
    printf("Digite o estado da cidade: ");
    fgets(cidade.estado, sizeof(cidade.estado), stdin);
    cidade.estado[strcspn(cidade.estado, "\n")] = '\0';
    printf("Digite a população da cidade: ");
    scanf("%d", &cidade.populacao);

    fprintf(arquivo, "%d,%s,%s,%d\n", cidade.codigo, cidade.nome, cidade.estado, cidade.populacao);
    fclose(arquivo);

    printf("Cidade adicionada com sucesso!\n");
}

void alterarCidade() {
    int codigo, encontrado = 0;
    Cidade cidade;
    FILE *arquivo = fopen(ARQUIVO, "r");
    FILE *temp = fopen(TEMP, "w");

    if (arquivo == NULL || temp == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o código da cidade a ser alterada: ");
    scanf("%d", &codigo);

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        if (cidade.codigo == codigo) {
            encontrado = 1;
            printf("Digite o novo nome da cidade: ");
            getchar(); // Limpar o buffer
            fgets(cidade.nome, sizeof(cidade.nome), stdin);
            cidade.nome[strcspn(cidade.nome, "\n")] = '\0';
            printf("Digite o novo estado da cidade: ");
            fgets(cidade.estado, sizeof(cidade.estado), stdin);
            cidade.estado[strcspn(cidade.estado, "\n")] = '\0';
            printf("Digite a nova população da cidade: ");
            scanf("%d", &cidade.populacao);
        }
        fprintf(temp, "%d,%s,%s,%d\n", cidade.codigo, cidade.nome, cidade.estado, cidade.populacao);
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQUIVO);
    rename(TEMP, ARQUIVO);

    if (encontrado) {
        printf("Cidade alterada com sucesso!\n");
    } else {
        printf("Cidade não encontrada.\n");
    }
}

void excluirCidade() {
    int codigo, encontrado = 0;
    Cidade cidade;
    FILE *arquivo = fopen(ARQUIVO, "r");
    FILE *temp = fopen(TEMP, "w");

    if (arquivo == NULL || temp == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o código da cidade a ser excluída: ");
    scanf("%d", &codigo);

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        if (cidade.codigo == codigo) {
            encontrado = 1;
        } else {
            fprintf(temp, "%d,%s,%s,%d\n", cidade.codigo, cidade.nome, cidade.estado, cidade.populacao);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQUIVO);
    rename(TEMP, ARQUIVO);

    if (encontrado) {
        printf("Cidade excluída com sucesso!\n");
    } else {
        printf("Cidade não encontrada.\n");
    }
}

void consultarCidade() {
    int codigo, encontrado = 0;
    Cidade cidade;
    FILE *arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o código da cidade: ");
    scanf("%d", &codigo);

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        if (cidade.codigo == codigo) {
            encontrado = 1;
            printf("\nCódigo: %d\n", cidade.codigo);
            printf("Nome: %s\n", cidade.nome);
            printf("Estado: %s\n", cidade.estado);
            printf("População: %d\n", cidade.populacao);
            break;
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("Cidade não encontrada.\n");
    }
}

void listarCidades() {
    Cidade cidade;
    FILE *arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("\nLista de Cidades:\n");
    printf("----------------------------\n");
    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        printf("Código: %d\n", cidade.codigo);
        printf("Nome: %s\n", cidade.nome);
        printf("Estado: %s\n", cidade.estado);
        printf("População: %d\n\n", cidade.populacao);
    }

    fclose(arquivo);
}

int main() {
    int opcao;

    do {
        printf("\n--- Sistema de Cadastro de Cidades ---\n");
        printf("1. Incluir Cidade\n");
        printf("2. Alterar Dados da Cidade\n");
        printf("3. Excluir Cidade\n");
        printf("4. Consultar Cidade\n");
        printf("5. Listar Cidades\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                incluirCidade();
                break;
            case 2:
                alterarCidade();
                break;
            case 3:
                excluirCidade();
                break;
            case 4:
                consultarCidade();
                break;
            case 5:
                listarCidades();
                break;
            case 6:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 6);

    return 0;
}
