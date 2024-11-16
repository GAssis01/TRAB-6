#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "veiculos.dat"

typedef struct {
    int id;
    char modelo[50];
    char placa[10];
    int ano;
} Veiculo;

void adicionarVeiculo() {
    Veiculo veiculo;
    FILE *arquivo = fopen(ARQUIVO, "ab");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o ID do veículo: ");
    scanf("%d", &veiculo.id);
    getchar(); // Limpar o buffer
    printf("Digite o modelo do veículo: ");
    fgets(veiculo.modelo, sizeof(veiculo.modelo), stdin);
    veiculo.modelo[strcspn(veiculo.modelo, "\n")] = '\0';
    printf("Digite a placa do veículo: ");
    fgets(veiculo.placa, sizeof(veiculo.placa), stdin);
    veiculo.placa[strcspn(veiculo.placa, "\n")] = '\0';
    printf("Digite o ano de fabricação: ");
    scanf("%d", &veiculo.ano);

    fwrite(&veiculo, sizeof(Veiculo), 1, arquivo);
    fclose(arquivo);

    printf("Veículo adicionado com sucesso!\n");
}

void alterarVeiculo() {
    int id, encontrado = 0;
    Veiculo veiculo;
    FILE *arquivo = fopen(ARQUIVO, "rb+");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o ID do veículo a ser alterado: ");
    scanf("%d", &id);

    while (fread(&veiculo, sizeof(Veiculo), 1, arquivo)) {
        if (veiculo.id == id) {
            encontrado = 1;
            printf("Digite o novo modelo: ");
            getchar(); // Limpar o buffer
            fgets(veiculo.modelo, sizeof(veiculo.modelo), stdin);
            veiculo.modelo[strcspn(veiculo.modelo, "\n")] = '\0';
            printf("Digite a nova placa: ");
            fgets(veiculo.placa, sizeof(veiculo.placa), stdin);
            veiculo.placa[strcspn(veiculo.placa, "\n")] = '\0';
            printf("Digite o novo ano de fabricação: ");
            scanf("%d", &veiculo.ano);

            fseek(arquivo, -sizeof(Veiculo), SEEK_CUR);
            fwrite(&veiculo, sizeof(Veiculo), 1, arquivo);
            printf("Dados do veículo alterados com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Veículo não encontrado.\n");
    }

    fclose(arquivo);
}

void excluirVeiculo() {
    int id, encontrado = 0;
    Veiculo veiculo;
    FILE *arquivo = fopen(ARQUIVO, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (arquivo == NULL || temp == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite o ID do veículo a ser excluído: ");
    scanf("%d", &id);

    while (fread(&veiculo, sizeof(Veiculo), 1, arquivo)) {
        if (veiculo.id == id) {
            encontrado = 1;
        } else {
            fwrite(&veiculo, sizeof(Veiculo), 1, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQUIVO);
    rename("temp.dat", ARQUIVO);

    if (encontrado) {
        printf("Veículo excluído com sucesso!\n");
    } else {
        printf("Veículo não encontrado.\n");
    }
}

void consultarVeiculo() {
    char placa[10];
    int encontrado = 0;
    Veiculo veiculo;
    FILE *arquivo = fopen(ARQUIVO, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("Digite a placa do veículo: ");
    getchar(); // Limpar o buffer
    fgets(placa, sizeof(placa), stdin);
    placa[strcspn(placa, "\n")] = '\0';

    while (fread(&veiculo, sizeof(Veiculo), 1, arquivo)) {
        if (strcmp(veiculo.placa, placa) == 0) {
            encontrado = 1;
            printf("\nID: %d\n", veiculo.id);
            printf("Modelo: %s\n", veiculo.modelo);
            printf("Placa: %s\n", veiculo.placa);
            printf("Ano de fabricação: %d\n", veiculo.ano);
            break;
        }
    }

    if (!encontrado) {
        printf("Veículo não encontrado.\n");
    }

    fclose(arquivo);
}

void listarVeiculos() {
    Veiculo veiculo;
    FILE *arquivo = fopen(ARQUIVO, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("\nLista de Veículos:\n");
    printf("----------------------------\n");
    while (fread(&veiculo, sizeof(Veiculo), 1, arquivo)) {
        printf("ID: %d\n", veiculo.id);
        printf("Modelo: %s\n", veiculo.modelo);
        printf("Placa: %s\n", veiculo.placa);
        printf("Ano de fabricação: %d\n\n", veiculo.ano);
    }

    fclose(arquivo);
}

int main() {
    int opcao;

    do {
        printf("\n--- Sistema de Registro de Veículos ---\n");
        printf("1. Adicionar Veículo\n");
        printf("2. Alterar Veículo\n");
        printf("3. Excluir Veículo\n");
        printf("4. Consultar Veículo pela Placa\n");
        printf("5. Listar Veículos\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarVeiculo();
                break;
            case 2:
                alterarVeiculo();
                break;
            case 3:
                excluirVeiculo();
                break;
            case 4:
                consultarVeiculo();
                break;
            case 5:
                listarVeiculos();
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
