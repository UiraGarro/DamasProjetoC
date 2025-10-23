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

Se preferir não usar a versão modularizada com vários arquivos `.c` e o `Makefile`, é possível compilar diretamente com o `gcc` — útil quando você tem todo o código em um único arquivo (por exemplo `damas.c`) ou quer compilar todos os arquivos `.c` de uma vez. Exemplos:

* Se todo o código estiver em um único arquivo:

```bash
gcc -std=c11 -Wall -Wextra -o damas damas.c
```

* Compilar todos os módulos (`.c`) diretamente com `gcc` (equivalente ao que o Makefile faz):

```bash
gcc -std=c11 -Wall -Wextra -o damas main.c jogo.c ia.c arquivo.c utils.c
```

> Use essa alternativa quando quiser rodar o jogo sem gerar um projeto modularizado com headers separados. Ambas as formas — `make` ou `gcc` direto — geram o executável `damas`.

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

## 👥 Contribuindo

1. Fork o projeto
2. Crie sua branch de feature
3. Commit suas mudanças
4. Push para a branch
5. Abra um Pull Request

---

Desenvolvido para a disciplina de Técnicas de Desenvolvimento de Algoritmos
