#include <stdio.h>  // Biblioteca para entrada e saída
#include <stdlib.h> // Biblioteca para funções padrão (ex.: malloc, free)
#include <string.h> // Biblioteca para manipulação de strings
#include <ctype.h>  // Biblioteca para funções de manipulação de caracteres (ex.: tolower)
#include <time.h>   // Biblioteca para manipular tempo (ex.: gerar números aleatórios)

// Definições de constantes
#define MAX_PALAVRAS 100  // Máximo de palavras que podem ser cadastradas
#define TAM_PALAVRA 50    // Tamanho máximo de cada palavra e dica
#define MAX_JOGADORES 10  // Máximo de jogadores no ranking

// Estrutura para armazenar uma palavra e sua dica
typedef struct {
    char palavra[TAM_PALAVRA];
    char dica[TAM_PALAVRA];
} Palavra;

// Estrutura para armazenar dados de um jogador no ranking
typedef struct {
    char nome[30];
    int pontos;
} Jogador;

// Variáveis globais
Palavra palavras[MAX_PALAVRAS]; // Lista de palavras cadastradas
int totalPalavras = 0;          // Quantidade atual de palavras cadastradas

Jogador ranking[MAX_JOGADORES]; // Ranking dos jogadores
int totalJogadores = 0;         // Quantidade atual de jogadores no ranking

// Função para limpar o buffer de entrada (evita problemas com `scanf` e `fgets`)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Converte uma string para minúsculas
void converterMinusculas(char* texto) {
    for (int i = 0; texto[i]; i++) {
        texto[i] = tolower(texto[i]); // Converte cada caractere para minúsculo
    }
}

// Salva o ranking atual em um arquivo
void salvarRanking(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w"); // Abre o arquivo em modo de escrita
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar o ranking!\n");
        return;
    }

    fprintf(arquivo, "%d\n", totalJogadores); // Salva o número de jogadores
    for (int i = 0; i < totalJogadores; i++) {
        fprintf(arquivo, "%s %d\n", ranking[i].nome, ranking[i].pontos); // Salva nome e pontos de cada jogador
    }

    fclose(arquivo); // Fecha o arquivo
    printf("Ranking salvo com sucesso no arquivo '%s'.\n", nomeArquivo);
}

// Carrega o ranking de um arquivo, se existir
void carregarRanking(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r"); // Abre o arquivo em modo de leitura
    if (arquivo == NULL) {
        printf("Arquivo de ranking não encontrado. Um novo ranking será criado.\n");
        return;
    }

    fscanf(arquivo, "%d\n", &totalJogadores); // Lê o número de jogadores
    for (int i = 0; i < totalJogadores; i++) {
        fscanf(arquivo, "%s %d\n", ranking[i].nome, &ranking[i].pontos); // Lê nome e pontos de cada jogador
    }

    fclose(arquivo); // Fecha o arquivo
    printf("Ranking carregado com sucesso do arquivo '%s'.\n", nomeArquivo);
}

// Cadastra uma nova palavra com sua dica
void cadastrarPalavra() {
    if (totalPalavras >= MAX_PALAVRAS) { // Verifica se o limite de palavras foi atingido
        printf("Limite de palavras atingido!\n");
        return;
    }

    printf("Digite a palavra (sem espaços): ");
    scanf("%s", palavras[totalPalavras].palavra); // Lê a palavra
    limparBuffer();
    converterMinusculas(palavras[totalPalavras].palavra); // Converte a palavra para minúsculas

    printf("Digite a dica: ");
    fgets(palavras[totalPalavras].dica, TAM_PALAVRA, stdin); // Lê a dica
    palavras[totalPalavras].dica[strcspn(palavras[totalPalavras].dica, "\n")] = '\0'; // Remove o '\n' do final

    totalPalavras++; // Incrementa o número total de palavras
    printf("Palavra cadastrada com sucesso!\n");
}

// Mostra o ranking dos jogadores
void mostrarRanking() {
    printf("\n=== Ranking ===\n");
    if (totalJogadores == 0) { // Verifica se o ranking está vazio
        printf("Nenhum jogador no ranking.\n");
        return;
    }

    for (int i = 0; i < totalJogadores; i++) { // Exibe cada jogador e seus pontos
        printf("%d. %s - %d pontos\n", i + 1, ranking[i].nome, ranking[i].pontos);
    }
}

// Atualiza o ranking, adicionando pontos para um jogador
void atualizarRanking(char nome[], int pontos) {
    for (int i = 0; i < totalJogadores; i++) {
        if (strcmp(ranking[i].nome, nome) == 0) { // Se o jogador já existe, adiciona pontos
            ranking[i].pontos += pontos;
            return;
        }
    }

    if (totalJogadores < MAX_JOGADORES) { // Adiciona um novo jogador se houver espaço no ranking
        strcpy(ranking[totalJogadores].nome, nome);
        ranking[totalJogadores].pontos = pontos;
        totalJogadores++;
    }
}

// Função para jogar contra o computador
void jogarContraComputador() {
    char nome[30];
    printf("Digite seu nome: ");
    scanf("%s", nome); // Lê o nome do jogador
    limparBuffer();

    // Define a palavra e a dica (em um jogo completo, poderia ser aleatória)
    char palavra[] = "wallace"; 
    char dica[] = "Nome próprio";
    int tamanho = strlen(palavra);

    char descoberta[TAM_PALAVRA]; // Inicia a palavra com '_'
    for (int i = 0; i < tamanho; i++) {
        descoberta[i] = '_';
    }
    descoberta[tamanho] = '\0';

    int tentativas = 6; // Número de tentativas do jogador
    int acertou = 0;

    while (tentativas > 0 && !acertou) { // Laço principal do jogo
        printf("\nPalavra: %s\n", descoberta);
        printf("Dica: %s\n", dica);
        printf("Tentativas restantes: %d\n", tentativas);
        printf("Digite uma letra ou tente adivinhar a palavra: ");

        char entrada[TAM_PALAVRA];
        scanf("%s", entrada);
        limparBuffer();
        converterMinusculas(entrada);

        if (strlen(entrada) > 1) { // Se o jogador tenta adivinhar a palavra inteira
            if (strcmp(entrada, palavra) == 0) {
                acertou = 1;
                strcpy(descoberta, palavra);
            } else {
                tentativas--;
                printf("Palavra incorreta!\n");
            }
        } else { // Se o jogador tenta uma letra
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

        if (strcmp(descoberta, palavra) == 0) { // Verifica se a palavra foi descoberta
            acertou = 1;
        }
    }

    if (acertou) {
        printf("\nParabéns, você acertou a palavra: %s!\n", palavra);
        atualizarRanking(nome, 10); // Adiciona pontos ao jogador
    } else {
        printf("\nVocê perdeu! A palavra era: %s\n", palavra);
    }
}

// Menu principal do jogo
void menu() {
    const char* nomeArquivoRanking = "ranking.txt"; // Nome do arquivo de ranking
    carregarRanking(nomeArquivoRanking); // Carrega o ranking do arquivo

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
                salvarRanking(nomeArquivoRanking); // Salva o ranking antes de sair
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);
}

int main() {
    srand((unsigned int)time(NULL)); // Inicializa o gerador de números aleatórios
    menu(); // Chama o menu principal
    return 0;
}
