#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estruturas para Paciente e Consulta com lista duplamente encadeada
typedef struct Paciente {
    int id;
    char nome[100];
    struct Paciente *prox;
    struct Paciente *ant;
} Paciente;

typedef struct Consulta {
    int idConsulta;
    int idPaciente;
    char data[11]; // formato: dd/mm/aaaa
    struct Consulta *prox;
    struct Consulta *ant;
} Consulta;

// Variáveis globais para controle de IDs
int proximoIdPaciente = 1;
int proximoIdConsulta = 1; 

// Função para limpar a tela
void limparTela() {
    system("cls");
}

// Funções para manipulação de Pacientes
Paciente* criarPaciente(int id, const char* nome) {
    Paciente *novo = (Paciente*)malloc(sizeof(Paciente));
    novo->id = id;
    strcpy(novo->nome, nome);
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}

void adicionarPaciente(Paciente **lista, const char* nome) {
    Paciente *novo = criarPaciente(proximoIdPaciente++, nome); // Incrementa ID automaticamente
    novo->prox = *lista;
    if (*lista != NULL) {
        (*lista)->ant = novo;
    }
    *lista = novo;
}

void listarPacientes(Paciente *lista) {
    Paciente *atual = lista;
    while (atual != NULL) {
        printf("ID: %d, Nome: %s\n", atual->id, atual->nome);
        atual = atual->prox;
    }
}

// Funções para manipulação de Consultas
Consulta* criarConsulta(int idConsulta, int idPaciente, const char* data) {
    Consulta *nova = (Consulta*)malloc(sizeof(Consulta));
    nova->idConsulta = idConsulta;
    nova->idPaciente = idPaciente;
    strcpy(nova->data, data);
    nova->prox = NULL;
    nova->ant = NULL;
    return nova;
}

void adicionarConsulta(Consulta **lista, int idPaciente, const char* data) {
    Consulta *nova = criarConsulta(proximoIdConsulta++, idPaciente, data); // Incrementa ID do agendamento automaticamente
    nova->prox = *lista;
    if (*lista != NULL) {
        (*lista)->ant = nova;
    }
    *lista = nova;
}

void listarConsultas(Consulta *lista, Paciente *pacientes) {
    Consulta *atual = lista;
    while (atual != NULL) {
        // Encontrar o nome do paciente correspondente
        Paciente *pacienteAtual = pacientes;
        char nomePaciente[100] = "Desconhecido"; // Caso o paciente não seja encontrado

        while (pacienteAtual != NULL) {
            if (pacienteAtual->id == atual->idPaciente) {
                strcpy(nomePaciente, pacienteAtual->nome);
                break;
            }
            pacienteAtual = pacienteAtual->prox;
        }

        printf("Agendamento ID: %d, Paciente: %s, Data: %s\n", atual->idConsulta, nomePaciente, atual->data);
        atual = atual->prox;
    }
}


int main() {
    setlocale(LC_ALL, "Portuguese");

    Paciente *listaPacientes = NULL;
    Consulta *listaConsultas = NULL;
    int op, idPaciente;
    char nome[100], data[11];

    do {
        limparTela(); // Limpa a tela antes de mostrar o menu
        printf("\nMenu:\n");
        printf("1. Adicionar Paciente\n");
        printf("2. Listar Pacientes\n");
        printf("3. Adicionar Consulta\n");
        printf("4. Listar Consultas\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1:
                limparTela();
                printf("Digite o nome do paciente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0; // Remove a nova linha do final
                adicionarPaciente(&listaPacientes, nome);
                printf("Paciente adicionado com sucesso!\n");
                break;
            case 2:
                limparTela();
                printf("\nPacientes:\n");
                listarPacientes(listaPacientes);
                break;
            case 3:
                limparTela();
                printf("Pacientes disponíveis:\n");
                listarPacientes(listaPacientes); // Lista pacientes antes de adicionar consulta
                printf("Digite o ID do paciente: ");
                scanf("%d", &idPaciente);
                printf("Digite a data da consulta (dd/mm/aaaa): ");
                scanf("%s", data);
                adicionarConsulta(&listaConsultas, idPaciente, data); // Adiciona a consulta
                printf("Consulta adicionada com sucesso!\n");
                break;
            case 4:
                limparTela();
                printf("\nConsultas:\n");
                listarConsultas(listaConsultas, listaPacientes); // Passa a lista de pacientes
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
        printf("\nPressione Enter para continuar...");
        getchar(); // Espera o usuário pressionar Enter
    } while (op != 5);

    return 0;
}

