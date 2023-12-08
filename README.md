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

## Lógica do Jogo

O jogo utiliza a lógica de LIFO (Last in, First Out), ou pilha, na qual o conceito é que: O primeiro disco a ser colocado será o último a ser retirado.

## Como Jogar

A Torre de Hanói é um quebra-cabeça com três hastes e discos de diferentes tamanhos. O objetivo é mover a pilha original da primeira haste (1) para a última haste (3), obedecendo à regra de que discos maiores não podem ficar sobre discos menores. Para jogar, basta selecionar com um clique a torre de onde deseja retirar o disco e, em seguida, com um clique, escolher a torre para a qual deseja posicionar o disco. O jogador vence quando a última torre está completa, e perde ao selecionar a opção de desistência.

### Caso Venceu

![image](https://github.com/edenilsonjunior/torre-de-hanoi/assets/85528622/b247a6a5-8074-4e96-821b-e4d2fd900d28)

### Caso Desistiu



https://github.com/edenilsonjunior/torre-de-hanoi/assets/85528622/9b1cb1aa-8e6a-4918-8624-5f15094a167e


## Como Compilar

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

## Metodologia de Desenvolvimento

#### 1. Escolha do Jogo
O grupo realizou uma decisão conjunta para escolher o tipo de jogo a ser desenvolvido.

#### 2. Análise Preliminar
Foi conduzida uma análise detalhada utilizando técnicas de brainstorming para determinar os elementos essenciais do jogo.

#### 3. Definição de TADs e Métodos
Com base na análise, foram definidos os Tipos Abstratos de Dados (TADs) e os métodos que seriam implementados.

#### 4. Organização do Projeto
A estrutura do jogo foi organizada, e a biblioteca SDL2 foi escolhida para atender aos requisitos do projeto.

#### 5. Divisão de Responsabilidades
A equipe dividiu-se em dois grupos, atribuindo duas pessoas para a parte gráfica (front-end) e outras duas para a parte lógica (back-end).

#### 6. Implementação
A parte lógica do jogo foi desenvolvida em linguagem C, enquanto a parte gráfica foi construída utilizando a biblioteca SDL2.

#### 7. Gerenciamento de Interdependências
O relacionamento entre as partes lógica e gráfica apresentou desafios, mas a equipe superou-os por meio de comunicação eficiente e colaboração constante.

#### 9. Boas Práticas de Programação
Foram implementadas boas práticas de programação para garantir uma clara divisão de responsabilidades no código, contribuindo para a manutenibilidade e compreensão eficaz do sistema.

#### 10. Conclusão do Projeto
Ao final do desenvolvimento, foram adicionados elementos gráficos finais para aprimorar a estética e completar a integração do projeto. O resultado foi um produto funcional que atendeu aos objetivos estabelecidos.

Este arquivo .readme fornece uma visão geral do processo de desenvolvimento do jogo, desde a escolha inicial até a conclusão bem-sucedida do projeto.

