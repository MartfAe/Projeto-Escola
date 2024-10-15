      /*Projeto Escola do semestre 24.2 da disciplina INF029.
      Desenvolvido por: Ana Emília Lobo, Marcus Vinícius da Fonseca, Roberto Silva. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#define Max_Alunos 3
#define Max_Professores 3
#define Max_Disciplinas 3


// Definição das structs
typedef struct {
    int dia, mes, ano;
} data;

typedef struct {
    int matricula;
    char sexo, nome[50], cpf[15];
    data aniversario;
} pessoas;

typedef struct {
    char nome[50], codigo[8], professor[50];
    int semestre;
} materias;

// Inicialização das variáveis globais
pessoas aluno[Max_Alunos], professor[Max_Professores];
materias disciplinas[Max_Disciplinas];


// Funções
int listar(int tipoLista) {
    // Com base no tipo informado, chama as funções correspondentes de listagem

    switch (tipoLista) {
        case 1: {
            // apresentar opções para listagem de alunos
            break;
        }
        case 2: {
            // apresentar opções para listagem de professores
            break;
        }
        case 3: {
            // apresentar opções para listagem de disciplinas
            break;
        }
    }
    return 0;
}

//Função para o cadastro de alunos ou professores
void cadastrarPessoa(pessoas *cadastro, int maxPessoas, char tipoPessoa)  {
    int i;
    for (i = 0; i < maxPessoas; i++) {
        if (cadastro[i].matricula == 0) {  // Verifica se o campo matrícula está vazio
            if (tipoPessoa == '1') {
                printf("Cadastro de Aluno:\n\n");
            } else if (tipoPessoa == '2') {
                printf("Cadastro de Professor:\n");
            }

            printf("Informe o nome:\n");
            scanf(" %[^\n]", cadastro[i].nome);

            printf("Informe a matrícula:\n");
            scanf("%d", &cadastro[i].matricula);

            printf("Informe o CPF:\n");
            scanf("%s", cadastro[i].cpf);

            printf("Informe o sexo (M/F):\n");
            scanf(" %c", &cadastro[i].sexo);  // Corrige o uso do scanf para ler char corretamente

            printf("Informe a data de nascimento separada por um espaço (dd mm aaaa):\n");
            scanf("%d %d %d", &cadastro[i].aniversario.dia, &cadastro[i].aniversario.mes, &cadastro[i].aniversario.ano);

            if (tipoPessoa == '1') {
                printf("Aluno cadastrado com sucesso!\n");
            } else if (tipoPessoa == '2') {
                printf("Professor cadastrado com sucesso!\n");
            }

            break;  // Sai do loop após o cadastro
        }
    }

    // Se o loop terminar sem encontrar uma posição vazia, exibe mensagem
    if (i == maxPessoas) {
        if (tipoPessoa == '1') {
            printf("Não há espaço para cadastrar mais alunos.\n");
        } else if (tipoPessoa == '2') {
            printf("Não há espaço para cadastrar mais professores.\n");
        }
    }
}

int cadastrar(int tipoCadastrar) {
    // Fazer cadastro conforme tipo informado

    switch (tipoCadastrar) {
        case 1: {
            cadastrarPessoa(aluno, Max_Alunos, '1');
            break;
        }
        case 2: {
            cadastrarPessoa(professor, Max_Professores, '2');
            break;
        }
        case 3: {
            // Cadastrar disciplina
            break;
        }
    }
    return 0;
}