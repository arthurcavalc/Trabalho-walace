#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_PALAVRAS 100
#define TAM_PALAVRA 50
#define MAX_JOGADORES 10

void jogarContraComputador() {
    char nome[30];
    printf("Digite seu nome: ");
    scanf("%s", nome);    // Lê o nome do jogador
    limparBuffer();

    char palavra[] = "wallace";    // Define a palavra a ser adivinhada
    char dica[] = "Nome próprio";    // Define a dica da palavra
    int tamanho = strlen(palavra);    // Calcula o tamanho da palavra

    char descoberta[TAM_PALAVRA];
    for (int i = 0; i < tamanho; i++) {
        descoberta[i] = '_';    // Inicializa a palavra descoberta com sublinhados
    }
    descoberta[tamanho] = '\0';

    int tentativas = 6;    // Define o número de tentativas
    int acertou = 0;    // Inicializa o status de acerto

    while (tentativas > 0 && !acertou) {
        printf("\nPalavra: %s\n", descoberta);
        printf("Dica: %s\n", dica);
        printf("Tentativas restantes: %d\n", tentativas);
        printf("Digite uma letra ou tente adivinhar a palavra: ");

        char entrada[TAM_PALAVRA];
        scanf("%s", entrada);    // Lê a entrada do jogador (letra ou palavra)
        limparBuffer();
        converterMinusculas(entrada);

        if (strlen(entrada) > 1) {    // Se a entrada for uma palavra
            if (strcmp(entrada, palavra) == 0) {
                acertou = 1;    // Se a palavra estiver correta
                strcpy(descoberta, palavra);    // Copia a palavra para descoberta
            } else {
                tentativas--;
                printf("Palavra incorreta!\n");
            }
        } else {    // Se a entrada for uma letra
            char letra = entrada[0];
            int encontrou = 0;
            for (int i = 0; i < tamanho; i++) {
                if (palavra[i] == letra && descoberta[i] == '_') {
                    descoberta[i] = palavra[i];    // Atualiza a palavra descoberta com a letra correta
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
            acertou = 1;    // Se a palavra foi totalmente descoberta
        }
    }

    if (acertou) {
        printf("\nParabéns, você acertou a palavra: %s!\n", palavra);
        atualizarRanking(nome, 10);    // Atualiza o ranking com os pontos do jogador
    } else {
        printf("\nVocê perdeu! A palavra era: %s\n", palavra);
    }
}

void menu() {
    const char* nomeArquivoRanking = "ranking.txt";    // Nome do arquivo de ranking
    carregarRanking(nomeArquivoRanking);    // Carrega o ranking do arquivo

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
                mostrarRanking();
                break;
            case 6:
                salvarRanking(nomeArquivoRanking);    // Salva o ranking no arquivo antes de sair
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);    // Loop do menu até que o usuário escolha sair
}

int main() {
    srand((unsigned int)time(NULL));    // Inicializa a semente do gerador de números aleatórios
    menu();    // Chama a função do menu principal
    return 0;    // Retorna 0 para indicar que o programa terminou com sucesso
}

