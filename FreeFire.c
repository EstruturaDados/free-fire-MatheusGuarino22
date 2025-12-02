#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// -----------------------------
// STRUCT DO COMPONENTE
// -----------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;


// -----------------------------
// FUNÇÕES AUXILIARES
// -----------------------------
void mostrarComponentes(Componente c[], int n) {
    printf("\n--- LISTA DE COMPONENTES ---\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] Nome: %s | Tipo: %s | Prioridade: %d\n",
               i, c[i].nome, c[i].tipo, c[i].prioridade);
    }
    printf("\n");
}


// -----------------------------
// BUBBLE SORT — ORDENAR POR NOME
// -----------------------------
int bubbleSortNome(Componente c[], int n) {
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comparacoes++;
            if (strcmp(c[j].nome, c[j + 1].nome) > 0) {
                Componente temp = c[j];
                c[j] = c[j + 1];
                c[j + 1] = temp;
            }
        }
    }
    return comparacoes;
}


// -----------------------------
// INSERTION SORT — ORDENAR POR TIPO
// -----------------------------
int insertionSortTipo(Componente c[], int n) {
    int comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = c[i];
        int j = i - 1;

        while (j >= 0 && strcmp(c[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            c[j + 1] = c[j];
            j--;
        }
        comparacoes++;
        c[j + 1] = chave;
    }
    return comparacoes;
}


// -----------------------------
// SELECTION SORT — ORDENAR POR PRIORIDADE
// -----------------------------
int selectionSortPrioridade(Componente c[], int n) {
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (c[j].prioridade < c[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            Componente temp = c[i];
            c[i] = c[min];
            c[min] = temp;
        }
    }
    return comparacoes;
}


// -----------------------------
// BUSCA BINÁRIA (APENAS APÓS ORDENAR POR NOME)
// -----------------------------
int buscaBinariaPorNome(Componente c[], int n, char chave[]) {
    int inicio = 0, fim = n - 1;
    int comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;

        int cmp = strcmp(chave, c[meio].nome);

        if (cmp == 0) {
            printf("\n>>> Componente encontrado: %s (%s), prioridade %d\n",
                   c[meio].nome, c[meio].tipo, c[meio].prioridade);
            printf("Comparações realizadas: %d\n", comparacoes);
            return meio;
        }
        if (cmp > 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("\n>>> Componente não encontrado.\n");
    printf("Comparações realizadas: %d\n", comparacoes);
    return -1;
}


// -----------------------------
// FUNÇÃO PRINCIPAL (MENU)
// -----------------------------
int main() {
    Componente componentes[20];
    int quantidade = 0;
    int opcao;

    do {
        printf("\n=============================\n");
        printf("  SISTEMA — TORRE DE RESGATE\n");
        printf("=============================\n");
        printf("1. Cadastrar componente\n");
        printf("2. Ordenar por nome (Bubble Sort)\n");
        printf("3. Ordenar por tipo (Insertion Sort)\n");
        printf("4. Ordenar por prioridade (Selection Sort)\n");
        printf("5. Busca binária por nome\n");
        printf("6. Mostrar componentes\n");
        printf("0. Sair\n> ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        if (opcao == 1) {
            if (quantidade >= 20) {
                printf("\nMochila cheia! (20 itens)\n");
            } else {
                printf("Nome do componente: ");
                fgets(componentes[quantidade].nome, 30, stdin);
                componentes[quantidade].nome[strcspn(componentes[quantidade].nome, "\n")] = 0;

                printf("Tipo do componente: ");
                fgets(componentes[quantidade].tipo, 20, stdin);
                componentes[quantidade].tipo[strcspn(componentes[quantidade].tipo, "\n")] = 0;

                printf("Prioridade (1 a 10): ");
                scanf("%d", &componentes[quantidade].prioridade);
                getchar();

                quantidade++;
                printf("\nComponente cadastrado!\n");
            }
        }

        else if (opcao == 2) {
            clock_t inicio = clock();
            int comp = bubbleSortNome(componentes, quantidade);
            clock_t fim = clock();
            printf("\nOrdenado por NOME (Bubble Sort)\n");
            printf("Comparações: %d\n", comp);
            printf("Tempo: %.5f ms\n", (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC);
        }

        else if (opcao == 3) {
            clock_t inicio = clock();
            int comp = insertionSortTipo(componentes, quantidade);
            clock_t fim = clock();
            printf("\nOrdenado por TIPO (Insertion Sort)\n");
            printf("Comparações: %d\n", comp);
            printf("Tempo: %.5f ms\n", (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC);
        }

        else if (opcao == 4) {
            clock_t inicio = clock();
            int comp = selectionSortPrioridade(componentes, quantidade);
            clock_t fim = clock();
            printf("\nOrdenado por PRIORIDADE (Selection Sort)\n");
            printf("Comparações: %d\n", comp);
            printf("Tempo: %.5f ms\n", (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC);
        }

        else if (opcao == 5) {
            char nomeBusca[30];
            printf("Digite o nome para busca: ");
            fgets(nomeBusca, 30, stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = 0;
            buscaBinariaPorNome(componentes, quantidade, nomeBusca);
        }

        else if (opcao == 6) {
            mostrarComponentes(componentes, quantidade);
        }

    } while (opcao != 0);

    return 0;
}
