
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>
#include <ctype.h>

#define Max_Alunos 3
#define Max_Professores 3
#define Max_Disciplinas 3
#define Max_Alunos_Disciplinas 100
#define Max_Matricula 12

# define prefixo_Professor "2024117"
#define prefixo_Aluno "2024106"

// Definição das structs
typedef struct {
    int dia, mes, ano;
} data;

typedef struct {
    char matricula[Max_Matricula];
    char sexo, nome[50], cpf[15];
    data aniversario;
} pessoas;

typedef struct {
    char nome[50], codigo[8], professor[50];
    int semestre;
    pessoas aluno[Max_Alunos_Disciplinas];
    int numAlunos;
} materias;

//Definindo as funções 
void cadastrarPessoa(pessoas *cadastro, int maxPessoas, char tipoPessoa);
void cadastrarDisciplina(materias *disciplinas, int max_Disciplinas, pessoas *professores, int max_Professores);
void gerarMatriculaAluno(char matricula[]);
void gerarMatriculaProfessor(char matricula[]);

void gerarMatriculaAluno(char matricula[]);
void gerarMatriculaProfessor(char matricula[]);
int validarNome(char nome[]);
int validarCPF(char cpf[]);
int validarSexo(char sexo);
int validarData(data aniversario);
int validarMatricula(int matricula);
int validarCodigoDisciplina(char codigo[]);
int validarSemestre(int semestre);
void toUpperString(char *str);


int contadorAluno = 0; // Contador de alunos
int contadorProfessor = 0; // Contador de professores

// Implementação de separador
void separadorTexto(void) {
    printf("\n");
    for (int i = 0; i < 70; i++) {
        printf("-");
    }
}

// Implementação de cabeçalho
void cabecalho(char nomeMenu[20]) {
    printf("Cabecalho chamado para: %s\n", nomeMenu); // Debug
    separadorTexto();
    printf("\n");
    if (strcmp(nomeMenu, "principal") == 0) {
        printf("\t\t\t\tProjeto Escola");
    } else if (strcmp(nomeMenu, "professor") == 0) {
        printf("\t\t\t\tProfessor");
    } else if (strcmp(nomeMenu, "aluno") == 0) {
        printf("\t\t\t\tAluno");
    } else if (strcmp(nomeMenu, "disciplina") == 0) {
        printf("\t\t\t\tDisciplina");
    } else if (strcmp(nomeMenu, "ajuste") == 0) {
        printf("\t\t\t\tAjuste de Matrículas");
    } else if (strcmp(nomeMenu, "relatorio") == 0) {
        printf("\t\t\t\tRelatórios");
    }
    separadorTexto();
    printf("\n");
}

// Implementação de menus
int menu(char tipoMenu[20]) {
    int opcao;
    if (strcmp(tipoMenu, "principal") == 0) { //Menu principal
        printf("0 - Sair\n");
        printf("1 - Aluno\n");
        printf("2 - Professor\n");
        printf("3 - Disciplina\n");
        printf("4 - Ajuste de matrículas em disciplinas\n");
        printf("5 - Relatório\n");
        // Adicione mais opções se necessário
        printf("\n");
    } else if (strcmp(tipoMenu, "cadastro") == 0) { //Menu alunos, professor e disciplina
        printf("0 - Voltar\n");
        printf("1 - Cadastrar\n");
        printf("2 - Atualizar\n");
        printf("3 - Excluir\n");
        // Adicione mais opções se necessário
        printf("\n");
    } else if (strcmp(tipoMenu, "ajuste") == 0) { //Menu ajuste de matrícula
        printf("0 - Voltar\n");
        printf("1 - Matricular aluno em uma disciplina\n");
        printf("2 - Desmatricular aluno de uma disciplina\n");
        // Adicione mais opções se necessário
        printf("\n");
    } else if (strcmp(tipoMenu, "relatorio") == 0) { //Menu relatórios
        printf("0 - Voltar\n");
        printf("\nRelatórios de Alunos:\n\n");
        printf("%-46s %-30s\n","1 - Sem ordenação","2 - Por sexo");
        printf("%-45s %-30s\n","3 - Em ordem alfabética","4 - Em ordem de nascimento");
        printf("%-45s\n","5 - Matriculados em menos de 3 disciplinas");
        printf("\nRelatórios de Professores:\n\n");
        printf("%-46s %-30s\n","6 - Sem ordenação","7 - Por sexo");
        printf("%-45s %-30s\n","8 - Em ordem alfabética","9 - Em ordem de nascimento");
        printf("\nRelatórios de Disciplinas:\n\n");
        printf("%-44s %-30s\n","10 - Disciplinas cadastradas","12 - Dados de disciplina");
        printf("%-43s\n","11 - Disciplinas com mais de 40 vagas");
        printf("\nDemais Relatórios:\n\n");
        printf("%-45s %-30s\n","13 - Aniversariantes do mês","14 - Todas as pessoas cadastradas");
        // Adicione mais opções se necessário
        printf("\n");
    }
    
    scanf("%d", &opcao);
    return opcao;
}

