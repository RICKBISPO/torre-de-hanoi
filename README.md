# Torre de Hanoi

![Imagem](https://github.com/edenilsonjunior/torre-de-hanoi/assets/110670578/bbac9cc2-fa7d-4465-9f04-002a6ba44b35)

Projeto desenvolvido como parte da disciplina de Estrutura de Dados do curso de Sistemas para Internet no IFSP, Campus Araraquara.

## Integrantes

- Edenilson Silva Garcia Junior
- Endrew Gomes da Silva
- Gabriel Roberts Silva Soares
- Henrique Ferreira Bispo

## Descrição

O projeto foi desenvolvido como parte da disciplina de Estrutura de Dados do curso de Sistemas para Internet no IFSP, Campus Araraquara.

É o jogo Torre de Hanoi implementado em C. Ele faz uso de um tipo abstrato de dados, Pilha, onde o jogador pode fazer suas jogadas. Além disso, caso o jogador deseje desistir, o computador é capaz de completar o jogo por ele.

## Como Compilar

Para compilar e rodar o projeto, siga as etapas:

### 1. Clonar o repositório

```bash
git clone https://github.com/edenilsonjunior/torre-de-hanoi.git
```

### 2. Abra o terminal na pasta onde foi clonado o repositório

Navegue até a pasta do projeto e execute esse comando no terminal:

Para windows:
```bash
gcc -o programa.exe impl_pilha.c main.c
```

Para linux:
```bash
gcc -o programa impl_pilha.c main.c
```

### 3. Executar o programa compilado

Após ter compilado o projeto seguindo as instruções acima, execute o projeto digitando:

Para windows:
```bash
./programa.exe
```

Para linux:
```bash
./programa
```