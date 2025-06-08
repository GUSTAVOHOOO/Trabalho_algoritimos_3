#ifndef MATRIZ_H
#define MATRIZ_H

// ----------- ESTRUTURAS -----------

// Representa um nó da matriz. Pode ser um valor real, ou só um nó cabeça (de linha ou coluna)
typedef struct Node {
    int linha;
    int coluna;
    double valor;
    struct Node *direita; // Aponta pro próximo na mesma linha
    struct Node *abaixo;  // Aponta pro proximo na mesma coluna
} Node;

// Estrutura da matriz em si. Guarda o tamanho e o ponteiro pro nó principal
typedef struct {
    int linhas;
    int colunas;
    Node *cabeca; // Nó sentinela principal
} Matrix;


// ----------- FUNÇÕES -----------

/*
 Cria uma nova matriz esparsa com as dimensões indicadas.
 Retorna NULL se algo der errado.
*/
Matrix* matriz_criar(int totalDeLinhas, int totalDeColunas);

/*
 Define ou atualiza um valor na matriz.
 Se o valor for zero, o nó é removido (se existir)
*/
void matriz_definir_valor(Matrix *matrizDestino, int posicaoLinha, int posicaoColuna, double novoValor);

/*
 Recupera o valor armazenado numa posição específica
 Se nao houver valor ali, retorna 0.0
*/
double matriz_obter_valor(Matrix *matrizReferencia, int linhaDesejada, int colunaDesejada);

/*
 Mostra a matriz inteira no terminal (inclusive os zeros)
*/
void matriz_mostrar_na_tela(Matrix *matrizParaImprimir);

/*
 Libera toda a memória usada pela matriz e zera o ponteiro
*/
void matriz_apagar_completa(Matrix **ponteiroParaMatriz);

/*
 Dado um par linha coluna, imprime o valor dos seus 4 vizinhoas  
*/
void imprimir_vizinhos(Matrix *matriz, int linha, int coluna);

/*
 Percorre todos os nós da matriz e retorna o ponteiro para o no cujo valor corresponde extamente ao buscado
*/
Node* matriz_buscar_valor(Matrix *matriz, double valor);



#endif // MATRIZ_H
