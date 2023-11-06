# Torre de Hanoi

![image](https://github.com/edenilsonjunior/torre-de-hanoi/assets/110670578/ed32e041-e102-47d1-a909-8baa3be47ced)

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
gcc main.c impl_jogo.c impl_pilha.c -o programa.exe -I .\SDL2\i686-w64-mingw32\include -L .\SDL2\i686-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
```

### 3. Executar o programa compilado

Após ter compilado o projeto seguindo as instruções acima, execute o projeto digitando:

Para windows:
```bash
./programa
```
