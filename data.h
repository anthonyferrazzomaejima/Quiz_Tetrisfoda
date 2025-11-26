#ifndef DATA_H
#define DATA_H

#define MAX_PERGUNTAS 20
#define ARQUIVO_PERGUNTAS "perguntas.txt"
#define ARQUIVO_RECORDE "recorde.txt"

typedef struct {
    char enunciado[200];
    char opcoes[4][100];
    int resposta_correta;
} Pergunta;

typedef struct {
    char nome[50];
    int pontuacao;
} Jogador;

#endif