// Implementação dos Getters e Setters

pessoas getProfessor(pessoas professores[], int index) {
    return professores[index];
}


void setProfessor(pessoas professores[], int index, pessoas novoProfessor) {
    if (strlen(novoProfessor.nome) > 0 && strlen(novoProfessor.cpf) == 14) {
        professores[index] = novoProfessor;
    } else {
        printf("Erro: Nome ou CPF inválido.\n");
    }
}

pessoas getAluno(pessoas alunos[], int index) {
    return alunos[index];
}

void setAluno(pessoas alunos[], int index, pessoas novoAluno) {
    if (strlen(novoAluno.nome) > 0 && strlen(novoAluno.cpf) == 14) {
        alunos[index] = novoAluno;
    } else {
        printf("Erro: Nome ou CPF inválido.\n");
    }
}

materias getDisciplina(materias disciplinas[], int index) {
    return disciplinas[index];
}

void setDisciplina(materias disciplinas[], int index, materias novaDisciplina) {
    if (strlen(novaDisciplina.nome) > 0 && strlen(novaDisciplina.codigo) <= 8) {
        disciplinas[index] = novaDisciplina;
        printf("Disciplina atualizada com sucesso!\n");
    } else {
        printf("Erro: Nome ou Código da disciplina inválido.\n");
    }
}

//Função para gerar a matrícula para aluno
void gerarMatriculaAluno(char matricula[]) {
    if (contadorAluno >= 9999) {
        printf("Erro: Limite de matrículas atingido para alunos.\n");
        return;
    } 
    sprintf(matricula, "%s%04d", prefixo_Aluno, contadorAluno + 1);
    contadorAluno++;
}

//Função para gerar a matrícula para professor
void gerarMatriculaProfessor(char matricula[]) {
    if (contadorProfessor >= 9999) {
        printf("Erro: Limite de matrículas atingido para professores.\n");
        return;
    }
    
    sprintf(matricula, "%s%04d", prefixo_Professor, contadorProfessor + 1);
    contadorProfessor++;
}

//FUnção cadastrar pessoa
void cadastrarPessoa(pessoas *cadastro, int maxPessoas, char tipoPessoa) {
    printf("Entrou na função cadastrarPessoa\n"); // Debug
    int i;

    for (i = 0; i < maxPessoas; i++) {
        if (cadastro[i].matricula[0] == '\0') {  // Verifica se o campo matrícula está vazio
            pessoas novoCadastro; 

            if (tipoPessoa == 1) {
                printf("Cadastro de Aluno:\n\n");
                gerarMatriculaAluno(novoCadastro.matricula);
                printf("Matrícula gerada: %s\n", novoCadastro.matricula);
            } else if (tipoPessoa == 2) {
                printf("Cadastro de Professor:\n");
                gerarMatriculaProfessor(novoCadastro.matricula);
                printf("Matrícula gerada: %s\n", novoCadastro.matricula);
            }

            // Loop para o nome
            do {
                printf("Informe o nome:\n");
                getchar();
                fgets(novoCadastro.nome, sizeof(novoCadastro.nome), stdin);
                novoCadastro.nome[strcspn(novoCadastro.nome, "\n")] = '\0';  
                toUpperString(novoCadastro.nome); 
            } while (!validarNome(novoCadastro.nome));

            // Loop para o CPF
            do {
                printf("Informe o CPF no seguinte formato xxx.xxx.xxx-xx:\n");
                fgets(novoCadastro.cpf, sizeof(novoCadastro.cpf), stdin);
                novoCadastro.cpf[strcspn(novoCadastro.cpf, "\n")] = '\0'; 
            } while (!validarCPF(novoCadastro.cpf));

            // Loop para o sexo
            do {
                printf("Informe o sexo (M/F):\n");
                scanf(" %c", &novoCadastro.sexo);
                getchar(); 
            } while (!validarSexo(novoCadastro.sexo));

            // Loop para a data de nascimento
            do {
                printf("Informe a data de nascimento separada por um espaço (dd mm aaaa):\n");
                if (scanf("%d %d %d", &novoCadastro.aniversario.dia, &novoCadastro.aniversario.mes, &novoCadastro.aniversario.ano) != 3) {
                    printf("Formato inválido. Tente novamente.\n");
                    while (getchar() != '\n');  // Limpa o buffer
                }
            } while (!validarData(novoCadastro.aniversario));

            // Usa o setter apropriado para atualizar o cadastro
            if (tipoPessoa == 1) {
                setAluno(cadastro, i, novoCadastro); 
                printf("Aluno cadastrado com sucesso!\n");
            } else if (tipoPessoa == 2) {
                setProfessor(cadastro, i, novoCadastro); 
                printf("Professor cadastrado com sucesso!\n");
            }
            break;
        }

    // Se o loop terminar sem encontrar uma posição vazia, exibe mensagem
    if (i == maxPessoas) {
        if (tipoPessoa == 1) {
            printf("Não há espaço para cadastrar mais alunos.\n");
        } else if (tipoPessoa == 2) {
            printf("Não há espaço para cadastrar mais professores.\n");
        }
    }
}
}
//Função para validar nome
  int validarNome(char nome[]) {
    printf("Entrou na função validarNome.\n"); // Debug

    // Verifica se o nome foi inserido
    if (strlen(nome) == 0) {
        printf("O nome não pode ser vazio. Tente novamente.\n");
        return 0;
    }

    // Converte o nome para letras maiúsculas e verifica se contém números
    for (int i = 0; i < strlen(nome); i++) {
        if (isdigit(nome[i])) {  // Verifica se é um dígito
            printf("Erro: O nome não deve conter números.\n");
            return 0;
        }
        nome[i] = toupper(nome[i]);  // Converte para maiúsculo
    }

    // Verifica se o nome tem pelo menos 3 caracteres após a conversão
    if (strlen(nome) < 3) {
        printf("Erro: O nome deve ter pelo menos 3 caracteres.\n");
        return 0;
    }

    return 1; // Nome é válido
}

