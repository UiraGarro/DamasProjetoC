#include <stdio.h>
#include <stdlib.h>

#define MAX 8

typedef enum {
    VAZIO, BRANCA, PRETA, DAMA_BRANCA, DAMA_PRETA
} Peca;

typedef struct
{
    int linha;
    int coluna;
    Peca peca;
} Celula;

typedef struct
{
    Celula tabuleiro[MAX][MAX];
    int turno; // 0 para branca, 1 para preta
} Jogo;

typedef struct {
    char nome[50];
    int pontuacao;
} Jogador;