# Torre de Hanoi

![image](https://github.com/edenilsonjunior/torre-de-hanoi/assets/110670578/eeefade5-0247-44e2-bccb-bc7847eee918)



Projeto desenvolvido como parte da disciplina de Estrutura de Dados do curso de Sistemas para Internet no IFSP, Campus Araraquara.

## Integrantes

- Edenilson Silva Garcia Junior
- Endrew Gomes da Silva
- Gabriel Roberts Silva Soares
- Henrique Ferreira Bispo

## Descrição

O projeto foi desenvolvido como parte da disciplina de Estrutura de Dados do curso de Sistemas para Internet no IFSP, Campus Araraquara.

É o jogo Torre de Hanoi implementado em C. Ele faz uso de um tipo abstrato de dados, Pilha, onde o jogador pode fazer suas jogadas. Além disso, caso o jogador deseje desistir, o computador é capaz de completar o jogo por ele.

## Lógica do jogo

O jogo utiliza a lógica de LIFO (Last in, First Out), ou pilha, na qual o conceito é que: O primeiro disco a ser colocado será o último a ser retirado.

## Como Compilar e jogar

Clone o repositório para algum lugar de sua preferência e siga as instruções:

```bash
git clone https://github.com/edenilsonjunior/torre-de-hanoi.git
```

### Linux
Para compilar e rodar o projeto no Linux, siga as etapas:

#### 1. Abra o terminal na pasta onde foi clonado o repositório

Digite esse comando para baixar as dependências do jogo:
```bash
make linux-libs
```

Caso não funcione, abra um terminal e digite esses dois comandos:
```bash
sudo apt-get update
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```

Após ter baixado as dependências, execute esse comando para compilar:
```bash
make linux
```

#### 2. Executar o programa compilado

Após ter compilado o projeto, execute o projeto digitando:

```bash
./programa
```


### Windows
Para compilar e rodar o projeto no Windows, siga as etapas:

#### 1. Abra o terminal na pasta onde foi clonado o repositório

Execute esse comando para compilar:

```bash
mingw32-make windows
```

#### 2. Executar o programa compilado

Após ter compilado o projeto, execute o projeto digitando:

```bash
.\programa.exe
```
