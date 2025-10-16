#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct
{
    long int cpf;
    long int rg;
    char *nome;
    char sexo;
    char data_nascimento[11];
    long int *telefones;
} Faxineiro;

typedef struct
{
    char cpf[15];
    char *nome;
    char data_nascimento[11];
    char *endereço;
    char cep[10];
    char *cidade;
    char *emails;
    char *telefones;
} Cliente;

typedef struct
{
    char *cpf_faxineiro;
    char *cpf_cliente;
    char data[11];
    float valor;
} Servico;

Faxineiro *carregar_faxineiros(char *nome_arquivo)
{
    FILE *arquivo;
    Faxineiro *vetor_faxineiros;
    int i;
    int tamanho_vetor, tamanho_nome, quantidade_telefones;
    int tamanho_data_nasc = 11;

    if ((arquivo = fopen(nome_arquivo, "wd+")) == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(0);
    }
    /*
    Conteúdo:

    [quantidade de faxineiros no vetor]
    [cpf][rg][tamanho do nome][nome][sexo][dt nascimento][quantidade de telefones][vetor de telefones]
    [cpf][rg][tamanho do nome][nome][sexo][dt nascimento][quantidade de telefones][vetor de telefones]
    [cpf][rg][tamanho do nome][nome][sexo][dt nascimento][quantidade de telefones][vetor de telefones]
    ...
    */
    fread(&tamanho_vetor, sizeof(int), 1, arquivo);
    vetor_faxineiros = (Faxineiro *)malloc(tamanho_vetor * sizeof(Faxineiro));

    for (i = 0; i < tamanho_vetor; i++)
    {
        if (!feof(arquivo))
        {
            fread(&vetor_faxineiros[i].cpf, sizeof(long int), 1, arquivo);
            fread(&vetor_faxineiros[i].rg, sizeof(long int), 1, arquivo);
            fread(&tamanho_nome, sizeof(int), 1, arquivo);
            if (ferror(arquivo))
            {
                perror("Erro");
                exit(0);
            }
            vetor_faxineiros[i].nome = (char *)malloc(tamanho_nome * sizeof(char));
            if ((fread(&vetor_faxineiros[i].nome, sizeof(char), tamanho_nome, arquivo)) != tamanho_nome)
            {
                perror("Erro ao ler o nome");
                exit(0);
            }
            fread(&vetor_faxineiros[i].sexo, sizeof(char), 1, arquivo);
            fread(&vetor_faxineiros[i].data_nascimento, sizeof(char), tamanho_data_nasc, arquivo);
            if (ferror(arquivo))
            {
                perror("Erro");
                exit(0);
            }
            fread(&quantidade_telefones, sizeof(int), 1, arquivo);
            vetor_faxineiros[i].telefones = (long int *)malloc(quantidade_telefones * sizeof(long int));
            if ((fread(&vetor_faxineiros[i].telefones, sizeof(long int), quantidade_telefones, arquivo)) != quantidade_telefones)
            {
                perror("Erro ao ler os telefones");
                exit(0);
            }
        }
        else
        {
            perror("Erro");
            exit(0);
        }
    }
    return vetor_faxineiros;
}

void salvar_faxineiros()
{
    
}

int menu()
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

int sub_menu(char *tipo_submenu)
{
    int opt; // Listar todos, Listar um, Incluir (sem repetição), Alterar e Excluir
    printf("\n1. Listar todos os %s\n", tipo_submenu);
    printf("2. Listar um %s\n", tipo_submenu);
    printf("3. Incluir um %s\n", tipo_submenu);
    printf("4. Alterar um %s\n", tipo_submenu);
    printf("5. Excluir um %s\n", tipo_submenu);
    printf("6. Voltar\n");
    printf(": ");
    scanf("%d", &opt);

    return opt;
}

int sub_menu_relatorios()
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

int main()
{
    setlocale(LC_ALL, "Portuguese");
    FILE *dados, *relatorios;
    int opcao;
    do
    {
        opcao = menu();
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