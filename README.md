

-----

# Implementação de Matriz Esparsa em C

Este é um trabalho acadêmico que implementa o conceito de uma **Matriz Esparsa** utilizando a linguagem C. O objetivo principal é criar uma estrutura de dados otimizada para matrizes que possuem uma grande quantidade de elementos com valor zero, economizando uma quantidade significativa de memória em comparação com uma representação de array 2D convencional.

## Conceito Principal

Uma matriz esparsa é uma matriz em que a maioria dos elementos é zero. Para evitar o desperdício de memória ao alocar espaço para todos esses zeros, esta implementação armazena apenas os elementos não nulos.

A estrutura de dados utilizada é uma **lista duplamente ligada ortogonal com nós cabeça**. Cada nó que armazena um valor diferente de zero está simultaneamente em duas listas:

  * Uma **lista circular horizontal** (através do ponteiro `direita`) que conecta todos os elementos da mesma linha.
  * Uma **lista circular vertical** (através do ponteiro `abaixo`) que conecta todos os elementos da mesma coluna.

Para organizar essa estrutura, utilizamos **nós cabeça**:

  * **Nó Cabeça Principal**: O ponto de partida de toda a matriz, com `linha = -1` e `coluna = -1`.
  * **Nós Cabeça de Linha e Coluna**: Cada linha e cada coluna possui seu próprio nó cabeça, que serve como ponto de entrada e marca o início/fim das listas circulares.

## Estrutura de Dados

As `structs` fundamentais que definem a matriz estão no arquivo `matriz.h`:

### `No`

A unidade fundamental que representa um elemento (ou um nó cabeça) na matriz.

```c
typedef struct No {
    int linha;
    int coluna;
    double valor;
    struct No *direita; // Aponta para o próximo nó na mesma linha
    struct No *abaixo;  // Aponta para o próximo nó na mesma coluna
} No;
```

### `Matriz`

O objeto principal que representa a matriz, guardando suas dimensões e o ponteiro para o nó cabeça principal.

```c
typedef struct {
    int linhas;
    int colunas;
    No *cabeca; // Nó sentinela principal
} Matriz;
```

-----

## Funcionalidades (API)

As seguintes funções estão disponíveis em `matriz.h` para manipulação da estrutura:

| Função | Descrição |
| :--- | :--- |
| **`Matriz* matriz_criar(int linhas, int colunas)`** | Aloca a memória e inicializa a estrutura da matriz, incluindo todos os nós cabeça necessários. Retorna um ponteiro para a `Matriz` ou `NULL` em caso de falha. |
| **`void matriz_definir_valor(Matriz *m, int l, int c, double v)`** | Função principal para inserir, atualizar ou remover um valor. Se o valor `v` for `0.0`, o nó correspondente na posição `(l, c)` é removido. Caso contrário, o valor é inserido ou atualizado. |
| **`double matriz_obter_valor(Matriz *m, int l, int c)`** | Retorna o valor na posição `(l, c)`. Se nenhum nó for encontrado nessa posição, a função assume que o valor é zero e retorna `0.0`. |
| **`No* matriz_buscar_valor(Matriz *matriz, double valor)`** | Percorre todos os nós de dados da matriz e retorna um ponteiro para o primeiro nó encontrado cujo valor seja exatamente igual ao `valor` buscado. Retorna `NULL` se não encontrar. |
| **`void imprimir_vizinhos(Matriz *matriz, int linha, int coluna)`** | Mostra os valores dos quatro vizinhos (acima, abaixo, à esquerda e à direita) de uma célula específica, reutilizando a função `matriz_obter_valor`. |
| **`void matriz_mostrar_na_tela(Matriz *m)`** | Imprime uma representação visual da matriz completa no terminal, exibindo `0.0` para as posições que não possuem nós alocados. |
| **`void matriz_apagar_completa(Matriz **pm)`** | Libera toda a memória alocada pela matriz (nós de dados, nós cabeça e a própria struct `Matriz`) para evitar vazamentos de memória. Ao final, define o ponteiro da matriz como `NULL`. |

-----

## Como Compilar e Executar

Este projeto pode ser compilado utilizando um compilador C padrão como o GCC.

1.  **Clone o repositório:**

    ```bash
    git clone https://github.com/seu-usuario/trabalho_algoritimos_3.git
    ```

2.  **Navegue até a pasta do projeto:**

    ```bash
    cd trabalho_algoritimos_3
    ```

3.  **Compile os arquivos fonte:**

    ```bash
    gcc main.c matriz.c -o programa_matriz
    ```

4.  **Execute o programa:**

    ```bash
    ./programa_matriz
    ```

Após a execução, um menu interativo será exibido, permitindo testar todas as funcionalidades da matriz em tempo real.

### Menu Interativo

O arquivo `main.c` contém um menu para facilitar a demonstração e o teste da implementação:

```
===== MENU MATRIZ =====
1. Criar nova matriz
2. Definir valor
3. Obter valor
4. Mostrar matriz
5. Apagar matriz
6. Buscar valor na matriz
7. Imprimir vizinhos de um elemento
0. Sair
Escolha uma opcao:
```

## Autor

  * **Gustavo** - *Desenvolvedor do projeto* - [gustavohooo](https://www.google.com/search?q=https://github.com/gustavohooo)

## Licença

Este projeto é um trabalho acadêmico e seu código é aberto para fins educacionais. Sinta-se à vontade para utilizá-lo como referência para estudos sobre estruturas de dados em C.
