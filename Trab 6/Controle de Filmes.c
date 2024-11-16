#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "filmes.dat"

typedef struct {
    int id;
    char titulo[50];
    char genero[20];
    int ano;
} Filme;

void adicionarFilme() {
    Filme filme;
    FILE *arquivo = fopen(ARQUIVO, "ab");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o ID do filme: ");
    scanf("%d", &filme.id);
    getchar(); // Limpar o buffer
    printf("Digite o título do filme: ");
    fgets(filme.titulo, sizeof(filme.titulo), stdin);
    filme.titulo[strcspn(filme.titulo, "\n")] = '\0';
    printf("Digite o gênero do filme: ");
    fgets(filme.genero, sizeof(filme.genero), stdin);
    filme.genero[strcspn(filme.genero, "\n")] = '\0';
    printf("Digite o ano de lançamento: ");
    scanf("%d", &filme.ano);

    fwrite(&filme, sizeof(Filme), 1, arquivo);
    fclose(arquivo);

    printf("Filme adicionado com sucesso!\n");
}

void alterarFilme() {
    int id, encontrado = 0;
    Filme filme;
    FILE *arquivo = fopen(ARQUIVO, "rb+");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o ID do filme a ser alterado: ");
    scanf("%d", &id);

    while (fread(&filme, sizeof(Filme), 1, arquivo)) {
        if (filme.id == id) {
            encontrado = 1;
            printf("Digite o novo título: ");
            getchar(); // Limpar o buffer
            fgets(filme.titulo, sizeof(filme.titulo), stdin);
            filme.titulo[strcspn(filme.titulo, "\n")] = '\0';
            printf("Digite o novo gênero: ");
            fgets(filme.genero, sizeof(filme.genero), stdin);
            filme.genero[strcspn(filme.genero, "\n")] = '\0';
            printf("Digite o novo ano de lançamento: ");
            scanf("%d", &filme.ano);

            fseek(arquivo, -sizeof(Filme), SEEK_CUR);
            fwrite(&filme, sizeof(Filme), 1, arquivo);
            printf("Dados do filme alterados com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Filme não encontrado.\n");
    }

    fclose(arquivo);
}

void excluirFilme() {
    int id, encontrado = 0;
    Filme filme;
    FILE *arquivo = fopen(ARQUIVO, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (arquivo == NULL || temp == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o ID do filme a ser excluído: ");
    scanf("%d", &id);

    while (fread(&filme, sizeof(Filme), 1, arquivo)) {
        if (filme.id == id) {
            encontrado = 1;
        } else {
            fwrite(&filme, sizeof(Filme), 1, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQUIVO);
    rename("temp.dat", ARQUIVO);

    if (encontrado) {
        printf("Filme excluído com sucesso!\n");
    } else {
        printf("Filme não encontrado.\n");
    }
}

void consultarFilme() {
    int id, encontrado = 0;
    Filme filme;
    FILE *arquivo = fopen(ARQUIVO, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o ID do filme: ");
    scanf("%d", &id);

    while (fread(&filme, sizeof(Filme), 1, arquivo)) {
        if (filme.id == id) {
            encontrado = 1;
            printf("\nID: %d\n", filme.id);
            printf("Título: %s\n", filme.titulo);
            printf("Gênero: %s\n", filme.genero);
            printf("Ano de lançamento: %d\n", filme.ano);
            break;
        }
    }

    if (!encontrado) {
        printf("Filme não encontrado.\n");
    }

    fclose(arquivo);
}

void listarFilmes() {
    Filme filme;
    FILE *arquivo = fopen(ARQUIVO, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("\nLista de Filmes:\n");
    printf("----------------------------\n");
    while (fread(&filme, sizeof(Filme), 1, arquivo)) {
        printf("ID: %d\n", filme.id);
        printf("Título: %s\n", filme.titulo);
        printf("Gênero: %s\n", filme.genero);
        printf("Ano de lançamento: %d\n\n", filme.ano);
    }

    fclose(arquivo);
}

int main() {
    int opcao;

    do {
        printf("\n--- Sistema de Controle de Filmes ---\n");
        printf("1. Adicionar Filme\n");
        printf("2. Alterar Filme\n");
        printf("3. Excluir Filme\n");
        printf("4. Consultar Filme pelo ID\n");
        printf("5. Listar Filmes\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarFilme();
                break;
            case 2:
                alterarFilme();
                break;
            case 3:
                excluirFilme();
                break;
            case 4:
                consultarFilme();
                break;
            case 5:
                listarFilmes();
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
