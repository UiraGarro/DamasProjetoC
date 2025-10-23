#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void salvarHistorico(Jogo *jogo) {
    FILE *arquivo = fopen("historico.txt", "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de histórico!\n");
        return;
    }

    fprintf(arquivo, "===== HISTÓRICO DE JOGADAS =====\n\n");
    for (int i = 0; i < jogo->numJogadas; i++) {
        Jogada j = jogo->historico[i];
        fprintf(arquivo, "%2d. %s moveu %s de %s para %s\n",
                i + 1, j.jogador, j.peca, j.origem, j.destino);
    }

    fclose(arquivo);
    printf("\n📜 Histórico salvo em 'historico.txt'.\n");
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
        printf("\n🏆 %s (Brancas) venceu o jogo!\n", jogadorBrancas->nome);
        salvarHistorico(jogo);
        return 1;
    }
    else if (!temBrancas) {
        printf("\n🏆 %s (Pretas) venceu o jogo!\n", jogadorPretas->nome);
        salvarHistorico(jogo);
        return 1;
    }

    return 0;
}

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

int main() {
    Jogo jogo;
    Jogador jogadorBrancas, jogadorPretas;
    char posicaoOrigem[3], posicaoDestino[3];
    char jogarNovamente;

    printf("Digite o nome do jogador das Brancas: ");
    scanf("%49s", jogadorBrancas.nome);
    jogadorBrancas.pontuacao = 0;

    int modoSolo = 0;
    printf("\nDeseja jogar contra o computador? (S/N): ");
    char resposta;
    scanf(" %c", &resposta);

    if (toupper(resposta) == 'N') {
        modoSolo = 0;
        printf("Digite o nome do jogador das Pretas: ");
        scanf("%49s", jogadorPretas.nome);
        jogadorPretas.pontuacao = 0;
    } else if (toupper(resposta) == 'S'){
        modoSolo = (toupper(resposta) == 'S');
        strcpy(jogadorPretas.nome, "Computador");
        jogadorPretas.pontuacao = 0;
    } else {
        printf("Resposta inválida. Encerrando o jogo.\n");
        return 1;
    }
    do {
        jogo = inicializarJogo();

        while (1) {
            if (jogo.turno == 0 || !modoSolo) {
                exibirTabuleiro(jogo, jogadorBrancas, jogadorPretas);
        
                printf("Turno de %s (%s)\n",
                       jogo.turno == 0 ? jogadorBrancas.nome : jogadorPretas.nome,
                       jogo.turno == 0 ? "O Brancas" : "X Pretas");
        
                printf("Mover de (ex: D3 ou S para sair): ");
                scanf("%2s", posicaoOrigem);
        
                if (toupper(posicaoOrigem[0]) == 'S') {
                    salvarHistorico(&jogo);
                    printf("\nDeseja jogar novamente? (S/N): ");
                    scanf(" %c", &jogarNovamente);
                    jogarNovamente = toupper(jogarNovamente);
                    break;
                }
        
                printf("Para (ex: E4): ");
                scanf("%2s", posicaoDestino);
        
                int colunaOrigem = toupper(posicaoOrigem[0]) - 'A';
                int linhaOrigem = posicaoOrigem[1] - '1';
                int colunaDestino = toupper(posicaoDestino[0]) - 'A';
                int linhaDestino = posicaoDestino[1] - '1';
        
                moverPeca(&jogo, linhaOrigem, colunaOrigem, linhaDestino,
                          colunaDestino, &jogadorBrancas, &jogadorPretas);
        
            } else {
                jogarIA(&jogo, &jogadorPretas, &jogadorBrancas);
            }
        
            if (verificarVencedor(&jogo, &jogadorBrancas, &jogadorPretas)) {
                printf("\nDeseja jogar novamente? (S/N): ");
                scanf(" %c", &jogarNovamente);
                jogarNovamente = toupper(jogarNovamente);
                break;
            }
        }

    } while (jogarNovamente == 'S');

    printf("\n Obrigado por jogar!\n");
    return 0;
}