// Função validar CPF
int validarCPF(char cpf[]) {
    printf("Entrou na função validarCPF.\n"); // debug
    if (strlen(cpf) != 14) {
        printf("Erro: O CPF deve ser informado com 14 dígitos.\n");
        return 0;
    }
    return 1;
}

// Função Validar Sexo
int validarSexo(char sexo) {
    // Converte o caractere para maiúsculo
    sexo = toupper(sexo);

    // Verifica se o sexo é 'M' ou 'F'
    if (sexo != 'M' && sexo != 'F') {
        printf("Sexo inválido. Use 'M' para sexo masculino ou 'F' para o sexo feminino.\n");
        return 0;
    }
    return 1;
}

// Função validar data
int validarData(data aniversario) {
    printf("Entrou na função validarData.\n"); // debug
    if (aniversario.dia < 1 || aniversario.dia > 31 || aniversario.mes < 1 || aniversario.mes > 12 || aniversario.ano < 1900) {
        printf("Formato de data inválido. Tente novamente.\n");
        return 0;
    }
    return 1;
}

// Implementação da função de cadastrar disciplina
void cadastrarDisciplina(materias *disciplinas, int max_Disciplinas, pessoas *professores, int max_Professores) {
    printf("Entrou na função cadastro de disciplina.\n"); // Debug
    int i;

    for (i = 0; i < max_Disciplinas; i++) {
        if (disciplinas[i].codigo[0] == '\0') { // Verifica se a disciplina não foi cadastrada
            materias novaDisciplina;

            // Validação do nome da disciplina
            do {
                printf("Informe o nome da disciplina:\n");
                getchar();
                fgets(novaDisciplina.nome, sizeof(novaDisciplina.nome), stdin);
                novaDisciplina.nome[strcspn(novaDisciplina.nome, "\n")] = '\0';

                if (strlen(novaDisciplina.nome) < 3) {
                    printf("O nome da disciplina deve ter no mínimo 3 caracteres.\n");
                } else {
                    toUpperString(novaDisciplina.nome); // Converte o nome para maiúsculas
                }
            } while (strlen(novaDisciplina.nome) < 3);

            // Validação do código da disciplina
            do {
                printf("Informe o código da disciplina (máx 8 caracteres):\n");
                fgets(novaDisciplina.codigo, sizeof(novaDisciplina.codigo), stdin);
                novaDisciplina.codigo[strcspn(novaDisciplina.codigo, "\n")] = '\0';

                if (strlen(novaDisciplina.codigo) > 8 || strlen(novaDisciplina.codigo) == 0) {
                    printf("O código deve ter entre 1 e 8 caracteres.\n");
                } else {
                    toUpperString(novaDisciplina.codigo); // Converte o código para maiúsculas
                }
            } while (strlen(novaDisciplina.codigo) > 8 || strlen(novaDisciplina.codigo) == 0);

            // Validação do semestre
            do {
                printf("Informe o semestre da disciplina:\n");
                if (scanf("%d", &novaDisciplina.semestre) != 1 || novaDisciplina.semestre <= 0) {
                    printf("Semestre inválido. Informe um número positivo.\n");
                    while (getchar() != '\n');  // Limpa o buffer de entrada
                } else {
                    getchar();  // Limpa o buffer após ler o semestre
                    break;      // Sai do loop se o semestre for válido
                }
            } while (1);

            // Seleção do professor
            int encontrou = 0; // Reset da flag antes de buscar o professor

            if (max_Professores <= 0) {
                printf("Não há professores cadastrados.\n");
                return;
            }
            char matriculaProf[15]; // Tamanho ajustado para incluir o '\0'
            do {
                printf("Informe a matrícula do professor:\n");
                fgets(matriculaProf, sizeof(matriculaProf), stdin);
                matriculaProf[strcspn(matriculaProf, "\n")] = '\0'; // Remove o newline

                // Verifica se a matrícula inserida corresponde a um professor cadastrado
                for (int j = 0; j < max_Professores; j++) {
                    if (strcmp(professores[j].matricula, matriculaProf) == 0) {
                        strcpy(novaDisciplina.professor, professores[j].nome);
                        encontrou = 1; // Professor encontrado
                        printf("Professor encontrado: %s - %s\n", professores[j].matricula, professores[j].nome);
                        break; // Sai do loop se o professor foi encontrado
                    }
                }

                if (!encontrou) {
                    printf("Professor não encontrado. Tente novamente.\n");
                }
            } while (!encontrou);

            // Finalizando cadastro da disciplina
            novaDisciplina.numAlunos = 0;
            setDisciplina(disciplinas, i, novaDisciplina); // Supondo que essa função esteja definida corretamente
            printf("Disciplina cadastrada com sucesso!\n");
            return;  // Sai da função após o cadastro
        }
    }
    
    // Mensagem caso não haja espaço
    if (i == max_Disciplinas) {
        printf("Não há espaço para cadastrar mais disciplinas.\n");
    }
}

