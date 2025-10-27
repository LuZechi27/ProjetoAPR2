#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    unsigned long int cpf;
    unsigned long int rg;
    char nome[50];
    char sexo;
    char data_nascimento[11];
    int quantidade_telefones;
    unsigned long int telefones[10];
} faxineiro;

typedef struct
{
    unsigned long int cpf;
    char nome[50];
    char data_nascimento[11];
    char endereço[100];
    char cep[10];
    char cidade[100];
    char emails[10][100];
    int quantidade_telefones;
    unsigned long int telefones[10];
} cliente;

typedef struct
{
    unsigned long int cpf_faxineiro;
    unsigned long int cpf_cliente;
    char data[11];
    float valor;
} servico;

faxineiro *carregar_faxineiros(char *nome_arquivo, int *retorno_tamanho_vetor)
{
    FILE *arquivo;
    faxineiro *vetor_faxineiros;
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
    fclose(arquivo);
    *retorno_tamanho_vetor = tamanho_vetor;
    return vetor_faxineiros;
}

cliente *carregar_clientes(char *nome_arquivo, int *retorno_tamanho_vetor)
{
    FILE *arquivo;
    cliente *vetor_clientes;
    int tamanho_vetor;

    if ((arquivo = fopen(nome_arquivo, "wd+")) == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(0);
    }
    fread(&tamanho_vetor, sizeof(int), 1, arquivo);
    if ((vetor_clientes = (cliente *)malloc(tamanho_vetor * sizeof(cliente))) == NULL)
    {
        perror("Erro ao alocar o vetor");
        exit(0);
    }
    if ((fread(&vetor_clientes, sizeof(cliente), tamanho_vetor, arquivo) != tamanho_vetor))
    {
        perror("Erro ao carregar os dados");
        exit(0);
    }
    fclose(arquivo);
    *retorno_tamanho_vetor = tamanho_vetor;
    return vetor_clientes;
}

servico *carregar_servicos(char *nome_arquivo, int *retorno_tamanho_vetor)
{
    FILE *arquivo;
    servico *vetor_servicos;
    int tamanho_vetor;

    if ((arquivo = fopen(nome_arquivo, "wd+")) == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(0);
    }
    fread(&tamanho_vetor, sizeof(int), 1, arquivo);
    if ((vetor_servicos = (servico *)malloc(tamanho_vetor * sizeof(servico))) == NULL)
    {
        perror("Erro ao alocar o vetor");
        exit(0);
    }
    if ((fread(&vetor_servicos, sizeof(servico), tamanho_vetor, arquivo) != tamanho_vetor))
    {
        perror("Erro ao carregar os dados");
        exit(0);
    }
    fclose(arquivo);
    *retorno_tamanho_vetor = tamanho_vetor;
    return vetor_servicos;
}

void salvar_faxineiros(faxineiro *vetor_faxineiros, int tamanho_vetor, char *nome_do_arquivo)
{
    FILE *arquivo;

    if ((arquivo = fopen(nome_do_arquivo, "wb+")) == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(0);
    }
    fwrite(&tamanho_vetor, sizeof(int), 1, arquivo);
    if ((fwrite(vetor_faxineiros, sizeof(faxineiro), tamanho_vetor, arquivo)) != tamanho_vetor)
    {
        perror("Erro ao salvar os dados");
        exit(0);
    }
    fclose(arquivo);
}

int buscar_faxineiro(faxineiro *faxineiros, int inicio, int fim, unsigned long int cpf_procurado)
{
    int meio = (inicio + fim) / 2;
    if (inicio > fim)
        return -1;
    if (faxineiros[meio].cpf == cpf_procurado)
        return meio;
    if (faxineiros[meio].cpf < cpf_procurado)
        return buscar_faxineiro(faxineiros, meio + 1, fim, cpf_procurado);
    if (faxineiros[meio].cpf > cpf_procurado)
        return buscar_faxineiro(faxineiros, inicio, meio - 1, cpf_procurado);
    return -1;
}

