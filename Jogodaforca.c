#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_PALAVRAS 100
#define TAM_PALAVRA 50
#define MAX_JOGADORES 10

typedef struct {
    char palavra[TAM_PALAVRA];
    char dica[TAM_PALAVRA];
} Palavra;

typedef struct {
    char nome[30];
    int pontos;
} Jogador;

Palavra palavras[MAX_PALAVRAS];
int totalPalavras = 0;

Jogador ranking[MAX_JOGADORES];
int totalJogadores = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void converterMinusculas(char* texto) {
    for (int i = 0; texto[i]; i++) {
        texto[i] = tolower(texto[i]);
    }
}

void salvarRanking(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar o ranking!\n");
        return;
    }

    fprintf(arquivo, "%d\n", totalJogadores);
    for (int i = 0; i < totalJogadores; i++) {
        fprintf(arquivo, "%s %d\n", ranking[i].nome, ranking[i].pontos);
    }

    fclose(arquivo);
    printf("Ranking salvo com sucesso no arquivo '%s'.\n", nomeArquivo);
}

void carregarRanking(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Arquivo de ranking não encontrado. Um novo ranking será criado.\n");
        return;
    }

    fscanf(arquivo, "%d\n", &totalJogadores);
    for (int i = 0; i < totalJogadores; i++) {
        fscanf(arquivo, "%s %d\n", ranking[i].nome, &ranking[i].pontos);
    }

    fclose(arquivo);
    printf("Ranking carregado com sucesso do arquivo '%s'.\n", nomeArquivo);
}

void cadastrarPalavra() {
    if (totalPalavras >= MAX_PALAVRAS) {
        printf("Limite de palavras atingido!\n");
        return;
    }

    printf("Digite a palavra (sem espaços): ");
    scanf("%s", palavras[totalPalavras].palavra);
    limparBuffer();
    converterMinusculas(palavras[totalPalavras].palavra);

    printf("Digite a dica: ");
    fgets(palavras[totalPalavras].dica, TAM_PALAVRA, stdin);
    palavras[totalPalavras].dica[strcspn(palavras[totalPalavras].dica, "\n")] = '\0';

    totalPalavras++;
    printf("Palavra cadastrada com sucesso!\n");
}

void mostrarRanking() {
    printf("\n=== Ranking ===\n");
    if (totalJogadores == 0) {
        printf("Nenhum jogador no ranking.\n");
        return;
    }

    for (int i = 0; i < totalJogadores; i++) {
        printf("%d. %s - %d pontos\n", i + 1, ranking[i].nome, ranking[i].pontos);
    }
}

void atualizarRanking(char nome[], int pontos) {
    for (int i = 0; i < totalJogadores; i++) {
        if (strcmp(ranking[i].nome, nome) == 0) {
            ranking[i].pontos += pontos;
            return;
        }
    }

    if (totalJogadores < MAX_JOGADORES) {
        strcpy(ranking[totalJogadores].nome, nome);
        ranking[totalJogadores].pontos = pontos;
        totalJogadores++;
    }
}