//Função para adicionar aluno em uma disciplina
void adicionarAlunoDisciplina(materias *disciplina, int maxDisciplinas, pessoas *alunos, int maxAlunos, char matriculaAluno[]) {
    int alunoEncontrado = -1;

    // Buscar o aluno pela matrícula
    for (int i = 0; i < maxAlunos; i++) {
        if (strcmp(getAluno(alunos, i).matricula, matriculaAluno) == 0) {
            alunoEncontrado = i;
            break;
        }
    }

    if (alunoEncontrado == -1) {
        printf("Erro: Aluno com matrícula %s não encontrado.\n", matriculaAluno);
        return;
    }

    // Verificar limite de alunos na disciplina
    if (disciplina->numAlunos >= Max_Alunos_Disciplinas) {
        printf("Erro: A disciplina já atingiu o limite de alunos.\n");
        return;
    }

    // Adicionar aluno na disciplina
    setAluno(disciplina->aluno, disciplina->numAlunos, getAluno(alunos, alunoEncontrado)); // Usando o setter para adicionar o aluno
    disciplina->numAlunos++; // Atualiza o número de alunos
    printf("Aluno %s adicionado com sucesso à disciplina %s.\n", getAluno(alunos, alunoEncontrado).nome, disciplina->nome);
}

// Função para desmatricular um aluno de uma disciplina
void desmatricularAlunoDisciplina(materias disciplinas[], int numDisciplinas) {
    char matriculaAluno[Max_Matricula];
    char codigoDisciplina[8];

    printf("Informe o código da disciplina:\n");
    fgets(codigoDisciplina, sizeof(codigoDisciplina), stdin);
    codigoDisciplina[strcspn(codigoDisciplina, "\n")] = '\0';

    // Busca a disciplina pelo código
    int disciplinaEncontrada = -1;
    for (int i = 0; i < numDisciplinas; i++) {
        if (strcmp(getDisciplina(disciplinas, i).codigo, codigoDisciplina) == 0) {
            disciplinaEncontrada = i;
            break;
        }
    }

    if (disciplinaEncontrada == -1) {
        printf("Erro: Disciplina com código %s não encontrada.\n", codigoDisciplina);
        return;
    }

    printf("Informe a matrícula do aluno a ser desmatriculado:\n");
    fgets(matriculaAluno, sizeof(matriculaAluno), stdin);
    matriculaAluno[strcspn(matriculaAluno, "\n")] = '\0';

    int alunoEncontrado = -1;

    // Buscar o aluno pela matrícula
    for (int i = 0; i < getDisciplina(disciplinas, disciplinaEncontrada).numAlunos; i++) {
        if (strcmp(getAluno(disciplinas[disciplinaEncontrada].aluno, i).matricula, matriculaAluno) == 0) {
            alunoEncontrado = i;
            break;
        }
    }

    if (alunoEncontrado == -1) {
        printf("Erro: Aluno com matrícula %s não encontrado na disciplina %s.\n", matriculaAluno, getDisciplina(disciplinas, disciplinaEncontrada).nome);
        return;
    }

    // Solicitar confirmação
    char confirmacao;
    printf("Você tem certeza que deseja desmatricular o aluno %s? (S/N): ", getAluno(disciplinas[disciplinaEncontrada].aluno, alunoEncontrado).nome);
    scanf(" %c", &confirmacao); // Espaço antes de %c para consumir o caractere de nova linha anterior

    // Permitir que S e N sejam lidos tanto em maiúsculo quanto em minúsculo
    if (confirmacao == 'S' || confirmacao == 's') {
        // Remover aluno da disciplina
        for (int i = alunoEncontrado; i < getDisciplina(disciplinas, disciplinaEncontrada).numAlunos - 1; i++) {
            setAluno(disciplinas[disciplinaEncontrada].aluno, i, getAluno(disciplinas[disciplinaEncontrada].aluno, i + 1)); // Usar o setter para mover alunos
        }
        disciplinas[disciplinaEncontrada].numAlunos--;
        printf("Aluno desmatriculado com sucesso!\n");
    } else {
        printf("Desmatriculação cancelada.\n");
    }
}

