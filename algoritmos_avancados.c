#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 20

// =====================
// ÁRVORE DA MANSÃO
// =====================

typedef struct Sala {
    char nome[50];
    struct Sala *esq;
    struct Sala *dir;
} Sala;

/*
 * criarSala()
 * Cria dinamicamente um cômodo da mansão.
 */
Sala* criarSala(char nome[]) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));

    strcpy(nova->nome, nome);
    nova->esq = NULL;
    nova->dir = NULL;

    return nova;
}

// =====================
// BST DE PISTAS
// =====================

typedef struct Pista {
    char nome[100];
    struct Pista *esq;
    struct Pista *dir;
} Pista;

/*
 * inserirPista()
 * Insere uma pista coletada na BST.
 */
Pista* inserirPista(Pista* raiz, char pista[]) {

    if (raiz == NULL) {
        Pista* nova = (Pista*) malloc(sizeof(Pista));

        strcpy(nova->nome, pista);

        nova->esq = NULL;
        nova->dir = NULL;

        return nova;
    }

    if (strcmp(pista, raiz->nome) < 0)
        raiz->esq = inserirPista(raiz->esq, pista);

    else if (strcmp(pista, raiz->nome) > 0)
        raiz->dir = inserirPista(raiz->dir, pista);

    return raiz;
}

void listarPistas(Pista* raiz) {

    if (raiz != NULL) {

        listarPistas(raiz->esq);

        printf("- %s\n", raiz->nome);

        listarPistas(raiz->dir);
    }
}

// =====================
// HASH
// =====================

typedef struct EntradaHash {
    char pista[100];
    char suspeito[50];
    struct EntradaHash* prox;
} EntradaHash;

EntradaHash* tabela[TAM_HASH];

int funcaoHash(char chave[]) {

    int soma = 0;

    for (int i = 0; chave[i] != '\0'; i++)
        soma += chave[i];

    return soma % TAM_HASH;
}

/*
 * inserirNaHash()
 * Associa uma pista a um suspeito.
 */
void inserirNaHash(char pista[], char suspeito[]) {

    int indice = funcaoHash(pista);

    EntradaHash* nova =
        (EntradaHash*) malloc(sizeof(EntradaHash));

    strcpy(nova->pista, pista);
    strcpy(nova->suspeito, suspeito);

    nova->prox = tabela[indice];
    tabela[indice] = nova;
}

/*
 * encontrarSuspeito()
 * Consulta o suspeito associado à pista.
 */
char* encontrarSuspeito(char pista[]) {

    int indice = funcaoHash(pista);

    EntradaHash* atual = tabela[indice];

    while (atual != NULL) {

        if (strcmp(atual->pista, pista) == 0)
            return atual->suspeito;

        atual = atual->prox;
    }

    return NULL;
}

// =====================
// CONTAGEM DE PISTAS
// =====================

int contarPistasSuspeito(
    Pista* raiz,
    char suspeito[])
{
    if (raiz == NULL)
        return 0;

    int total = 0;

    char* dono = encontrarSuspeito(raiz->nome);

    if (dono != NULL &&
        strcmp(dono, suspeito) == 0)
        total++;

    total += contarPistasSuspeito(
        raiz->esq,
        suspeito);

    total += contarPistasSuspeito(
        raiz->dir,
        suspeito);

    return total;
}

// =====================
// PISTAS DAS SALAS
// =====================

char* obterPista(char sala[]) {

    if (strcmp(sala, "Biblioteca") == 0)
        return "Livro Rasgado";

    if (strcmp(sala, "Escritorio") == 0)
        return "Carta Misteriosa";

    if (strcmp(sala, "Cozinha") == 0)
        return "Faca Ensanguentada";

    if (strcmp(sala, "Jardim") == 0)
        return "Pegadas";

    if (strcmp(sala, "Salao") == 0)
        return "Relogio Quebrado";

    return NULL;
}

// =====================
// EXPLORAÇÃO
// =====================

/*
 * explorarSalas()
 * Navega pela mansão e coleta pistas.
 */
void explorarSalas(
    Sala* atual,
    Pista** arvorePistas)
{
    char opcao;

    while (atual != NULL) {

        printf("\nVoce esta em: %s\n",
               atual->nome);

        char* pista =
            obterPista(atual->nome);

        if (pista != NULL) {

            printf("Pista encontrada: %s\n",
                   pista);

            *arvorePistas =
                inserirPista(
                    *arvorePistas,
                    pista);
        }

        printf("\n[e] Esquerda\n");
        printf("[d] Direita\n");
        printf("[s] Sair\n");
        printf("Opcao: ");

        scanf(" %c", &opcao);

        if (opcao == 'e')
            atual = atual->esq;

        else if (opcao == 'd')
            atual = atual->dir;

        else
            break;
    }
}

// =====================
// JULGAMENTO FINAL
// =====================

/*
 * verificarSuspeitoFinal()
 * Realiza a acusação final.
 */
void verificarSuspeitoFinal(
    Pista* arvorePistas)
{
    char suspeito[50];

    printf("\nDigite o nome do suspeito: ");
    scanf("%s", suspeito);

    int quantidade =
        contarPistasSuspeito(
            arvorePistas,
            suspeito);

    printf("\nPistas encontradas: %d\n",
           quantidade);

    if (quantidade >= 2)
        printf("Acusacao sustentada! %s e o culpado.\n",
               suspeito);
    else
        printf("Evidencias insuficientes contra %s.\n",
               suspeito);
}

// =====================
// MAIN
// =====================

int main() {

    Pista* arvorePistas = NULL;

    for (int i = 0; i < TAM_HASH; i++)
        tabela[i] = NULL;

    // Associações pista -> suspeito

    inserirNaHash(
        "Livro Rasgado",
        "Carlos");

    inserirNaHash(
        "Carta Misteriosa",
        "Carlos");

    inserirNaHash(
        "Faca Ensanguentada",
        "Ana");

    inserirNaHash(
        "Pegadas",
        "Ana");

    inserirNaHash(
        "Relogio Quebrado",
        "Bruno");

    // Montagem da mansão

    Sala* raiz =
        criarSala("Salao");

    raiz->esq =
        criarSala("Biblioteca");

    raiz->dir =
        criarSala("Escritorio");

    raiz->esq->esq =
        criarSala("Cozinha");

    raiz->esq->dir =
        criarSala("Jardim");

    printf("=== DETECTIVE QUEST ===\n");

    explorarSalas(
        raiz,
        &arvorePistas);

    printf("\n=== PISTAS COLETADAS ===\n");

    listarPistas(arvorePistas);

    verificarSuspeitoFinal(
        arvorePistas);

    return 0;
}

