#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "damas.h"

Jogo inicializarJogo() {
    Jogo jogo;
    jogo.turno = 0; // brancas começam
    jogo.numJogadas = 0;

    for (int linha = 0; linha < MAX; linha++) {
        for (int coluna = 0; coluna < MAX; coluna++) {
            jogo.tabuleiro[linha][coluna].peca = VAZIO;
        }
    }

    for (int linha = 0; linha < 3; linha++) {
        for (int coluna = 0; coluna < MAX; coluna++) {
            if ((linha + coluna) % 2 == 1)
                jogo.tabuleiro[linha][coluna].peca = PECA_PRETA;
        }
    }
    for (int linha = 5; linha < MAX; linha++) {
        for (int coluna = 0; coluna < MAX; coluna++) {
            if ((linha + coluna) % 2 == 1)
                jogo.tabuleiro[linha][coluna].peca = PECA_BRANCA;
        }
    }

    return jogo;
}

void exibirTabuleiro(Jogo jogo, Jogador jogadorBrancas, Jogador jogadorPretas) {
    int invertido = jogo.turno; // 0 = brancas, 1 = pretas
    printf("\n===============================================================\n");

    if (!invertido)
        printf(" Cima: %s (X Pretas) - Pontos: %d\n", jogadorPretas.nome, jogadorPretas.pontuacao);
    else
        printf(" Cima: %s (O Brancas) - Pontos: %d\n", jogadorBrancas.nome, jogadorBrancas.pontuacao);

    printf("===============================================================\n\n");

    if (!invertido)
        printf("     A   B   C   D   E   F   G   H\n");
    else
        printf("     H   G   F   E   D   C   B   A\n");

    printf("   +---+---+---+---+---+---+---+---+\n");

    for (int i = 0; i < MAX; i++) {
        int linha = invertido ? (MAX - 1 - i) : i;
        printf(" %d |", invertido ? (MAX - i) : (i + 1));

        for (int j = 0; j < MAX; j++) {
            int coluna = invertido ? (MAX - 1 - j) : j;

            TipoPeca peca = jogo.tabuleiro[linha][coluna].peca;
            const char* simbolo = " ";

            switch (peca) {
                case PECA_BRANCA: simbolo = "O"; break;
                case PECA_PRETA:  simbolo = "X"; break;
                case DAMA_BRANCA: simbolo = "D"; break;
                case DAMA_PRETA:  simbolo = "Q"; break;
                default: simbolo = " "; break;
            }

            printf(" %s |", simbolo);
        }

        printf(" %d\n", invertido ? (MAX - i) : (i + 1));
        printf("   +---+---+---+---+---+---+---+---+\n");
    }

    if (!invertido)
        printf("     A   B   C   D   E   F   G   H\n\n");
    else
        printf("     H   G   F   E   D   C   B   A\n\n");

    if (!invertido)
        printf(" Baixo: %s (O Brancas) - Pontos: %d\n", jogadorBrancas.nome, jogadorBrancas.pontuacao);
    else
        printf(" Baixo: %s (X Pretas) - Pontos: %d\n", jogadorPretas.nome, jogadorPretas.pontuacao);

    printf("===============================================================\n");
}