//Atualização de Disciplina
void atualizarDisciplina(materias *cadastro, int maxDisciplinas, pessoas *professores, int maxProfessores) {
    char codigo[8];
    printf("Informe o código da disciplina a ser atualizada:\n");
    scanf("%s", codigo);

    for (int i = 0; i < maxDisciplinas; i++) {
        // Verifica se o código corresponde à disciplina cadastrada
        if (strcmp(getDisciplina(cadastro, i).codigo, codigo) == 0) {
            char novoNome[50];
            char matriculaProfessor[Max_Matricula];
            int novoSemestre;

            //Atualiza o nome da disciplina
            printf("Digite um novo nome para a disciplina (ou pressione Enter para manter):\n");
            getchar(); // Limpa o buffer do teclado
            fgets(novoNome, sizeof(novoNome), stdin);
            novoNome[strcspn(novoNome, "\n")] = '\0'; // Remove a nova linha

            if (strlen(novoNome) > 0) {
                toUpperString(novoNome); // Chama a função para converter o nome para maiúsculas
                strcpy(cadastro[i].nome, novoNome);
                printf("Nome da disciplina atualizado para: %s\n", cadastro[i].nome);
            } else {
                // Se o usuário não digitou nada, mantém o nome atual
                printf("Nome da disciplina mantido como: %s\n", cadastro[i].nome);
            }

            // Solicita a matrícula do novo professor
            printf("Digite a matrícula do novo professor (ou pressione Enter para manter):\n");
            fgets(matriculaProfessor, sizeof(matriculaProfessor), stdin);
            matriculaProfessor[strcspn(matriculaProfessor, "\n")] = '\0'; // Remove a nova linha

            // Verifica se a matrícula não está vazia
            if (strlen(matriculaProfessor) > 0) {
                // Busca o professor pela matrícula
                int professorEncontrado = 0; // Flag para verificar se o professor foi encontrado
                for (int j = 0; j < maxProfessores; j++) {
                    if (strcmp(getProfessor(professores, j).matricula, matriculaProfessor) == 0) {
                        // Se o professor foi encontrado, atualiza o nome do professor na disciplina
                        strcpy(cadastro[i].professor, getProfessor(professores, j).nome);
                        professorEncontrado = 1; // Marca que o professor foi encontrado
                        break; // Sai do loop, pois já encontramos o professor
                    }
                }
                if (!professorEncontrado) {
                    printf("Professor com matrícula %s não encontrado.\n", matriculaProfessor);
                    return; // Sai da função se o professor não for encontrado
                }
            }

            // Atualiza o semestre
            printf("Digite um novo semestre (ou pressione Enter para manter):\n");
            if (scanf("%d", &novoSemestre) == 1) {
                cadastro[i].semestre = novoSemestre; // Atualiza o semestre
            }

            printf("Disciplina atualizada com sucesso!\n");
            return;
        }
    }
    printf("Código da disciplina não encontrado.\n");
}

