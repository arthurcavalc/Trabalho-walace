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

void jogarContraComputador() {
    char nome[30];
    printf("Digite seu nome: ");
    scanf("%s", nome);
    limparBuffer();

    char palavra[] = "wallace"; 
    char dica[] = "Nome próprio";
    int tamanho = strlen(palavra);

    char descoberta[TAM_PALAVRA];
    for (int i = 0; i < tamanho; i++) {
        descoberta[i] = '_';
    }
    descoberta[tamanho] = '\0';

    int tentativas = 6;
    int acertou = 0;

    while (tentativas > 0 && !acertou) {
        printf("\nPalavra: %s\n", descoberta);
        printf("Dica: %s\n", dica);
        printf("Tentativas restantes: %d\n", tentativas);
        printf("Digite uma letra ou tente adivinhar a palavra: ");

        char entrada[TAM_PALAVRA];
        scanf("%s", entrada);
        limparBuffer();
        converterMinusculas(entrada);

        if (strlen(entrada) > 1) { 
            if (strcmp(entrada, palavra) == 0) {
                acertou = 1;
                strcpy(descoberta, palavra);
            } else {
                tentativas--;
                printf("Palavra incorreta!\n");
            }
        } else { 
            char letra = entrada[0];
            int encontrou = 0;
            for (int i = 0; i < tamanho; i++) {
                if (palavra[i] == letra && descoberta[i] == '_') {
                    descoberta[i] = palavra[i];
                    encontrou = 1;
                }
            }
            if (!encontrou) {
                tentativas--;
                printf("Letra incorreta!\n");
            } else {
                printf("Você acertou uma letra!\n");
            }
        }

        if (strcmp(descoberta, palavra) == 0) {
            acertou = 1;
        }
    }

    if (acertou) {
        printf("\nParabéns, você acertou a palavra: %s!\n", palavra);
        atualizarRanking(nome, 10);
    } else {
        printf("\nVocê perdeu! A palavra era: %s\n", palavra);
    }
}

void menu() {
    const char* nomeArquivoRanking = "ranking.txt";
    carregarRanking(nomeArquivoRanking);

    int opcao;
    do {
        printf("\n=== Jogo da Forca ===\n");
        printf("1. Jogar contra o Computador\n");
        printf("2. Jogar Multiplayer\n");
        printf("3. Cadastrar Palavra\n");
        printf("4. Mostrar Ranking\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Opção inválida! Tente novamente.\n");
            limparBuffer();
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                jogarContraComputador();
                break;
            case 3:
                cadastrarPalavra();
                break;
            case 4:
                mostrarRanking();
                break;
            case 5:
                salvarRanking(nomeArquivoRanking);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);
}

int main() {
    srand((unsigned int)time(NULL));
    menu();
    return 0;
}
