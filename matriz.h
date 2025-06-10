#ifndef MATRIZ_H
#define MATRIZ_H

// ----------- ESTRUTURAS -----------

// Representa um nó da matriz. Pode ser um valor real, ou só um nó cabeça (de linha ou coluna)
typedef struct No {
    int linha;
    int coluna;
    double valor;
    struct No *direita; // Aponta pro próximo na mesma linha
    struct No *abaixo;  // Aponta pro proximo na mesma coluna
} No;

// Estrutura da matriz em si. Guarda o tamanho e o ponteiro pro nó principal
typedef struct {
    int linhas;
    int colunas;
    No *cabeca; // Nó sentinela principal
} Matriz;


// ----------- FUNÇÕES -----------

/*
 Cria uma nova matriz esparsa com as dimensões indicadas.
 Retorna NULL se algo der errado.
*/
Matriz* matriz_criar(int totalDeLinhas, int totalDeColunas);

/*
 Define ou atualiza um valor na matriz.
 Se o valor for zero, o nó é removido (se existir)
*/
void matriz_definir_valor(Matriz *matrizDestino, int posicaoLinha, int posicaoColuna, double novoValor);

/*
 Recupera o valor armazenado numa posição específica
 Se nao houver valor ali, retorna 0.0
*/
double matriz_obter_valor(Matriz *matrizReferencia, int linhaDesejada, int colunaDesejada);

/*
 Mostra a matriz inteira no terminal (inclusive os zeros)
*/
void matriz_mostrar_na_tela(Matriz *matrizParaImprimir);

/*
 Libera toda a memória usada pela matriz e zera o ponteiro
*/
void matriz_apagar_completa(Matriz **ponteiroParaMatriz);

/*
 Dado um par linha coluna, imprime o valor dos seus 4 vizinhoas  
*/
void imprimir_vizinhos(Matriz *matriz, int linha, int coluna);

/*
 Percorre todos os nós da matriz e retorna o ponteiro para o no cujo valor corresponde extamente ao buscado
*/
No* matriz_buscar_valor(Matriz *matriz, double valor);



#endif // MATRIZ_H