//Atualização de pessoa
void atualizarPessoa(pessoas *cadastro, int maxPessoas, int tipoPessoa) {
    char matricula[Max_Matricula];
    printf("Informe a matrícula da pessoa a ser atualizada:\n");
    scanf("%s", matricula);

    for (int i = 0; i < maxPessoas; i++) {
        // Verifica se a matrícula corresponde à que está cadastrada
        if ((tipoPessoa == 1 && strncmp(getAluno(cadastro, i).matricula, prefixo_Aluno, strlen(prefixo_Aluno)) == 0) ||
            (tipoPessoa == 2 && strncmp(getProfessor(cadastro, i).matricula, prefixo_Professor, strlen(prefixo_Professor)) == 0)) {
            if (strcmp(getAluno(cadastro, i).matricula, matricula) == 0 || strcmp(getProfessor(cadastro, i).matricula, matricula) == 0) {
                char novoNome[50];  // Tamanho do nome conforme definido na struct
                char novoCPF[15];   // Tamanho do CPF conforme definido na struct
                char novoSexo;

                // Atualiza o nome
                printf("Digite um novo nome (ou pressione Enter para manter):\n");
                getchar(); // Limpa o buffer do teclado
                fgets(novoNome, sizeof(novoNome), stdin);
                novoNome[strcspn(novoNome, "\n")] = '\0'; // Remove a nova linha

                // Se o usuário não digitou nada, mantém o nome atual
                if (strlen(novoNome) > 0) {
                    if (validarNome(novoNome)) {
                        if (tipoPessoa == 1) {
                            pessoas alunoAtual = getAluno(cadastro, i);
                            strcpy(alunoAtual.nome, novoNome);
                            setAluno(cadastro, i, alunoAtual);
                        } else {
                            pessoas professorAtual = getProfessor(cadastro, i);
                            strcpy(professorAtual.nome, novoNome);
                            setProfessor(cadastro, i, professorAtual);
                        }
                    }
                }

                // Atualiza o CPF
                printf("Digite um novo CPF (ou pressione Enter para manter):\n");
                fgets(novoCPF, sizeof(novoCPF), stdin);
                novoCPF[strcspn(novoCPF, "\n")] = '\0'; // Remove a nova linha

                // Se o usuário não digitou nada, mantém o CPF atual
                if (strlen(novoCPF) > 0) {
                    if (validarCPF(novoCPF)) {
                        if (tipoPessoa == 1) {
                            pessoas alunoAtual = getAluno(cadastro, i);
                            strcpy(alunoAtual.cpf, novoCPF);
                            setAluno(cadastro, i, alunoAtual);
                        } else {
                            pessoas professorAtual = getProfessor(cadastro, i);
                            strcpy(professorAtual.cpf, novoCPF);
                            setProfessor(cadastro, i, professorAtual);
                        }
                    }
                }

                // Atualiza o sexo
                printf("Digite um novo sexo (M/F ou pressione Enter para manter):\n");
                scanf(" %c", &novoSexo); // Lê um único caractere

                // Verifica se o usuário digitou 'M' ou 'F' ou pressionou Enter
                if (novoSexo == 'M' || novoSexo == 'F') {
                    if (tipoPessoa == 1) {
                        pessoas alunoAtual = getAluno(cadastro, i);
                        alunoAtual.sexo = novoSexo;
                        setAluno(cadastro, i, alunoAtual);
                    } else {
                        pessoas professorAtual = getProfessor(cadastro, i);
                        professorAtual.sexo = novoSexo;
                        setProfessor(cadastro, i, professorAtual);
                    }
                }

                printf("Dados atualizados com sucesso!\n");
                return;
            }
        }
    }
    printf("Matrícula não encontrada.\n");
}

// Função para excluir pessoa
void excluirPessoa(pessoas *cadastro, int *maxPessoas, int tipoPessoa) {
    char matricula[Max_Matricula];
    printf("Informe a matrícula da pessoa a ser excluída:\n");
    scanf("%s", matricula);

    for (int i = 0; i < *maxPessoas; i++) {
        // Verifica se a matrícula corresponde à que está cadastrada
        if ((tipoPessoa == 1 && strncmp(cadastro[i].matricula, prefixo_Aluno, strlen(prefixo_Aluno)) == 0) ||
            (tipoPessoa == 2 && strncmp(cadastro[i].matricula, prefixo_Professor, strlen(prefixo_Professor)) == 0)) {
            if (strcmp(cadastro[i].matricula, matricula) == 0) {
                // Encontrou a matrícula, solicita confirmação
                char confirmacao;
                printf("Você tem certeza que deseja excluir a pessoa %s? (s/n): ", cadastro[i].nome);
                scanf(" %c", &confirmacao); // Lê a confirmação

                if (confirmacao == 's' || confirmacao == 'S') {
                    // Excluindo a pessoa
                    for (int j = i; j < *maxPessoas - 1; j++) {
                        cadastro[j] = cadastro[j + 1]; // Move os registros para preencher a lacuna
                    }
                    (*maxPessoas)--; // Diminui o contador de pessoas
                    printf("Pessoa excluída com sucesso!\n");
                } else {
                    printf("Exclusão cancelada.\n");
                }
                return;
            }
        }
    }
    printf("Matrícula não encontrada.\n");
}

