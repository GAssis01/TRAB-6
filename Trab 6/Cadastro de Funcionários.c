 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "funcionarios.dat"

typedef struct {
    int id;
    char nome[50];
    char cargo[30];
    int salario;
} Funcionario;

void cadastrarFuncionario() {
    Funcionario func;
    FILE *arquivo = fopen(ARQUIVO, "ab");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o ID do funcionário: ");
    scanf("%d", &func.id);
    getchar(); // Limpar o buffer do teclado
    printf("Digite o nome do funcionário: ");
    fgets(func.nome, sizeof(func.nome), stdin);
    func.nome[strcspn(func.nome, "\n")] = '\0';
    printf("Digite o cargo: ");
    fgets(func.cargo, sizeof(func.cargo), stdin);
    func.cargo[strcspn(func.cargo, "\n")] = '\0';
    printf("Digite o salário: ");
    scanf("%d", &func.salario);

    fwrite(&func, sizeof(Funcionario), 1, arquivo);
    fclose(arquivo);

    printf("Funcionário cadastrado com sucesso!\n");
}

void alterarFuncionario() {
    int id, encontrado = 0;
    Funcionario func;
    FILE *arquivo = fopen(ARQUIVO, "rb+");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o ID do funcionário a ser alterado: ");
    scanf("%d", &id);

    while (fread(&func, sizeof(Funcionario), 1, arquivo)) {
        if (func.id == id) {
            encontrado = 1;
            printf("Digite o novo cargo: ");
            getchar(); // Limpar o buffer
            fgets(func.cargo, sizeof(func.cargo), stdin);
            func.cargo[strcspn(func.cargo, "\n")] = '\0';
            printf("Digite o novo salário: ");
            scanf("%d", &func.salario);

            fseek(arquivo, -sizeof(Funcionario), SEEK_CUR);
            fwrite(&func, sizeof(Funcionario), 1, arquivo);
            printf("Dados do funcionário alterados com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Funcionário não encontrado.\n");
    }

    fclose(arquivo);
}

void excluirFuncionario() {
    int id, encontrado = 0;
    Funcionario func;
    FILE *arquivo = fopen(ARQUIVO, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (arquivo == NULL || temp == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o ID do funcionário a ser excluído: ");
    scanf("%d", &id);

    while (fread(&func, sizeof(Funcionario), 1, arquivo)) {
        if (func.id == id) {
            encontrado = 1;
        } else {
            fwrite(&func, sizeof(Funcionario), 1, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQUIVO);
    rename("temp.dat", ARQUIVO);

    if (encontrado) {
        printf("Funcionário excluído com sucesso!\n");
    } else {
        printf("Funcionário não encontrado.\n");
    }
}

void consultarFuncionario() {
    int id, encontrado = 0;
    Funcionario func;
    FILE *arquivo = fopen(ARQUIVO, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o ID do funcionário: ");
    scanf("%d", &id);

    while (fread(&func, sizeof(Funcionario), 1, arquivo)) {
        if (func.id == id) {
            encontrado = 1;
            printf("\nID: %d\n", func.id);
            printf("Nome: %s\n", func.nome);
            printf("Cargo: %s\n", func.cargo);
            printf("Salário: R$ %d\n", func.salario);
            break;
        }
    }

    if (!encontrado) {
        printf("Funcionário não encontrado.\n");
    }

    fclose(arquivo);
}

void listarFuncionarios() {
    Funcionario func;
    FILE *arquivo = fopen(ARQUIVO, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("\nLista de Funcionários:\n");
    printf("----------------------------\n");
    while (fread(&func, sizeof(Funcionario), 1, arquivo)) {
        printf("ID: %d\n", func.id);
        printf("Nome: %s\n", func.nome);
        printf("Cargo: %s\n", func.cargo);
        printf("Salário: R$ %d\n\n", func.salario);
    }

    fclose(arquivo);
}

int main() {
    int opcao;

    do {
        printf("\n--- Sistema de Cadastro de Funcionários ---\n");
        printf("1. Cadastrar Funcionário\n");
        printf("2. Alterar Funcionário\n");
        printf("3. Excluir Funcionário\n");
        printf("4. Consultar Funcionário\n");
        printf("5. Listar Funcionários\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarFuncionario();
                break;
            case 2:
                alterarFuncionario();
                break;
            case 3:
                excluirFuncionario();
                break;
            case 4:
                consultarFuncionario();
                break;
            case 5:
                listarFuncionarios();
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
