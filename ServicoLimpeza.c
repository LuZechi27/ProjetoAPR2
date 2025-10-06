#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct
{
    char cpf[15];
    char rg[15];
    char *nome;
    char sexo;
    char dataNascimento[11];
    char *telefones;
} faxineiro;

typedef struct
{
    char cpf[15];
    char *nome;
    char dataNascimento[11];
    char *endereço;
    char *cep;
    char *cidade;
    char *emails;
    char *telefones;
} cliente;

typedef struct
{
    char *cpfFaxineiro;
    char *cpfCliente;
    char data[11];
    int valor;
} servico;

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

int subMenu()
{
    int opt; //Listar todos, Listar um, Incluir (sem repetição), Alterar e Excluir
    printf("\n1. Listar todos\n");
    printf("2. Listar um\n");
    printf("3. Incluir\n");
    printf("4. Alterar\n");
    printf("5. Excluir\n");
    printf("6. Voltar\n");
    printf(": ");
    scanf("%d", &opt);

    return opt;
}

int subMenuRelatorios()
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
    setlocale(LC_ALL,"Portuguese");
    int opcao;
    do
    {
        opcao = menu();
        switch (opcao)
        {
            case 1:
                //Submenu de Faxineiros
                printf("1. Submenu de Faxineiros");
                break;
            case 2:
                //Submenu de Clientes
                printf("2. Submenu de Clientes");
                break;
            case 3:
                //Submenu de Serviços
                printf("3. Submenu de Serviços");
                break;
            case 4:
                //Submenu Relatórios
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