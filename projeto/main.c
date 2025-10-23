#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "damas.h"

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