//Exclusão de discplina
void excluirDisciplina(materias *disciplinas, int max_Disciplinas) {
    printf("Entrou na função excluir disciplina.\n"); // Debug
    char codigo[9]; 
    int encontrada = 0;

    // Solicita o código da disciplina a ser excluída
    printf("Informe o código da disciplina que deseja excluir:\n");
    fgets(codigo, sizeof(codigo), stdin);
    codigo[strcspn(codigo, "\n")] = '\0'; 

    // Converte o código inserido para maiúsculas
    toUpperString(codigo);

    // Procura a disciplina pelo código
    for (int i = 0; i < max_Disciplinas; i++) {
        if (strcmp(disciplinas[i].codigo, codigo) == 0) {
            encontrada = 1;

            // Verifica se há alunos matriculados
            if (disciplinas[i].numAlunos > 0) {
                printf("Não é possível excluir a disciplina, pois existem %d aluno(s) matriculado(s).\n", disciplinas[i].numAlunos);
            } else {
                // Solicita confirmação antes de excluir
                char confirmacao;
                printf("Você tem certeza que deseja excluir a disciplina %s (Cód.: %s)? (S/N)\n", disciplinas[i].nome, disciplinas[i].codigo);
                scanf(" %c", &confirmacao);
                getchar();

                if (confirmacao == 'S' || confirmacao == 's') {
                    // Exclui a disciplina, limpando os dados
                    disciplinas[i].codigo[0] = '\0'; // Marca a disciplina como não cadastrada
                    disciplinas[i].nome[0] = '\0';   // Limpa o nome da disciplina
                    disciplinas[i].semestre = 0;     // Reseta o semestre
                    disciplinas[i].numAlunos = 0;    // Reseta o número de alunos
                    printf("Disciplina excluída com sucesso!\n");
                } else {
                    printf("Exclusão da disciplina cancelada.\n");
                }
            }
            break; 
        }
    }

    if (!encontrada) {
        printf("Disciplina não encontrada.\n");
    }
}

