#ifndef QUIZ_H
#define QUIZ_H

#include "data.h"

int carregar_perguntas(Pergunta quiz[], const char* nome_arquivo);
void carregar_recorde(Jogador *recordista);
void salvar_recorde(int pontuacao_atual);
void iniciar_quiz(Pergunta quiz[], int total_perguntas);

#endif