int busca_para_inserir_faxineiro(faxineiro *faxineiros, int inicio, int fim, unsigned long int cpf_procurado)
{
    int meio = (inicio + fim) / 2;
    if (faxineiros[meio].cpf == cpf_procurado)
        return -1;
    if ((fim - inicio) <= 1)
        return inicio;
    if (faxineiros[meio].cpf < cpf_procurado)
        return buscar_faxineiro(faxineiros, meio + 1, fim, cpf_procurado);
    if (faxineiros[meio].cpf > cpf_procurado)
        return buscar_faxineiro(faxineiros, inicio, meio - 1, cpf_procurado);
}

void listar_todos_faxineiros(faxineiro *faxineiros, int tamanho_vetor)
{
    int i, j;
    printf("\nTodos os faxineiros:");
    for (i = 0; i < tamanho_vetor; i++)
    {
        printf("\nNome: %s\n", faxineiros[i].nome);
        printf("CPF : %lu\n", faxineiros[i].cpf);
        printf("RG : %lu\n", faxineiros[i].rg);
        printf("Sexo : %c\n", faxineiros[i].sexo);
        printf("Data de nascimento : %s\n", faxineiros[i].data_nascimento);
        printf("Telefones : ");
        for (j = 0; j < faxineiros[i].quantidade_telefones; j++)
            printf("%lu | ", faxineiros[i].telefones[j]);
        printf("\n");
    }
    puts("\n");
}

void listar_um_faxineiro(faxineiro *faxineiros, unsigned long int cpf)
{
}

bool incluir_um_faxineiro(faxineiro **faxineiros, int *tamanho)
{
    unsigned long int cpf_a_registrar;
    int indice_inserir;
    char terminador;
    printf("\nInforme o CPF a ser cadastrado (apenas numeros. Ex: 01234567890): ");
    scanf("%lu", &cpf_a_registrar);
    if (((indice_inserir = busca_para_inserir_faxineiro(*faxineiros, 0, *tamanho - 1, cpf_a_registrar)) == -1) && *tamanho != 0)
    {
        printf("\nCPF já está cadastrado.\n");
        return false;
    }
    else
    {
        if (*tamanho == 0)
        {
            (*faxineiros)[0].cpf = cpf_a_registrar;
            printf("Informe o RG (somente numeros): ");
            scanf("%lu", &(*faxineiros)[0].rg);
            terminador = getchar();
            printf("Informe o Nome (Tamanho máximo = 50): ");
            fgets((*faxineiros)[0].nome, sizeof((*faxineiros)[0].nome), stdin);
            fgets((*faxineiros)[0].data_nascimento, sizeof((*faxineiros)[0].data_nascimento), stdin);

        }
    }
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

void main_faxineiros(faxineiro *faxineiros, int tamanho_vetor)
{
    int opcao;
    unsigned long int cpf;
    do
    {
        opcao = print_submenu("faxineiro");
        switch (opcao)
        {
        case 1:
            //listar todos
            listar_todos_faxineiros(faxineiros, tamanho_vetor);
            break;
        case 2:
            // listar um
            break;
        case 3:
            // incluir um (sem repeticao)
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
    int opcao, tamanho_vetor_faxineiros, tamanho_vetor_clientes, tamanho_vetor_servicos;
    char nome_arquivo_faxineiros[] = "dados_faxineiros.bin";
    char submenu_faxineiro[] = "faxineiro";
    char submenu_cliente[] = "cliente";
    char submenu_servico[] = "serviço";

    vetor_faxineiros = carregar_faxineiros(nome_arquivo_faxineiros, &tamanho_vetor_faxineiros);

    do
    {
        opcao = print_menu();
        switch (opcao)
        {
        case 1:
            // Submenu de Faxineiros
            printf("1. Submenu de Faxineiros");
            main_faxineiros(vetor_faxineiros, tamanho_vetor_faxineiros);
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