♟️ Jogo de Damas em C

Este é um jogo de Damas (Checkers) feito em linguagem C, jogado no terminal entre dois jogadores.
O jogo possui exibição visual do tabuleiro, pontuação, captura de peças, promoção para dama, histórico de jogadas e opção de jogar novamente.

🚀 Funcionalidades

Tabuleiro 8x8 com peças pretas (X) e brancas (O).

Alternância automática de turnos entre os jogadores.

Regras básicas de movimentação e captura.

Promoção automática para Dama (D / Q).

Sistema de pontuação por captura.

Histórico de jogadas salvo no arquivo historico.txt.

Opção de jogar novamente após sair da partida.

🕹️ Como Jogar

Compile o programa

gcc damas.c -o damas


Execute o jogo

./damas


Digite os nomes dos jogadores (Brancas e Pretas).

Durante o jogo:

Para mover, digite a posição de origem e destino, por exemplo:

Mover de (ex: D3): D3  
Para (ex: E4): E4


Para sair do jogo, digite S no campo “Mover de”.

Ao sair, o programa perguntará:

Deseja jogar novamente? (S/N):


Digite S para reiniciar o tabuleiro.

Digite N para encerrar o jogo.

📜 Histórico

Todas as jogadas realizadas são salvas automaticamente em um arquivo chamado:

historico.txt


O arquivo é sobrescrito a cada nova partida.

🧑‍💻 Desenvolvido com

Linguagem C

Biblioteca padrão (stdio.h, ctype.h, stdlib.h)

Interface de texto (console)

📦 Estrutura do Projeto
📁 Projeto-Damas
│
├── damas.c          # Código principal do jogo
├── historico.txt    # Arquivo gerado com o histórico das jogadas
└── README.md        # Este arquivo