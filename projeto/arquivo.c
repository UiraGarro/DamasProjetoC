#include <stdio.h>
#include "damas.h"

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
    printf("\n Histórico salvo em 'historico.txt'.\n");
}