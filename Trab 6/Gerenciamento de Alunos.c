#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "alunos.dat"

typedef struct {
    int matricula;
    char nome[50];
    char curso[30];
    int idade;
} Aluno;

void incluirAluno() {
    Aluno aluno;
    FILE *arquivo = fopen(ARQUIVO, "ab");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o número de matrícula: ");
    scanf("%d", &aluno.matricula);
    getchar(); // Limpar buffer
    printf("Digite o nome do aluno: ");
    fgets(aluno.nome, sizeof(aluno.nome), stdin);
    aluno.nome[strcspn(aluno.nome, "\n")] = '\0';
    printf("Digite o curso: ");
    fgets(aluno.curso, sizeof(aluno.curso), stdin);
    aluno.curso[strcspn(aluno.curso, "\n")] = '\0';
    printf("Digite a idade: ");
    scanf("%d", &aluno.idade);

    fwrite(&aluno, sizeof(Aluno), 1, arquivo);
    fclose(arquivo);

    printf("Aluno incluído com sucesso!\n");
}

void alterarAluno() {
    int matricula, encontrado = 0;
    Aluno aluno;
    FILE *arquivo = fopen(ARQUIVO, "rb+");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o número de matrícula do aluno a ser alterado: ");
    scanf("%d", &matricula);

    while (fread(&aluno, sizeof(Aluno), 1, arquivo)) {
        if (aluno.matricula == matricula) {
            encontrado = 1;
            printf("Digite o novo nome: ");
            getchar();
            fgets(aluno.nome, sizeof(aluno.nome), stdin);
            aluno.nome[strcspn(aluno.nome, "\n")] = '\0';
            printf("Digite o novo curso: ");
            fgets

