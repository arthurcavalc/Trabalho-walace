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