int moverPeca(Jogo *jogo, int linhaOrigem, int colunaOrigem, 
              int linhaDestino, int colunaDestino,
              Jogador *jogadorBrancas, Jogador *jogadorPretas) {
    
    TipoPeca pecaSelecionada = jogo->tabuleiro[linhaOrigem][colunaOrigem].peca;

    if (pecaSelecionada == VAZIO) {
        printf("Nenhuma peça nessa posição!\n");
        return 0;
    }

    if (jogo->turno == 0 && !pecaBranca(pecaSelecionada)) {
        printf("É o turno das brancas!\n");
        return 0;
    }
    if (jogo->turno == 1 && !pecaPreta(pecaSelecionada)) {
        printf("É o turno das pretas!\n");
        return 0;
    }

    int deslocamentoLinha = linhaDestino - linhaOrigem;
    int deslocamentoColuna = colunaDestino - colunaOrigem;

    if (!posicaoValida(linhaDestino, colunaDestino)) {
        printf("Movimento fora do tabuleiro!\n");
        return 0;
    }

    if (jogo->tabuleiro[linhaDestino][colunaDestino].peca != VAZIO) {
        printf("Casa destino ocupada!\n");
        return 0;
    }

    // Movimento para peças normais
    if (!pecaDama(pecaSelecionada)) {
        int direcaoMovimento = pecaBranca(pecaSelecionada) ? -1 : 1;

        if (abs(deslocamentoLinha) == 1 && abs(deslocamentoColuna) == 1 && deslocamentoLinha == direcaoMovimento) {
            jogo->tabuleiro[linhaDestino][colunaDestino].peca = pecaSelecionada;
            jogo->tabuleiro[linhaOrigem][colunaOrigem].peca = VAZIO;
        }
        else if (abs(deslocamentoLinha) == 2 && abs(deslocamentoColuna) == 2) {
            int linhaIntermediaria = linhaOrigem + deslocamentoLinha / 2;
            int colunaIntermediaria = colunaOrigem + deslocamentoColuna / 2;
            TipoPeca pecaCapturada = jogo->tabuleiro[linhaIntermediaria][colunaIntermediaria].peca;

            if ((pecaBranca(pecaSelecionada) && pecaPreta(pecaCapturada)) ||
                (pecaPreta(pecaSelecionada) && pecaBranca(pecaCapturada))) {
                
                jogo->tabuleiro[linhaIntermediaria][colunaIntermediaria].peca = VAZIO;
                jogo->tabuleiro[linhaDestino][colunaDestino].peca = pecaSelecionada;
                jogo->tabuleiro[linhaOrigem][colunaOrigem].peca = VAZIO;

                if (pecaBranca(pecaSelecionada)) jogadorBrancas->pontuacao++;
                else jogadorPretas->pontuacao++;
            } else {
                printf("Não há peça inimiga para capturar!\n");
                return 0;
            }
        } else {
            printf("Movimento inválido!\n");
            return 0;
        }
    }

    // Movimento para dama
    else {
        if (abs(deslocamentoLinha) == abs(deslocamentoColuna)) {
            int passoLinha = (deslocamentoLinha > 0) ? 1 : -1;
            int passoColuna = (deslocamentoColuna > 0) ? 1 : -1;
            int linha = linhaOrigem + passoLinha, coluna = colunaOrigem + passoColuna;
            int capturou = 0;
            TipoPeca pecaIntermediaria;

            while (linha != linhaDestino && coluna != colunaDestino) {
                if (jogo->tabuleiro[linha][coluna].peca != VAZIO) {
                    if (capturou) {
                        printf("Dama só pode capturar uma peça por vez!\n");
                        return 0;
                    }
                    pecaIntermediaria = jogo->tabuleiro[linha][coluna].peca;
                    if ((pecaBranca(pecaSelecionada) && pecaBranca(pecaIntermediaria)) ||
                        (pecaPreta(pecaSelecionada) && pecaPreta(pecaIntermediaria))) {
                        printf("Há uma peça da mesma cor no caminho!\n");
                        return 0;
                    }
                    capturou = 1;
                }
                linha += passoLinha;
                coluna += passoColuna;
            }

            jogo->tabuleiro[linhaDestino][colunaDestino].peca = pecaSelecionada;
            jogo->tabuleiro[linhaOrigem][colunaOrigem].peca = VAZIO;

            if (capturou) {
                jogo->tabuleiro[linhaOrigem + passoLinha][colunaOrigem + passoColuna].peca = VAZIO;
                if (pecaBranca(pecaSelecionada)) jogadorBrancas->pontuacao++;
                else jogadorPretas->pontuacao++;
            }
        } else {
            printf("Movimento inválido da dama!\n");
            return 0;
        }
    }

        // Registrar jogada no histórico
    if (jogo->numJogadas < MAX_JOGADAS) {
        Jogada *j = &jogo->historico[jogo->numJogadas];
        strcpy(j->jogador, jogo->turno == 0 ? jogadorBrancas->nome : jogadorPretas->nome);
        sprintf(j->origem, "%c%d", 'A' + colunaOrigem, linhaOrigem + 1);
        sprintf(j->destino, "%c%d", 'A' + colunaDestino, linhaDestino + 1);

        switch (pecaSelecionada) {
            case PECA_BRANCA: strcpy(j->peca, "Peça Branca"); break;
            case PECA_PRETA: strcpy(j->peca, "Peça Preta"); break;
            case DAMA_BRANCA: strcpy(j->peca, "Dama Branca"); break;
            case DAMA_PRETA: strcpy(j->peca, "Dama Preta"); break;
            default: strcpy(j->peca, "Desconhecida"); break;
        }

        jogo->numJogadas++;
    }

    jogo->turno = !jogo->turno;

    
    for (int coluna = 0; coluna < MAX; coluna++) {
        if (jogo->tabuleiro[0][coluna].peca == PECA_BRANCA)
            jogo->tabuleiro[0][coluna].peca = DAMA_BRANCA;
        if (jogo->tabuleiro[MAX-1][coluna].peca == PECA_PRETA)
            jogo->tabuleiro[MAX-1][coluna].peca = DAMA_PRETA;
    }

    return 1;
}