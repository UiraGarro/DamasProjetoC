#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 8


typedef enum {
    VAZIO,
    PECA_BRANCA,
    PECA_PRETA,
    DAMA_BRANCA,
    DAMA_PRETA
} TipoPeca;

typedef struct {
    TipoPeca peca;
} Casa;

typedef struct {
    Casa tabuleiro[MAX][MAX];
    int turno; // 0 = brancas, 1 = pretas
} Jogo;

typedef struct {
    char nome[50];
    int pontuacao;
} Jogador;


int posicaoValida(int linha, int coluna) {
    return linha >= 0 && linha < MAX && coluna >= 0 && coluna < MAX;
}

int pecaBranca(TipoPeca peca) {
    return peca == PECA_BRANCA || peca == DAMA_BRANCA;
}

int pecaPreta(TipoPeca peca) {
    return peca == PECA_PRETA || peca == DAMA_PRETA;
}

int pecaDama(TipoPeca peca) {
    return peca == DAMA_BRANCA || peca == DAMA_PRETA;
}

Jogo inicializarJogo() {
    Jogo jogo;
    jogo.turno = 0; // brancas começam

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
        printf("❌ Nenhuma peça nessa posição!\n");
        return 0;
    }

    if (jogo->turno == 0 && !pecaBranca(pecaSelecionada)) {
        printf("❌ É o turno das brancas!\n");
        return 0;
    }
    if (jogo->turno == 1 && !pecaPreta(pecaSelecionada)) {
        printf("❌ É o turno das pretas!\n");
        return 0;
    }

    int deslocamentoLinha = linhaDestino - linhaOrigem;
    int deslocamentoColuna = colunaDestino - colunaOrigem;

    if (!posicaoValida(linhaDestino, colunaDestino)) {
        printf("❌ Movimento fora do tabuleiro!\n");
        return 0;
    }

    if (jogo->tabuleiro[linhaDestino][colunaDestino].peca != VAZIO) {
        printf("❌ Casa destino ocupada!\n");
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
                printf("❌ Não há peça inimiga para capturar!\n");
                return 0;
            }
        } else {
            printf("❌ Movimento inválido!\n");
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
                        printf("❌ Dama só pode capturar uma peça por vez!\n");
                        return 0;
                    }
                    pecaIntermediaria = jogo->tabuleiro[linha][coluna].peca;
                    if ((pecaBranca(pecaSelecionada) && pecaBranca(pecaIntermediaria)) ||
                        (pecaPreta(pecaSelecionada) && pecaPreta(pecaIntermediaria))) {
                        printf("❌ Há uma peça da mesma cor no caminho!\n");
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
            printf("❌ Movimento inválido da dama!\n");
            return 0;
        }
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

int main() { 
    Jogo jogo = inicializarJogo(); 
    Jogador jogadorBrancas, jogadorPretas;

    printf("Digite o nome do jogador das Brancas: ");
    scanf("%49s", jogadorBrancas.nome);
    jogadorBrancas.pontuacao = 0;

    printf("Digite o nome do jogador das Pretas: ");
    scanf("%49s", jogadorPretas.nome);
    jogadorPretas.pontuacao = 0;

    char posicaoOrigem[3], posicaoDestino[3]; 
    
    while (1) { exibirTabuleiro(jogo, jogadorBrancas, jogadorPretas); 
    printf("Turno de %s (%s)\n", 
        jogo.turno == 0 ? jogadorBrancas.nome : 
    jogadorPretas.nome, 
        jogo.turno == 0 ? "O Brancas" : "X Pretas"); 

    printf("Mover de (ex: D3): "); 
    scanf("%2s", posicaoOrigem); 
    printf("Para (ex: E4): "); 
    scanf("%2s", posicaoDestino); 

    int colunaOrigem = toupper(posicaoOrigem[0]) - 'A'; 
    int linhaOrigem = posicaoOrigem[1] - '1'; 
    int colunaDestino = toupper(posicaoDestino[0]) - 'A'; 
    int linhaDestino = posicaoDestino[1] - '1'; 
    moverPeca(&jogo, linhaOrigem, colunaOrigem, linhaDestino, 
    colunaDestino, 
        &jogadorBrancas, &jogadorPretas); 
    } 
}

// Coisas a fazer
// verificar se alguem ganhou
//"IA" modo de movimentos random pros sem amigos