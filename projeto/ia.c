#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "damas.h"

void jogarIA(Jogo *jogo, Jogador *jogadorIA, Jogador *jogadorOponente) {
    typedef struct {
        int linhaOrigem, colunaOrigem;
        int linhaDestino, colunaDestino;
        int dama;
        int captura;
        int pontuacao;
    } Movimento;

    Movimento movimentosValidos[200];
    int numMovimentos = 0;

    for (int linha = 0; linha < MAX; linha++) {
        for (int coluna = 0; coluna < MAX; coluna++) {
            TipoPeca peca = jogo->tabuleiro[linha][coluna].peca;
            if (!pecaPreta(peca)) continue;

            int ehDama = pecaDama(peca);
            int direcoes[4][2] = { {1, -1}, {1, 1}, {-1, -1}, {-1, 1} };

            for (int d = 0; d < (ehDama ? 4 : 2); d++) {
                int dirLinha = direcoes[d][0];
                int dirColuna = direcoes[d][1];
                
                int novaLinha = linha + dirLinha;
                int novaColuna = coluna + dirColuna;

                if (posicaoValida(novaLinha, novaColuna) && jogo->tabuleiro[novaLinha][novaColuna].peca == VAZIO) {
                    movimentosValidos[numMovimentos++] = (Movimento){linha, coluna, novaLinha, novaColuna, ehDama, 0, 1};
                }

                int captLinha = linha + 2 * dirLinha;
                int captColuna = coluna + 2 * dirColuna;
                int meioLinha = linha + dirLinha;
                int meioColuna = coluna + dirColuna;

                if (posicaoValida(captLinha, captColuna) &&
                    jogo->tabuleiro[captLinha][captColuna].peca == VAZIO &&
                    pecaBranca(jogo->tabuleiro[meioLinha][meioColuna].peca)) {
                    
                    Movimento m = {linha, coluna, captLinha, captColuna, ehDama, 1, 0};
                    movimentosValidos[numMovimentos++] = m;
                }
            }
        }
    }

    if (numMovimentos == 0) {
        printf("%s (IA) nao tem movimentos validos e perde o jogo!\n", jogadorIA->nome);
        salvarHistorico(jogo);
        exit(0);
    }

    for (int i = 0; i < numMovimentos; i++) {
        Movimento *movimento = &movimentosValidos[i];
        if (movimento->captura)
            movimento->pontuacao += 100;
        if (movimento->dama)
            movimento->pontuacao += 50;

        int vulnerabilidade = 0;
        for (int d = 0; d < 4; d++) {
            int dl = (d == 0 || d == 1) ? 1 : -1;
            int dc = (d == 0 || d == 2) ? 1 : -1;

            int linhaOponente = movimento->linhaDestino + dl;
            int colunaOponente = movimento->colunaDestino + dc;
            int linhaApos = movimento->linhaDestino + 2 * dl;
            int colunaApos = movimento->colunaDestino + 2 * dc;

            if (posicaoValida(linhaOponente, colunaOponente) && posicaoValida(linhaApos, colunaApos)) {
                TipoPeca pecaOponente = jogo->tabuleiro[linhaOponente][colunaOponente].peca;
                if (pecaBranca(pecaOponente) && jogo->tabuleiro[linhaApos][colunaApos].peca == VAZIO) {
                    vulnerabilidade++;
                }
            }
        }
        if (vulnerabilidade > 0)
            movimento->pontuacao -= vulnerabilidade * 30;
    }

    int melhorPontuacao = -9999;
    for (int i = 0; i < numMovimentos; i++) {
        if (movimentosValidos[i].pontuacao > melhorPontuacao) {
            melhorPontuacao = movimentosValidos[i].pontuacao;
        }
    }

    Movimento melhoresMovimentos[200];
    int countMelhores = 0;
    for (int i = 0; i < numMovimentos; i++) {
        if (movimentosValidos[i].pontuacao == melhorPontuacao) {
            melhoresMovimentos[countMelhores++] = movimentosValidos[i];
        }
    }

    Movimento selecionado = melhoresMovimentos[rand() % countMelhores];

    moverPeca(jogo, selecionado.linhaOrigem, selecionado.colunaOrigem,
              selecionado.linhaDestino, selecionado.colunaDestino,
              jogadorOponente, jogadorIA);

    printf("%s (IA) moveu de (%d, %d) para (%d, %d)\n", jogadorIA->nome,
           selecionado.linhaOrigem, selecionado.colunaOrigem,
           selecionado.linhaDestino, selecionado.colunaDestino);

    if (selecionado.captura) {
        int novaLinha = selecionado.linhaDestino;
        int novaColuna = selecionado.colunaDestino;
        int capturaExtra = 1;

        while (capturaExtra) {
            capturaExtra = 0;
            for (int d = 0; d < 4; d++) {
                int dl = (d == 0 || d == 1) ? 1 : -1;
                int dc = (d == 0 || d == 2) ? 1 : -1;

                int meioLinha = novaLinha + dl;
                int meioColuna = novaColuna + dc;
                int destLinha = novaLinha + 2 * dl;
                int destColuna = novaColuna + 2 * dc;

                if (posicaoValida(destLinha, destColuna) &&
                    pecaBranca(jogo->tabuleiro[meioLinha][meioColuna].peca) &&
                    jogo->tabuleiro[destLinha][destColuna].peca == VAZIO) {

                    moverPeca(jogo, novaLinha, novaColuna, destLinha, destColuna,
                              jogadorOponente, jogadorIA);
                    printf("\nIA fez captura encadeada para %c%d\n",
                           'A' + destColuna, destLinha + 1);
                    novaLinha = destLinha;
                    novaColuna = destColuna;
                    capturaExtra = 1;
                    break;
                }
            }
        }
    }
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
        salvarHistorico(jogo); return 1;
    }
    else if (!temBrancas) {
        printf("\n%s (Pretas) venceu o jogo!\n", jogadorPretas->nome);
        salvarHistorico(jogo); return 1;
    }
    return 0;
}