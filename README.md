# ♟️ Jogo de Damas em C

Um jogo de **Damas (Checkers)** desenvolvido em **C**, com suporte para dois jogadores ou contra IA.
Possui visualização do tabuleiro, pontuação, captura de peças, promoção para dama e histórico de jogadas.

## 🎯 Funcionalidades

* Tabuleiro **8x8** com visualização dinâmica
* Peças pretas (**X**) e brancas (**O**)
* Damas promovidas (**D** brancas / **Q** pretas)
* Sistema de **captura de peças**
* **Modo single player** contra IA
* **Histórico** de movimentos
* Sistema de **pontuação**
* Interface amigável no terminal

## 🎮 Como Jogar

### Compilando

```bash
make
```

#### Alternativa: compilação direta com `gcc` (sem modularização)

Se preferir não usar a versão modularizada com vários arquivos `.c` e o `Makefile`, é possível compilar diretamente com o `gcc`.

```bash
gcc damas.c -o damas
```

### Executando

```bash
./damas
```

### Comandos do Jogo

1. Escolha o modo de jogo:

   * Jogador vs Jogador
   * Jogador vs Computador

2. Para mover peças:

   * Digite a posição de origem (ex: `D3`)
   * Digite a posição de destino (ex: `E4`)
   * Para sair, digite `S`

### Regras Básicas

* Peças movem-se diagonalmente
* Capturas são obrigatórias
* Damas podem mover-se várias casas
* Vence quem capturar todas as peças do oponente

## 📁 Estrutura do Projeto

```
projeto/
├── damas.h       # Definições e estruturas
├── main.c        # Função principal
├── jogo.c        # Lógica do jogo
├── ia.c          # Inteligência artificial
├── arquivo.c     # Manipulação de arquivos
├── utils.c       # Funções utilitárias
├── Makefile      # Compilação do projeto
└── historico.txt # Registro de jogadas
```

## 🧹 Limpando Arquivos Compilados

```bash
make clean
```

## 💻 Requisitos

* Compilador GCC
* Sistema operacional Windows
* Terminal com suporte a caracteres ASCII

---

Desenvolvido para a disciplina de Técnicas de Desenvolvimento de Algoritmos
