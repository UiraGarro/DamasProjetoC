#include "damas.h"

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