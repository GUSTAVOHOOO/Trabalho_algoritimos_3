#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

// Gera e inicializa nós cabeçalhos para linhas e colunas
static Node* criarNosCabecaCompletos(int totalLinhas, int totalColunas) {
    Node *cabecaMatriz = (Node*) malloc(sizeof(Node));
    if (!cabecaMatriz) return NULL;
    cabecaMatriz->linha = -1;
    cabecaMatriz->coluna = -1;

    // Cria cabeçalhos de coluna
    Node *cursor = cabecaMatriz;
    for (int col = 1; col <= totalColunas; col++) {
        Node *noColuna = (Node*) malloc(sizeof(Node));
        if (!noColuna) return NULL; // não libera anteriores por simplicidade
        noColuna->linha = -1;
        noColuna->coluna = col;
        noColuna->abaixo = noColuna; // aponta para si mesmo

        cursor->direita = noColuna;
        cursor = noColuna;
    }
    cursor->direita = cabecaMatriz;

    // Cria cabeçalhos de linha
    cursor = cabecaMatriz;
    for (int lin = 1; lin <= totalLinhas; lin++) {
        Node *noLinha = (Node*) malloc(sizeof(Node));
        if (!noLinha) return NULL;
        noLinha->linha = lin;
        noLinha->coluna = -1;
        noLinha->direita = noLinha; // aponta para si mesmo

        cursor->abaixo = noLinha;
        cursor = noLinha;
    }
    cursor->abaixo = cabecaMatriz;

    return cabecaMatriz;
}

// Cria uma matriz esparsa com dimenções definidas
Matrix* matriz_criar(int linhas, int colunas) {
    if (linhas <= 0 || colunas <= 0) return NULL;

    Matrix *mat = (Matrix*) malloc(sizeof(Matrix));
    if (!mat) return NULL;

    mat->linhas = linhas;
    mat->colunas = colunas;
    mat->cabeca = criarNosCabecaCompletos(linhas, colunas);
    if (!mat->cabeca) {
        free(mat);
        return NULL;
    }
    return mat;
}

// Insere ou remove valor na posição indicada
void matriz_definir_valor(Matrix *m, int linhaPos, int colunaPos, double valor) {
    if (!m || linhaPos <= 0 || linhaPos > m->linhas || colunaPos <= 0 || colunaPos > m->colunas)
        return;

    // Localiza cabeçalho de linha
    Node *antLinha = m->cabeca;
    for (int i = 0; i < linhaPos; i++) antLinha = antLinha->abaixo;
    while (antLinha->direita->coluna != -1 && antLinha->direita->coluna < colunaPos)
        antLinha = antLinha->direita;

    // Localiza cabeçalho de coluna
    Node *antColuna = m->cabeca;
    for (int j = 0; j < colunaPos; j++) antColuna = antColuna->direita;
    while (antColuna->abaixo->linha != -1 && antColuna->abaixo->linha < linhaPos)
        antColuna = antColuna->abaixo;

    Node *atual = antLinha->direita;
    // Se já existe nó naquela posição
    if (atual->linha == linhaPos && atual->coluna == colunaPos) {
        if (valor == 0.0) {
            // Remove o nó
            antLinha->direita = atual->direita;
            antColuna->abaixo = atual->abaixo;
            free(atual);
        } else {
            // Atualiza valor
            atual->valor = valor;
        }
    } else if (valor != 0.0) {
        // Cria novo nó para valor não-nulo
        Node *novoNo = (Node*) malloc(sizeof(Node));
        if (!novoNo) return;
        novoNo->linha = linhaPos;
        novoNo->coluna = colunaPos;
        novoNo->valor = valor;

        // Insere na lista de linha
        novoNo->direita = antLinha->direita;
        antLinha->direita = novoNo;
        // Insere na lista de coluna
        novoNo->abaixo = antColuna->abaixo;
        antColuna->abaixo = novoNo;
    }
}

// Obtém valor na posição especificada
double matriz_obter_valor(Matrix *m, int linhaPos, int colunaPos) {
    if (!m || linhaPos <= 0 || linhaPos > m->linhas || colunaPos <= 0 || colunaPos > m->colunas)
        return 0.0;

    Node *cursor = m->cabeca;
    for (int i = 0; i < linhaPos; i++) cursor = cursor->abaixo;
    cursor = cursor->direita;
    while (cursor->coluna != -1 && cursor->coluna < colunaPos)
        cursor = cursor->direita;

    if (cursor->linha == linhaPos && cursor->coluna == colunaPos)
        return cursor->valor;

    return 0.0;
}

