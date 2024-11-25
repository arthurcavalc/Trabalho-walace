#include <stdio.h> // Biblioteca padrÃ£o de entrada/saÃ­da
#include <stdlib.h> // Biblioteca padrÃ£o para alocaÃ§Ã£o de memÃ³ria, controle de processos e outras operaÃ§Ãµes
#include <string.h> // Biblioteca para manipulaÃ§Ã£o de strings
#include <ctype.h>  // Biblioteca para manipulaÃ§Ã£o de caracteres
#include <time.h>  // Biblioteca para manipulaÃ§Ã£o de tempo

#define MAX_PALAVRAS 100
#define TAM_PALAVRA 50
#define MAX_JOGADORES 10

typedef struct {
    char palavra[TAM_PALAVRA]; // Armazena a palavra
    char dica[TAM_PALAVRA]; // Armazena a dica da palavra
} Palavra;

typedef struct {
    char nome[30];  // Armazena o nome do jogador
    int pontos; // Armazena os pontos do jogador
} Jogador;

Palavra palavras[MAX_PALAVRAS]; // Array para armazenar palavras
int totalPalavras = 0;  // Contador de palavras cadastradas

Jogador ranking[MAX_JOGADORES]; // Array para armazenar jogadores
int totalJogadores = 0;  // Contador de jogadores no ranking

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada
}

void converterMinusculas(char* texto) {
    for (int i = 0; texto[i]; i++) {
        texto[i] = tolower(texto[i]);  // Converte cada caractere de 'texto' para minÃºsculo
    }
}

void cadastrarPalavra() {
    if (totalPalavras >= MAX_PALAVRAS) {
        printf("Limite de palavras atingido!\n");
        return;
    }

    printf("Digite a palavra (sem espaços): ");
    scanf("%s", palavras[totalPalavras].palavra); // LÃª a palavra digitada
    limparBuffer();
    converterMinusculas(palavras[totalPalavras].palavra); // Converte a palavra para minÃºsculas

    printf("Digite a dica: ");  // LÃª a dica digitada
    fgets(palavras[totalPalavras].dica, TAM_PALAVRA, stdin);
    palavras[totalPalavras].dica[strcspn(palavras[totalPalavras].dica, "\n")] = '\0'; // Remove o caractere de nova linha

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
        printf("%d. %s - %d pontos\n", i + 1, ranking[i].nome, ranking[i].pontos); // Mostra o ranking dos jogadores
    }
}

void atualizarRanking(char nome[], int pontos) {
    for (int i = 0; i < totalJogadores; i++) {
        if (strcmp(ranking[i].nome, nome) == 0) {
            ranking[i].pontos += pontos;  // Atualiza os pontos do jogador se ele jÃ¡ estiver no ranking
            return;
        }
    }

    if (totalJogadores < MAX_JOGADORES) {
        strcpy(ranking[totalJogadores].nome, nome);
        ranking[totalJogadores].pontos = pontos; // Adiciona um novo jogador ao ranking
        totalJogadores++; 
    }
}

void jogarContraComputador() {
    char nome[30];
    printf("Digite seu nome: "); // LÃª o nome do jogador
    scanf("%s", nome);
    limparBuffer();

    char palavra[] = "wallace";  // Palavra definida pelo computador
    char dica[] = "Nome próprio"; // Define a dica da palavra
    int tamanho = strlen(palavra); // Calcula o tamanho da palavra

    char descoberta[TAM_PALAVRA];
    for (int i = 0; i < tamanho; i++) {
        descoberta[i] = '_'; // Inicializa a palavra descoberta com sublinhados
    }
    descoberta[tamanho] = '\0';

    int tentativas = 6; // Define o nÃºmero de tentativas
    int acertou = 0; // Inicializa o status de acerto

    while (tentativas > 0 && !acertou) {
        printf("\nPalavra: %s\n", descoberta);
        printf("Dica: %s\n", dica);
        printf("Tentativas restantes: %d\n", tentativas);
        printf("Digite uma letra: ");
        char letra;
        if (scanf(" %c", &letra) != 1) {
            printf("Entrada inválida! Digite apenas uma letra.\n");  // LÃª a entrada do jogador (letra ou palavra)
            limparBuffer();
            continue;
        }
        limparBuffer();
        letra = tolower(letra);

        int encontrou = 0;
        for (int i = 0; i < tamanho; i++) {
            if (palavra[i] == letra && descoberta[i] == '_') {
                descoberta[i] = palavra[i];   // Atualiza a palavra descoberta com a letra correta
                encontrou = 1;
            }
        }

        if (!encontrou) {
            tentativas--;
            printf("Letra incorreta!\n");
        } else {
            printf("Você acertou uma letra!\n");
        }

        if (strcmp(descoberta, palavra) == 0) {
            acertou = 1; // Se a palavra foi totalmente descoberta
        }
    }

    if (acertou) {
        printf("\nParabéns, você acertou a palavra: %s!\n", palavra);   // Atualiza o ranking com os pontos do jogador
        atualizarRanking(nome, 10);
    } else {
        printf("\nVocê perdeu! A palavra era: %s\n", palavra);
    }
}

void jogarMultiplayer() {
    char jogador1[30], jogador2[30];
    printf("Digite o nome do Jogador 1 (que escolherá a palavra): ");
    scanf("%s", jogador1);
    limparBuffer();

    printf("Digite o nome do Jogador 2 (que tentará adivinhar): ");
    scanf("%s", jogador2);
    limparBuffer();

    char palavra[TAM_PALAVRA];
    char dica[TAM_PALAVRA];
    printf("\n%s, digite a palavra para %s adivinhar: ", jogador1, jogador2);
    scanf("%s", palavra);
    limparBuffer();
    converterMinusculas(palavra);

    printf("%s, digite uma dica para a palavra: ", jogador1);
    fgets(dica, TAM_PALAVRA, stdin);
    dica[strcspn(dica, "\n")] = '\0';

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
        printf("Digite uma letra, %s: ", jogador2);
        char letra;
        if (scanf(" %c", &letra) != 1) {
            printf("Entrada inválida! Digite apenas uma letra.\n");
            limparBuffer();
            continue;
        }
        limparBuffer();
        letra = tolower(letra);

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

        if (strcmp(descoberta, palavra) == 0) {
            acertou = 1;
        }
    }

    if (acertou) {
        printf("\nParabéns, %s acertou a palavra: %s!\n", jogador2, palavra);
        atualizarRanking(jogador2, 10);
    } else {
        printf("\n%s perdeu! A palavra era: %s\n", jogador2, palavra);
    }
}

void menu() {
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
            case 2:
                jogarMultiplayer();
                break;
            case 3:
                cadastrarPalavra();
                break;
            case 4:
                mostrarRanking();
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5); // Loop do menu atÃ© que o usuÃ¡rio escolha sair
}

int main() {
    srand((unsigned int)time(NULL));  // Inicializa a semente do gerador de nÃºmeros aleatÃ³rios
    menu(); // Chama a funcao do menu principal
    return 0; // Retorna 0 para indicar que o programa terminou com sucesso
}
