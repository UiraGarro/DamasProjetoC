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
    int turno; // 0 pra branca, 1 pra preta
} Jogo;

typedef struct {
    char nome[50];
    int pontuacao;
} Jogador;

Jogo inicializarJogo() {
    Jogo jogo;
    jogo.turno = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            jogo.tabuleiro[i][j].linha = i;
            jogo.tabuleiro[i][j].coluna = j;
            if ((i + j) % 2 == 1) {
                if (i < 3) {
                    jogo.tabuleiro[i][j].peca = PRETA;
                } else if (i > 4) {
                    jogo.tabuleiro[i][j].peca = BRANCA;
                } else {
                    jogo.tabuleiro[i][j].peca = VAZIO;
                }
            } else {
                jogo.tabuleiro[i][j].peca = VAZIO;
            }
        }
    }
    return jogo;
}

void exibirTabuleiro(Jogo jogo, Jogador jogadorBrancas, Jogador jogadorPretas) {
    int invertido = jogo.turno; // bota 1 pra testar o outro turno
    printf("\n");

    if (!invertido)
        printf("        %s (● Pretas) — Pontos: %d\n\n", jogadorPretas.nome, jogadorPretas.pontuacao);
    else
        printf("        %s (○ Brancas) — Pontos: %d\n\n", jogadorBrancas.nome, jogadorBrancas.pontuacao);

    if (!invertido)
        printf("    A   B   C   D   E   F   G   H\n");
    else
        printf("    H   G   F   E   D   C   B   A\n");

    printf("  ---------------------------------\n");

    for (int i = 0; i < MAX; i++) {
        int linha = invertido ? (MAX - 1 - i) : i;
        printf("%d |", invertido ? (MAX - i) : (i + 1));

        for (int j = 0; j < MAX; j++) {
            int coluna = invertido ? (MAX - 1 - j) : j;

            switch (jogo.tabuleiro[linha][coluna].peca) {
                case BRANCA: printf(" ● "); break;
                case PRETA: printf(" ○ "); break;
                case DAMA_BRANCA: printf(" ♕ "); break;
                case DAMA_PRETA: printf(" ♛ "); break;
                default: printf("   "); break;
            }
            printf("|");
        }

        printf(" %d\n  ---------------------------------\n", invertido ? (MAX - i) : (i + 1));
    }

    if (!invertido)
        printf("    A   B   C   D   E   F   G   H\n\n");
    else
        printf("    H   G   F   E   D   C   B   A\n\n");

    if (!invertido)
        printf("        %s (○ Brancas) — Pontos: %d\n", jogadorBrancas.nome, jogadorBrancas.pontuacao);
    else
        printf("        %s (● Pretas) — Pontos: %d\n", jogadorPretas.nome, jogadorPretas.pontuacao);
}

int main() {
    Jogo jogo = inicializarJogo();

    exibirTabuleiro(jogo, (Jogador){"Jogador 1", 0}, (Jogador){"Jogador 2", 0});
}

   