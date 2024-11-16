 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "livros.dat"

typedef struct {
    int codigo;
    char titulo[50];
    char autor[50];
    int ano;
} Livro;

void adicionarLivro() {
    Livro livro;
    FILE *arquivo = fopen(ARQUIVO, "ab");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o código do livro: ");
    scanf("%d", &livro.codigo);
    getchar(); // Limpar buffer
    printf("Digite o título do livro: ");
    fgets(livro.titulo, sizeof(livro.titulo), stdin);
    livro.titulo[strcspn(livro.titulo, "\n")] = '\0';
    printf("Digite o nome do autor: ");
    fgets(livro.autor, sizeof(livro.autor), stdin);
    livro.autor[strcspn(livro.autor, "\n")] = '\0';
    printf("Digite o ano de publicação: ");
    scanf("%d", &livro.ano);

    fwrite(&livro, sizeof(Livro), 1, arquivo);
    fclose(arquivo);

    printf("Livro adicionado com sucesso!\n");
}

void alterarLivro() {
    int codigo, encontrado = 0;
    Livro livro;
    FILE *arquivo = fopen(ARQUIVO, "rb+");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o código do livro a ser alterado: ");
    scanf("%d", &codigo);

    while (fread(&livro, sizeof(Livro), 1, arquivo)) {
        if (livro.codigo == codigo) {
            encontrado = 1;
            printf("Digite o novo título: ");
            getchar(); // Limpar buffer
            fgets(livro.titulo, sizeof(livro.titulo), stdin);
            livro.titulo[strcspn(livro.titulo, "\n")] = '\0';
            printf("Digite o novo autor: ");
            fgets(livro.autor, sizeof(livro.autor), stdin);
            livro.autor[strcspn(livro.autor, "\n")] = '\0';
            printf("Digite o novo ano de publicação: ");
            scanf("%d", &livro.ano);

            fseek(arquivo, -sizeof(Livro), SEEK_CUR);
            fwrite(&livro, sizeof(Livro), 1, arquivo);
            printf("Dados do livro alterados com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Livro não encontrado.\n");
    }

    fclose(arquivo);
}

void excluirLivro() {
    int codigo, encontrado = 0;
    Livro livro;
    FILE *arquivo = fopen(ARQUIVO, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (arquivo == NULL || temp == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o código do livro a ser excluído: ");
    scanf("%d", &codigo);

    while (fread(&livro, sizeof(Livro), 1, arquivo)) {
        if (livro.codigo == codigo) {
            encontrado = 1;
        } else {
            fwrite(&livro, sizeof(Livro), 1, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQUIVO);
    rename("temp.dat", ARQUIVO);

    if (encontrado) {
        printf("Livro excluído com sucesso!\n");
    } else {
        printf("Livro não encontrado.\n");
    }
}

void consultarLivro() {
    int codigo, encontrado = 0;
    Livro livro;
    FILE *arquivo = fopen(ARQUIVO, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o código do livro: ");
    scanf("%d", &codigo);

    while (fread(&livro, sizeof(Livro), 1, arquivo)) {
        if (livro.codigo == codigo) {
            encontrado = 1;
            printf("\nCódigo: %d\n", livro.codigo);
            printf("Título: %s\n", livro.titulo);
            printf("Autor: %s\n", livro.autor);
            printf("Ano de publicação: %d\n", livro.ano);
            break;
        }
    }

    if (!encontrado) {
        printf("Livro não encontrado.\n");
    }

    fclose(arquivo);
}

void listarLivros() {
    Livro livro;
    FILE *arquivo = fopen(ARQUIVO, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("\nLista de Livros:\n");
    printf("----------------------------\n");
    while (fread(&livro, sizeof(Livro), 1, arquivo)) {
        printf("Código: %d\n", livro.codigo);
        printf("Título: %s\n", livro.titulo);
        printf("Autor: %s\n", livro.autor);
        printf("Ano de publicação: %d\n\n", livro.ano);
    }

    fclose(arquivo);
}

int main() {
    int opcao;

    do {
        printf("\n--- Sistema de Gerenciamento de Livros ---\n");
        printf("1. Adicionar Livro\n");
        printf("2. Alterar Livro\n");
        printf("3. Excluir Livro\n");
        printf("4. Consultar Livro\n");
        printf("5. Listar Livros\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarLivro();
                break;
            case 2:
                alterarLivro();
                break;
            case 3:
                excluirLivro();
                break;
            case 4:
                consultarLivro();
                break;
            case 5:
                listarLivros();
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
