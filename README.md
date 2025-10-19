# ♟️ Jogo de Damas em C

Um jogo de **Damas (Checkers)** desenvolvido em **C**, jogado no terminal entre dois jogadores.  
Possui visualização do tabuleiro, pontuação, captura de peças, promoção para dama, histórico de jogadas e opção de reiniciar a partida.

---

## 🚀 Funcionalidades

- Tabuleiro **8x8** com peças pretas (**X**) e brancas (**O**)
- Alternância automática de turnos entre os jogadores
- Movimentação e captura de peças conforme regras clássicas
- Promoção automática para **Dama** (**D / Q**)
- Sistema de **pontuação por captura**
- **Histórico de jogadas** salvo no arquivo `historico.txt`
- Opção de **jogar novamente** após encerrar a partida

---

## 🕹️ Como Jogar

### 1. Compilar o programa
Abra o terminal e execute:

gcc damas.c -o damas

shell
Copiar código

### 2. Executar o jogo
./damas

markdown
Copiar código

### 3. Jogar
1. Digite os nomes dos jogadores (Brancas e Pretas)  
2. Para movimentar uma peça:
   - **Mover de**: digite a posição de origem (ex.: `D3`)  
   - **Para**: digite a posição de destino (ex.: `E4`)  
3. Para sair do jogo, digite **S** no campo “Mover de”

### 4. Reiniciar ou encerrar
Ao sair, o programa perguntará:

Deseja jogar novamente? (S/N):

yaml
Copiar código

- **S** → Reinicia o tabuleiro  
- **N** → Encerra o jogo

---

## 📜 Histórico

Todas as jogadas são salvas automaticamente no arquivo `historico.txt`  
> O arquivo é **sobrescrito** a cada nova partida

---

## 🧑‍💻 Desenvolvido com

- Linguagem **C**
- Bibliotecas padrão: `stdio.h`, `ctype.h`, `stdlib.h`
- Interface de texto (console)

---

## 📦 Estrutura do Projeto

Projeto-Damas/
├── damas.c # Código principal do jogo
├── historico.txt # Arquivo gerado com o histórico das jogadas
└── README.md # Este arquivo