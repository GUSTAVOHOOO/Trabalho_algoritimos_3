#include <stdio.h>
#include <stdlib.h>
#include "matriz.h" 

/*int main() {
    printf("--------------------------------------------------\n");
    printf("  DEMONSTRACAO DO TRABALHO DE ALGORITIMOS 3\n");
    printf("--------------------------------------------------\n\n");

    // 1. Criar a matriz com as dimensões desejadas
    printf("1. Criando uma matriz 5x5...\n");
    Matrix* matriz = matriz_criar(5, 5);
    if (matriz == NULL) {
        printf("Falha critica ao criar a matriz.\n");
        return 1; // Termina o programa se a criação falhar
    }
    printf("Matriz criada com sucesso!\n\n");

    // 2. Inserir (Setar) valores em posições específicas
    printf("2. Inserindo valores na matriz...\n");
    matriz_definir_valor(matriz, 1, 2, 10.5);
    matriz_definir_valor(matriz, 2, 3, 25.0);
    matriz_definir_valor(matriz, 3, 1, -5.0);
    matriz_definir_valor(matriz, 4, 4, 99.9);
    matriz_definir_valor(matriz, 5, 5, 123.45);
    matriz_definir_valor(matriz, 2, 2, 7.7);
    printf("Valores inseridos.\n");

    // Impressão completa para visualização inicial
    matriz_mostrar_na_tela(matriz);

    // 3. Consultar (Get) valores de posições específicas
    printf("3. Testando a funcao de consulta (get)...\n");
    double valorConsultado = matriz_obter_valor(matriz, 2, 3);
    printf("   - Consulta em (2,3): Valor = %.2f\n", valorConsultado);
    
    valorConsultado = matriz_obter_valor(matriz, 1, 1);
    printf("   - Consulta em (1,1) (vazio): Valor = %.2f (como esperado)\n\n", valorConsultado);

    // 4. Atualizar um valor existente
    printf("4. Atualizando o valor na posicao (4,4) para -77.7...\n");
    matriz_definir_valor(matriz, 4, 4, -77.7);
    printf("   - Novo valor em (4,4) eh: %.2f\n", matriz_obter_valor(matriz, 4, 4));
    matriz_mostrar_na_tela(matriz);

    // 5. Remover um elemento da matriz (setando seu valor para 0)
    printf("5. Removendo o elemento da posicao (2,3) setando-o para 0...\n");
    matriz_definir_valor(matriz, 2, 3, 0.0);
    printf("   - Valor em (2,3) agora eh: %.2f\n", matriz_obter_valor(matriz, 2, 3));
    matriz_mostrar_na_tela(matriz);

    // 6. Desalocar a matriz para liberar a memória
    printf("6. Destruindo a matriz e liberando toda a memoria...\n");
    matriz_apagar_completa(&matriz);
    if (matriz == NULL) {
        printf("Matriz destruida com sucesso e ponteiro definido como NULL.\n");
    } else {
        printf("Erro: O ponteiro da matriz nao foi definido como NULL.\n");
    }

    system("pause");
    
    printf("\n--------------------------------------------------\n");
    printf("            FINALIZAÇÃO DO TRABALHO\n");
    printf("--------------------------------------------------\n");

    return 0;
}
*/



void exibir_menu() {
    printf("\n===== MENU MATRIZ =====\n");
    printf("1. Criar nova matriz\n");
    printf("2. Definir valor\n");
    printf("3. Obter valor\n");
    printf("4. Mostrar matriz\n");
    printf("5. Apagar matriz\n");
    printf("6. Buscar valor na matriz\n");
    printf("7. Imprimir vizinhos de um elemento\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    Matriz *matriz = NULL;
    int opcao;

    do {
        exibir_menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int linhas, colunas;
                if (matriz != NULL) {
                    printf("Uma matriz já existe. Apague-a antes de criar outra.\n");
                    break;
                }
                printf("Digite o número de linhas: ");
                scanf("%d", &linhas);
                printf("Digite o número de colunas: ");
                scanf("%d", &colunas);
                matriz = matriz_criar(linhas, colunas);
                printf("Matriz criada com sucesso.\n");
                break;
            }
            case 2: {
                if (matriz == NULL) {
                    printf("Nenhuma matriz criada ainda.\n");
                    break;
                }
                int linha, coluna;
                double valor;
                printf("Digite a linha: ");
                scanf("%d", &linha);
                printf("Digite a coluna: ");
                scanf("%d", &coluna);
                printf("Digite o valor: ");
                scanf("%lf", &valor);
                matriz_definir_valor(matriz, linha, coluna, valor);
                printf("Valor atualizado.\n");
                break;
            }
            case 3: {
                if (matriz == NULL) {
                    printf("Nenhuma matriz criada ainda.\n");
                    break;
                }
                int linha, coluna;
                printf("Digite a linha: ");
                scanf("%d", &linha);
                printf("Digite a coluna: ");
                scanf("%d", &coluna);
                double valor = matriz_obter_valor(matriz, linha, coluna);
                printf("Valor na posição (%d, %d): %.2lf\n", linha, coluna, valor);
                break;
            }
            case 4: {
                if (matriz == NULL) {
                    printf("Nenhuma matriz criada ainda.\n");
                    break;
                }
                matriz_mostrar_na_tela(matriz);
                break;
            }
            case 5: {
                if (matriz != NULL) {
                    matriz_apagar_completa(&matriz);
                    printf("Matriz apagada com sucesso.\n");
                } else {
                    printf("Nenhuma matriz criada ainda.\n");
                }
                break;
            }
            case 6: {
                if (matriz == NULL) {
                    printf("Nenhuma matriz criada ainda.\n");
                    break;
                }
                double valor;
                printf("Digite o valor a ser buscado: ");
                scanf("%lf", &valor);
                No *resultado = matriz_buscar_valor(matriz, valor);
                if (resultado)
                    printf("Valor %.2lf encontrado na posição (%d, %d).\n", valor, resultado->linha, resultado->coluna);
                else
                    printf("Valor %.2lf não encontrado na matriz.\n", valor);
                break;
            }
            case 7: {
                if (matriz == NULL) {
                    printf("Nenhuma matriz criada ainda.\n");
                    break;
                }
                int linha, coluna;
                printf("Digite a linha do elemento: ");
                scanf("%d", &linha);
                printf("Digite a coluna do elemento: ");
                scanf("%d", &coluna);
                imprimir_vizinhos(matriz, linha, coluna);
                break;
            }
            case 0:
                printf("Encerrando o programa.\n");
                if (matriz != NULL) {
                    matriz_apagar_completa(&matriz);
                }
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
        
     } while (opcao != 0);

    return 0;
}