// Exibe a matriz completa, impressa linha a linha
void matriz_mostrar_na_tela(Matrix *m) {
    if (!m) {
        printf("Matriz não inicializada ou vazia.\n");
        return;
    }

    printf("\nMatriz %dx%d:\n", m->linhas, m->colunas);
    Node *cabLinha = m->cabeca->abaixo;
    for (int i = 1; i <= m->linhas; i++) {
        Node *pos = cabLinha->direita;
        for (int j = 1; j <= m->colunas; j++) {
            if (pos->linha == i && pos->coluna == j) {
                printf("%8.2f ", pos->valor);
                if (pos->direita != cabLinha)
                    pos = pos->direita;
            } else {
                printf("%8.2f ", 0.0);
            }
        }
        printf("\n");
        cabLinha = cabLinha->abaixo;
    }
    printf("----- FIM DA MATRIZ -----\n");
}

// Apaga e libera toda a estrutura da matriz
void matriz_apagar_completa(Matrix **pm) {
    if (!pm || !*pm) return;

    Matrix *mk = *pm;
    Node *linCab = mk->cabeca->abaixo;

    // Libera nós de dados
    while (linCab->linha != -1) {
        Node *it = linCab->direita;
        while (it->coluna != -1) {
            Node *temp = it;
            it = it->direita;
            free(temp);
        }
        linCab = linCab->abaixo;
    }

    // Libera cabeçalhos de linha
    Node *tln = mk->cabeca->abaixo;
    while (tln->linha != -1) {
        Node *prox = tln->abaixo;
        free(tln);
        tln = prox;
    }
    // Libera cabeçalhos de coluna
    Node *tcl = mk->cabeca->direita;
    while (tcl->coluna != -1) {
        Node *prox = tcl->direita;
        free(tcl);
        tcl = prox;
    }

    free(mk->cabeca);
    free(mk);
    *pm = NULL;
}



// Busca um nó com o valor exato na matriz
Node* matriz_buscar_valor(Matrix *matriz, double valor) {
    if (!matriz) return NULL;
    Node *linhaCab = matriz->cabeca->abaixo;
    while (linhaCab->linha != -1) {
        Node *cursor = linhaCab->direita;
        while (cursor->coluna != -1) {
            if (cursor->valor == valor)
                return cursor;
            cursor = cursor->direita;
        }
        linhaCab = linhaCab->abaixo;
    }
    return NULL;
}

// Imprime os vizinhos (cima, baixo, esquerda, direita) do nó na posição (linha, coluna)
void imprimir_vizinhos(Matrix *matriz, int linha, int coluna) {
    if (!matriz || linha <= 0 || linha > matriz->linhas || coluna <= 0 || coluna > matriz->colunas) {
        printf("Coordenadas fora dos limites da matriz.\n");
        return;
    }

    printf("Vizinhos do elemento (%d, %d):\n", linha, coluna);

    // Cima
    if (linha > 1) {
        double valor = matriz_obter_valor(matriz, linha - 1, coluna);
        printf("Cima (%d, %d): %.2lf\n", linha - 1, coluna, valor);
    } else {
        printf("Cima: inexistente\n");
    }

    // Baixo
    if (linha < matriz->linhas) {
        double valor = matriz_obter_valor(matriz, linha + 1, coluna);
        printf("Baixo (%d, %d): %.2lf\n", linha + 1, coluna, valor);
    } else {
        printf("Baixo: inexistente\n");
    }

    // Esquerda
    if (coluna > 1) {
        double valor = matriz_obter_valor(matriz, linha, coluna - 1);
        printf("Esquerda (%d, %d): %.2lf\n", linha, coluna - 1, valor);
    } else {
        printf("Esquerda: inexistente\n");
    }

    // Direita
    if (coluna < matriz->colunas) {
        double valor = matriz_obter_valor(matriz, linha, coluna + 1);
        printf("Direita (%d, %d): %.2lf\n", linha, coluna + 1, valor);
    } else {
        printf("Direita: inexistente\n");
    }
}