//Função para transformar em maiusculo
void toUpperString(char *str) {
    while (*str) {
        *str = toupper(*str);  // Converte cada caractere para maiúscula
        str++;
    }
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    // Inicialização de listas
    pessoas aluno[Max_Alunos] = {0}; // Inicializa o array com zeros
    pessoas professor[Max_Professores] = {0}; // Inicializa o array com zeros
    materias disciplinas[Max_Disciplinas] = {0}; // Inicializa o array com zeros
    
    int maxAlunos = Max_Alunos;
    int maxProfessores = Max_Professores;


    bool encerrar = false;
    bool voltar = false;

    while (!encerrar) {
        cabecalho("principal");
        int opcao = menu("principal");
        printf("Você escolheu a opção: %d\n", opcao); // Debug
        switch (opcao) {
            case 0: { //Encerramento do programa
                encerrar = true;
                break;
            }
            case 1: { //Menu Aluno
                voltar = false;
                while (!voltar) {
                    system("clear");
                    cabecalho("aluno");
                    opcao = menu("cadastro");
                    system("clear");
                    printf("Você escolheu a opção de cadastro: %d\n", opcao); // Debug
                    switch (opcao) {
                        case 0: { //Volta para o menu principal
                            voltar = true;
                            break;
                        }
                        case 1: { //Cadastro de novo aluno
                            printf("Chamando cadastrarPessoa...\n"); // Debug
                            cadastrarPessoa(aluno, Max_Alunos, 1);
                            break;
                        }
                        case 2: { //Atualizar dados de aluno
                            atualizarPessoa(aluno, Max_Alunos, 1);
                            break;
                        }
                        case 3: { //Excluir aluno
                            excluirPessoa(aluno, &maxAlunos, 1);
                            break;
                        }
                        // Outros casos se forem adicionados ao sistema...
                    }
                }
                break;
            }         
            case 2: { //Menu professor
                voltar = false;
                while (!voltar) {
                    system("clear");
                    cabecalho("professor");
                    opcao = menu("cadastro");
                    system("clear");
                    printf("Você escolheu a opção de cadastro: %d\n", opcao); // Debug
                    switch (opcao) {
                        case 0: { //Volta para o menu principal
                            voltar = true;
                            break;
                        }
                        case 1: { //Cadastro de novo professor
                            printf("Chamando cadastrarPessoa...\n"); // Debug
                            cadastrarPessoa(professor, Max_Professores, 2);
                            break;
                        }
                        case 2: { //Atualizar dados de professor
                            atualizarPessoa(professor, Max_Professores, 2);
                            break;
                        }
                        case 3: { //Excluir professor
                            excluirPessoa(professor, &maxProfessores, 2);
                            break;
                        }
                        // Outros casos se forem adicionados ao menu professor...
                    }
                }
                break;
            }
            case 3: { //Menu Disciplina
                voltar = false;
                while (!voltar) {
                    system("clear");
                    cabecalho("disciplina");
                    opcao = menu("cadastro");
                    system("clear");
                    printf("Você escolheu a opção de cadastro: %d\n", opcao); // Debug
                    switch (opcao) {
                        case 0: { //Volta para o menu principal
                            voltar = true;
                            break;
                        }
                        case 1: { //Cadastro de nova disciplina
                            printf("Chamando cadastrarDisciplina...\n"); // Debug
                            cadastrarDisciplina(disciplinas, Max_Disciplinas, professor, Max_Professores);
                            break;
                        }
                        case 2: { //Atualizar dados de disciplina
                            atualizarDisciplina(disciplinas, Max_Disciplinas, professor, Max_Professores);
                            break;
                        }
                        case 3: { //Excluir disciplina
                            excluirDisciplina(disciplinas, Max_Disciplinas);
                            break;
                        }
                        // Outros casos se forem adicionados ao menu disciplina...
                    }
                }
                break;
            }
            case 4: { //Menu Ajuste de matrículas em disciplinas
                voltar = false;
                while (!voltar) {
                    system("clear");
                    cabecalho("ajuste");
                    opcao = menu("ajuste");
                    system("clear");
                    printf("Você escolheu a opção de ajuste: %d\n", opcao); // Debug
                    switch (opcao) {
                        case 0: { //Volta para o menu principal
                            voltar = true;
                            break;
                        }
                        case 1: { //Matricular aluno em uma disciplina
                            char matriculaAluno[15]; 
                            printf("Informe a matrícula do aluno que deseja matricular:\n");
                            fgets(matriculaAluno, sizeof(matriculaAluno), stdin);
                            matriculaAluno[strcspn(matriculaAluno, "\n")] = '\0';
                            if (disciplinas[0].numAlunos < Max_Alunos_Disciplinas) { // Verifica se existe espaço na disciplina
                                adicionarAlunoDisciplina(&disciplinas[0], Max_Disciplinas, aluno, Max_Alunos, matriculaAluno);
                            } else {
                                printf("Não há espaço na disciplina para adicionar mais alunos.\n");
                            }
                            break;
                            
                        }
                        case 2: { //Desmatricular aluno de uma disciplina
                            desmatricularAlunoDisciplina(disciplinas, Max_Disciplinas);
                            break;
                        }
                        // Outros casos se forem adicionados ao menu ajuste de disciplina...
                    }
                }
                break;
            }
            case 5: { //Menu Relatórios
                voltar = false;
                while (!voltar) {
                    system("clear");
                    cabecalho("relatorio");
                    opcao = menu("relatorio");
                    system("clear");
                    printf("Você escolheu a opção de relatório: %d\n", opcao); // Debug
                    switch (opcao) {
                        case 0: { //Volta para o menu principal
                            voltar = true;
                            break;
                        }
                        case 1: { //listagem de alunos sem ordenação do vetor
                            //inserir função para listagem de pessoas(alunos) sem ordenação do vetor
                            break;
                        }
                        case 2: { //listagem de alunos por sexo
                            //inserir função para listagem de pessoas(alunos) por sexo informado
                            break;
                        }
                        case 3: { //listagem de alunos por ordem alfabética
                            //inserir função para listagem de pessoas(alunos) com ordenação do vetor em ordem alfabética
                            break;
                        }
                        case 4: { // listagem de alunos por ordem de nascimento
                            //inserir função para listagem de pessoas(alunos) com ordenação do vetor em ordem de nascimento
                            break;
                        }
                        case 5: { // listagem de alunos matriculados em menos de 3 disciplinas
                            //inserir função para listagem de alunos matriculados em menos de 3 disciplinas
                            break;
                        }
                        case 6: { //listagem de professor sem ordenação do vetor
                            //inserir função para listagem de pessoas(professor) sem ordenação do vetor
                            break;
                        }
                        case 7: { //listagem de professor por sexo
                            //inserir função para listagem de pessoas(professor) por sexo informado
                            break;
                        }
                        case 8: { //listagem de professor por ordem alfabética
                            //inserir função para listagem de pessoas(professor) com ordenação do vetor em ordem alfabética
                            break;
                        }
                        case 9: { // listagem de professor por ordem de nascimento
                            //inserir função para listagem de pessoas(professor) com ordenação do vetor em ordem de nascimento
                            break;
                        }
                        case 10: { //listagem de disciplinas cadastradas
                            //inserir função para listagem de todas as disciplinas cadastradas (nomes das disciplinas)
                            break;
                        }
                        case 11: { //listagem de disciplinas com mais de 40 vagas
                            //inserir função para listagem de disciplinas com mais de 40 vagas e pofessor correspondente (nome da disciplina e nome do professor)
                            break;
                        }
                        case 12: { //listagem dos dados de uma disciplina
                            //inserir função para listagem de todos os dados de uma disciplina selecionada pelo usuário
                            break;
                        }
                        case 13: { //listagem dos aniversariantes do mês
                            //inserir função para listagem de todos as pessoas que fazem aniversário no mês corrente e suas respectivas datas de aniversário (dia/mês)
                            break;
                        }
                        case 14: { //listagem de todas as pessoas cadastradas
                            //inserir função para listagem de pessoas(todas)
                            break;
                        }
                        // Outros casos se forem adicionados ao menu ajuste de relatórios...
                    }
                }
                break;
            }
            // Outros casos se forem adicionados ao menu principal do sistema...
        }
    }
}
