#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct
{
    long int cpf;
    long int rg;
    char nome[50];
    char sexo;
    char data_nascimento[11];
    long int telefones[10];
} faxineiro;

typedef struct
{
    long int cpf;
    char nome[50];
    char data_nascimento[11];
    char endereço[100];
    char cep[10];
    char cidade[100];
    char emails[10][100];
    long int telefones[10];
} cliente;

typedef struct
{
    long int cpf_faxineiro;
    long int cpf_cliente;
    char data[11];
    float valor;
} servico;

faxineiro *carregar_faxineiros(char *nome_arquivo, int *retorno_tamanho_vetor)
{
    FILE *arquivo;
    faxineiro *vetor_faxineiros;
    int i;
    int tamanho_vetor;

    if ((arquivo = fopen(nome_arquivo, "wd+")) == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(0);
    }
    fread(&tamanho_vetor, sizeof(int), 1, arquivo);
    if ((vetor_faxineiros = (faxineiro *)malloc(tamanho_vetor * sizeof(faxineiro))) == NULL)
    {
        perror("Erro ao alocar o vetor");
        exit(0);
    }
    if ((fread(&vetor_faxineiros, sizeof(faxineiro), tamanho_vetor, arquivo) != tamanho_vetor))
    {
        perror("Erro ao carregar os dados");
        exit(0);
    }
    *retorno_tamanho_vetor = tamanho_vetor;
    return vetor_faxineiros;
}

int print_menu()
{
    int opt;
    printf("\n1. Submenu de Faxineiros\n");
    printf("2. Submenu de Clientes\n");
    printf("3. Submenu de Serviços\n");
    printf("4. Submenu Relatórios\n");
    printf("5. Sair\n");
    printf(": ");
    scanf("%d", &opt);

    return opt;
}

int print_submenu(char *tipo_submenu)
{
    int opt; // Listar todos, Listar um, Incluir (sem repetição), Alterar e Excluir
    printf("\n1. Listar todos os %ss\n", tipo_submenu);
    printf("2. Listar um %s\n", tipo_submenu);
    printf("3. Incluir um %s\n", tipo_submenu);
    printf("4. Alterar um %s\n", tipo_submenu);
    printf("5. Excluir um %s\n", tipo_submenu);
    printf("6. Voltar\n");
    printf(": ");
    scanf("%d", &opt);

    return opt;
}

int print_submenu_relatorios()
{
    int opt;
    printf("\n1. Listar clientes de um faxineiro entre datas X até Y\n");
    printf("2. Listar serviços de uma data específica\n");
    printf("3. Listar todos os serviços de um faxineiro (pelo CPF)\n");
    printf("4. Voltar\n");
    printf(": ");
    scanf("%d", &opt);

    return opt;
}

void main_faxineiros()
{
    int opcao;
    do
    {
        opcao = print_submenu("faxineiro");
        switch (opcao)
        {
        case 1:
            // listar todos
            break;
        case 2:
            // listar um
            break;
        case 3:
            // incluir um
            break;
        case 4:
            // alterar um
            break;
        case 5:
            // excluir um
            break;
        case 6:
            printf("\nVoltando...\n");
            break;
        default:
            printf("\nOpção inválida\n");
        }

    } while (opcao != 6);
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    faxineiro *vetor_faxineiros;
    cliente *vetor_clientes;
    servico *vetor_servicos;
    int opcao, tamanho_vetor_faxineiros;
    char nome_arquivo_faxineiros[] = "dados_faxineiros";

    vetor_faxineiros = carregar_faxineiros(nome_arquivo_faxineiros, &tamanho_vetor_faxineiros);
    
    do
    {
        opcao = print_menu();
        switch (opcao)
        {
        case 1:
            // Submenu de Faxineiros
            printf("1. Submenu de Faxineiros");
            break;
        case 2:
            // Submenu de Clientes
            printf("2. Submenu de Clientes");
            break;
        case 3:
            // Submenu de Serviços
            printf("3. Submenu de Serviços");
            break;
        case 4:
            // Submenu Relatórios
            printf("4. Submenu Relatórios");
            break;
        case 5:
            printf("\nSaindo...\n");
            break;
        default:
            printf("\nOpção inválida!\n");
        }
    } while (opcao != 5);
}