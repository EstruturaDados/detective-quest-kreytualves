#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ====================
// Estrutura das salas
// ====================
typedef struct Sala {
    char nome[100];
    char pista[100];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// ====================
// Estrutura da BST de pistas
// ====================
typedef struct PistaNode {
    char pista[100];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

// ===================================================
// criarSala()
// Cria dinamicamente uma sala com nome e pista
// ===================================================
Sala* criarSala(const char *nome, const char *pista) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));

    strcpy(nova->nome, nome);

    if (pista != NULL)
        strcpy(nova->pista, pista);
    else
        nova->pista[0] = '\0';

    nova->esquerda = NULL;
    nova->direita = NULL;

    return nova;
}

// ===================================================
// inserirPista()
// Insere uma pista na BST
// ===================================================
PistaNode* inserirPista(PistaNode *raiz, const char *pista) {

    if (raiz == NULL) {
        PistaNode *novo = (PistaNode*) malloc(sizeof(PistaNode));

        strcpy(novo->pista, pista);
        novo->esquerda = NULL;
        novo->direita = NULL;

        return novo;
    }

    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    }
    else if (strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }

    return raiz;
}

// ===================================================
// exibirPistas()
// Percurso em ordem (alfabético)
// ===================================================
void exibirPistas(PistaNode *raiz) {

    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);

        printf("- %s\n", raiz->pista);

        exibirPistas(raiz->direita);
    }
}

// ===================================================
// explorarSalasComPistas()
// Navega pela mansão e coleta pistas
// ===================================================
void explorarSalasComPistas(Sala *inicio, PistaNode **arvorePistas) {

    Sala *atual = inicio;
    char opcao;

    while (atual != NULL) {

        printf("\n====================================\n");
        printf("Voce esta em: %s\n", atual->nome);

        if (strlen(atual->pista) > 0) {
            printf("Pista encontrada: %s\n", atual->pista);

            *arvorePistas =
                inserirPista(*arvorePistas, atual->pista);
        }

        printf("\nOpcoes:\n");

        if (atual->esquerda)
            printf("e - Ir para %s\n", atual->esquerda->nome);

        if (atual->direita)
            printf("d - Ir para %s\n", atual->direita->nome);

        printf("s - Sair da exploracao\n");

        printf("\nEscolha: ");
        scanf(" %c", &opcao);

        if (opcao == 's') {
            break;
        }
        else if (opcao == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        }
        else if (opcao == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        }
        else {
            printf("\nOpcao invalida!\n");
        }
    }
}

// ===================================================
// main()
// ===================================================
int main() {

    PistaNode *pistasColetadas = NULL;

    // Criação do mapa da mansão
    Sala *hall =
        criarSala("Hall de Entrada", "");

    Sala *salaEstar =
        criarSala("Sala de Estar", "Lençol manchado");

    Sala *cozinha =
        criarSala("Cozinha", "Gaveta perdida");

    Sala *biblioteca =
        criarSala("Biblioteca", "Livro com página faltando");

    Sala *porao =
        criarSala("Porao", "Pegadas de lama");

    // Ligações da árvore binária
    hall->esquerda = salaEstar;
    hall->direita = cozinha;

    salaEstar->esquerda = biblioteca;
    cozinha->direita = porao;

    printf("=== DETECTIVE QUEST ===\n");

    explorarSalasComPistas(hall, &pistasColetadas);

    printf("\n====================================\n");
    printf("PISTAS COLETADAS (ORDEM ALFABETICA)\n");
    printf("====================================\n");

    exibirPistas(pistasColetadas);

    return 0;
}

