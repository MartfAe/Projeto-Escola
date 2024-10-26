﻿#include <stdio.h>
#include <locale.h>
#include "escola.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    // Inicialização de listas
    pessoas aluno[Max_Alunos] = {0}; // Inicializa o array com zeros
    pessoas professor[Max_Professores] = {0}; // Inicializa o array com zeros
    materias disciplinas[Max_Disciplinas] = {0}; // Inicializa o array com zeros
    


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
                            //inserir função de atualizar pessoa (aluno)
                            break;
                        }
                        case 3: { //Excluir aluno
                            //inserir função de excluir pessoa (aluno)
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
                            //inserir função de atualizar pessoa (professor)
                            break;
                        }
                        case 3: { //Excluir professor
                            //inserir função de excluir pessoa (professor)
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
                            //inserir função de atualizar disciplina
                            break;
                        }
                        case 3: { //Excluir disciplina
                            //inserir função de excluir disciplina
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
                            //inserir função de matricular aluno em disciplina
                            break;
                        }
                        case 2: { //Desmatricular aluno de uma disciplina
                            //inserir função de desmatricular aluno disciplina
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
                        case 3: { // listagem de alunos por ordem alfabética
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
                        case 6: {
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
