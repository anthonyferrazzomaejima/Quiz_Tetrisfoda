#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "data.h"
#include "utils.h"
#include "quiz.h"

int main() {
    setlocale(LC_ALL, "Portuguese");

    Pergunta quiz[MAX_PERGUNTAS];
    int total_perguntas = 0;
    int opcao;

    // Carrega as perguntas ao iniciar
    total_perguntas = carregar_perguntas(quiz, ARQUIVO_PERGUNTAS);

    do {
        printf("\n=== MENU DO QUIZ ===\n");
        printf("1. Jogar\n");
        printf("2. Ver Recorde Atual\n");
        printf("3. Recarregar Perguntas do Arquivo\n");
        printf("4. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                iniciar_quiz(quiz, total_perguntas);
                break;
            case 2: {
                Jogador rec;
                carregar_recorde(&rec);
                printf("\n>>> RECORDE ATUAL <<<\n");
                printf("Nome: %s\n", rec.nome);
                printf("Pontos: %d\n", rec.pontuacao);
                break;
            }
            case 3:
                total_perguntas = carregar_perguntas(quiz, ARQUIVO_PERGUNTAS);
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 4);

    return 0;
}
