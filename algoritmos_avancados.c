#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa uma sala da mansão
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Cria uma nova sala dinamicamente
Sala* criarSala(char nome[]) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));

    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;

    return nova;
}

// Permite ao jogador explorar a mansão
void explorarSalas(Sala *atual) {
    char opcao;

    while (atual != NULL) {
        printf("\nVoce esta em: %s\n", atual->nome);

        // Verifica se chegou a uma folha
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Fim do caminho! Voce encontrou um comodo sem saidas.\n");
            break;
        }

        printf("Escolha um caminho:\n");

        if (atual->esquerda != NULL)
            printf("e - Ir para a esquerda\n");

        if (atual->direita != NULL)
            printf("d - Ir para a direita\n");

        printf("s - Sair\n");
        printf("Opcao: ");
        scanf(" %c", &opcao);

        if (opcao == 'e') {
            if (atual->esquerda != NULL)
                atual = atual->esquerda;
            else
                printf("Nao existe caminho para a esquerda!\n");
        }
        else if (opcao == 'd') {
            if (atual->direita != NULL)
                atual = atual->direita;
            else
                printf("Nao existe caminho para a direita!\n");
        }
        else if (opcao == 's') {
            printf("Exploracao encerrada.\n");
            break;
        }
        else {
            printf("Opcao invalida!\n");
        }
    }
}

// Libera toda a memoria da arvore
void liberarSalas(Sala *raiz) {
    if (raiz != NULL) {
        liberarSalas(raiz->esquerda);
        liberarSalas(raiz->direita);
        free(raiz);
    }
}

// Monta o mapa da mansao e inicia a exploracao
int main() {
    Sala *hall = criarSala("Hall de entrada");

    hall->esquerda = criarSala("Sala de estar");
    hall->direita = criarSala("Biblioteca");

    hall->esquerda->esquerda = criarSala("Cozinha");
    hall->esquerda->direita = criarSala("Jardim");

    hall->direita->esquerda = criarSala("Escritorio");
    hall->direita->direita = criarSala("Quarto Secreto");

    printf("=== DETECTIVE QUEST ===\n");
    printf("Explore a mansao em busca de pistas!\n");

    explorarSalas(hall);

    liberarSalas(hall);

    return 0;
}

