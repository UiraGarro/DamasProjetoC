#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "damas.h"

void jogarIA(Jogo *jogo, Jogador *jogadorIA, Jogador *jogadorOponente) {
    typedef struct {
        int linhaOrigem, colunaOrigem;
        int linhaDestino, colunaDestino;
    } Movimento;

    Movimento movimentosValidos[200];
    int numMovimentos = 0;

    for (int linha = 0; linha < MAX; linha++) {
        for (int coluna = 0; coluna < MAX; coluna++) {
            TipoPeca peca = jogo->tabuleiro[linha][coluna].peca;

            if (!pecaPreta(peca)) continue;

            int direcoes[4][2] = {
                {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
            };

            for (int d = 0; d < 4; d++) {
                int dl = direcoes[d][0];
                int dc = direcoes[d][1];

                int novaLinha = linha + dl;
                int novaColuna = coluna + dc;

                if (posicaoValida(novaLinha, novaColuna) &&
                    jogo->tabuleiro[novaLinha][novaColuna].peca == VAZIO &&
                    (!pecaDama(peca) ? dl == 1 : 1)) {
                    movimentosValidos[numMovimentos++] = (Movimento){linha, coluna, novaLinha, novaColuna};
                }

                int captLinha = linha + 2 * dl;
                int captColuna = coluna + 2 * dc;
                int meioLinha = linha + dl;
                int meioColuna = coluna + dc;

                if (posicaoValida(captLinha, captColuna) &&
                    jogo->tabuleiro[captLinha][captColuna].peca == VAZIO &&
                    ((pecaBranca(jogo->tabuleiro[meioLinha][meioColuna].peca)) &&
                     (pecaPreta(peca)))) {
                    movimentosValidos[numMovimentos++] = (Movimento){linha, coluna, captLinha, captColuna};
                }
            }
        }
    }

    if (numMovimentos == 0) {
        printf("\n IA não pode mover!\n");
        return;
    }

    srand(time(NULL));
    Movimento escolhido = movimentosValidos[rand() % numMovimentos];

    moverPeca(jogo,
              escolhido.linhaOrigem, escolhido.colunaOrigem,
              escolhido.linhaDestino, escolhido.colunaDestino,
              jogadorOponente, jogadorIA);

    printf("\n IA moveu de %c%d para %c%d\n",
           'A' + escolhido.colunaOrigem, escolhido.linhaOrigem + 1,
           'A' + escolhido.colunaDestino, escolhido.linhaDestino + 1);
}

int verificarVencedor(Jogo *jogo, Jogador *jogadorBrancas, Jogador *jogadorPretas) {
    int temBrancas = 0, temPretas = 0;

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            TipoPeca peca = jogo->tabuleiro[i][j].peca;

            if (pecaBranca(peca)) temBrancas = 1;
            if (pecaPreta(peca)) temPretas = 1;
        }
    }

    if (!temPretas) {
        printf("\n%s (Brancas) venceu o jogo!\n", jogadorBrancas->nome);
        salvarHistorico(jogo);
        return 1;
    }
    else if (!temBrancas) {
        printf("\n%s (Pretas) venceu o jogo!\n", jogadorPretas->nome);
        salvarHistorico(jogo);
        return 1;
    }

    return 0;
}