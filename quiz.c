#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "utils.h"
#include "quiz.h"

int carregar_perguntas(Pergunta quiz[], const char* nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "r");
    if (f == NULL) {
        printf("ERRO CRITICO: Nao achei o arquivo '%s'.\n", nome_arquivo);
        return 0;
    }

    char buffer[200];
    int count = 0;

    while (count < MAX_PERGUNTAS && fgets(buffer, sizeof(buffer), f)) {
        remover_nova_linha(buffer);
        strcpy(quiz[count].enunciado, buffer);

        for (int i = 0; i < 4; i++) {
            if (fgets(buffer, sizeof(buffer), f)) {
                remover_nova_linha(buffer);
                strcpy(quiz[count].opcoes[i], buffer);
            }
        }

        if (fgets(buffer, sizeof(buffer), f)) {
            quiz[count].resposta_correta = atoi(buffer);
        }

        count++;
    }
    fclose(f);
    printf("Carregadas %d perguntas com sucesso!\n", count);
    return count;
}

void carregar_recorde(Jogador *recordista) {
    FILE *f = fopen(ARQUIVO_RECORDE, "r");
    if (f == NULL) {
        strcpy(recordista->nome, "Ninguem");
        recordista->pontuacao = 0;
    } else {
        char buffer[50];
        if (fgets(buffer, sizeof(buffer), f)) {
            remover_nova_linha(buffer);
            strcpy(recordista->nome, buffer);
        }
        if (fgets(buffer, sizeof(buffer), f)) {
            recordista->pontuacao = atoi(buffer);
        }
        fclose(f);
    }
}

void salvar_recorde(int pontuacao_atual) {
    char nome[50];
    printf("Digite seu nome para o recorde: ");
    limpar_buffer();
    fgets(nome, sizeof(nome), stdin);
    remover_nova_linha(nome);

    FILE *f = fopen(ARQUIVO_RECORDE, "w");
    if (f == NULL) {
        printf("Erro ao salvar recorde!\n");
        return;
    }
    fprintf(f, "%s\n%d", nome, pontuacao_atual);
    fclose(f);
    printf("Recorde salvo com sucesso!\n");
}

void iniciar_quiz(Pergunta quiz[], int total_perguntas) {
    if (total_perguntas == 0) {
        printf("Nao ha perguntas carregadas.\n");
        return;
    }

    int pontos = 0;
    int resp_usuario;

    printf("\n=== INICIANDO O QUIZ ===\n");

    for (int i = 0; i < total_perguntas; i++) {
        printf("\nQuestao %d: %s\n", i + 1, quiz[i].enunciado);
        for (int j = 0; j < 4; j++) {
            printf("%d) %s\n", j + 1, quiz[i].opcoes[j]);
        }

        printf("Sua resposta: ");
        scanf("%d", &resp_usuario);

        if (resp_usuario == quiz[i].resposta_correta) {
            printf("CORRETO!\n");
            pontos += 10;
        } else {
            printf("ERRADO! A resposta correta era %d.\n", quiz[i].resposta_correta);
        }
    }

    printf("\n--- FIM DE JOGO ---\n");
    printf("Sua pontuacao final: %d\n", pontos);

    Jogador recordista;
    carregar_recorde(&recordista);

    if (pontos > recordista.pontuacao) {
        printf("VOCE BATEU O RECORDE!\n");
        salvar_recorde(pontos);
    } else {
        printf("Voce nao bateu o recorde de %d pontos.\n", recordista.pontuacao);
    }
}
