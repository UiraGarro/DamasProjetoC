#ifndef DAMAS_H
#define DAMAS_H

#define MAX 8
#define MAX_JOGADAS 200

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
    char jogador[50];
    char origem[3];
    char destino[3];
    char peca[10];
} Jogada;

typedef struct {
    char nome[50];
    int pontuacao;
} Jogador;

typedef struct {
    Casa tabuleiro[MAX][MAX];
    int turno;
    Jogada historico[MAX_JOGADAS];
    int numJogadas;
} Jogo;

// Function declarations
Jogo inicializarJogo(void);
void exibirTabuleiro(Jogo *jogo, Jogador *jogadorBrancas, Jogador *jogadorPretas);
int moverPeca(Jogo *jogo, int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, Jogador *jogadorBrancas, Jogador *jogadorPretas);
void salvarHistorico(Jogo *jogo);
int verificarVencedor(Jogo *jogo, Jogador *jogadorBrancas, Jogador *jogadorPretas);
void jogarIA(Jogo *jogo, Jogador *jogadorIA, Jogador *jogadorOponente);
int posicaoValida(int linha, int coluna);
int pecaBranca(TipoPeca peca);
int pecaPreta(TipoPeca peca);
int pecaDama(TipoPeca peca);

#endif