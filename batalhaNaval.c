#include <stdio.h>

#define TAM 10
#define NAVIO 3
#define HABILIDADE 5

// Inicializa tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;
}

// Verifica se pode posicionar navio/habilidade
int podePosicionar(int tabuleiro[TAM][TAM], int linha, int coluna) {
    return linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM;
}

// Posicionamento dos navios
void posicionarHorizontal(int tabuleiro[TAM][TAM], int linha, int coluna) {
    for (int i = 0; i < NAVIO; i++)
        if (podePosicionar(tabuleiro, linha, coluna + i))
            tabuleiro[linha][coluna + i] = 3;
}

void posicionarVertical(int tabuleiro[TAM][TAM], int linha, int coluna) {
    for (int i = 0; i < NAVIO; i++)
        if (podePosicionar(tabuleiro, linha + i, coluna))
            tabuleiro[linha + i][coluna] = 3;
}

void posicionarDiagonalPrincipal(int tabuleiro[TAM][TAM], int linha, int coluna) {
    for (int i = 0; i < NAVIO; i++)
        if (podePosicionar(tabuleiro, linha + i, coluna + i))
            tabuleiro[linha + i][coluna + i] = 3;
}

void posicionarDiagonalSecundaria(int tabuleiro[TAM][TAM], int linha, int coluna) {
    for (int i = 0; i < NAVIO; i++)
        if (podePosicionar(tabuleiro, linha + i, coluna - i))
            tabuleiro[linha + i][coluna - i] = 3;
}

// Sobreposição da matriz de habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[5][5], int origemLinha, int origemColuna) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int linha = origemLinha + i - 2;
            int coluna = origemColuna + j - 2;
            if (podePosicionar(tabuleiro, linha, coluna) && habilidade[i][j] == 1) {
                if (tabuleiro[linha][coluna] == 0) // não sobrescreve navio
                    tabuleiro[linha][coluna] = HABILIDADE;
            }
        }
    }
}

// Cria matriz Cone (5x5) em forma de pirâmide apontando para baixo
void criarCone(int matriz[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            matriz[i][j] = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 2 - i; j <= 2 + i; j++) {
            if (j >= 0 && j < 5 && i < 3) // forma de cone com 3 linhas
                matriz[i][j] = 1;
        }
    }
}

// Cria matriz Cruz (5x5)
void criarCruz(int matriz[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            matriz[i][j] = (i == 2 || j == 2) ? 1 : 0;
}

// Cria matriz Octaedro (5x5)
void criarOctaedro(int matriz[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            matriz[i][j] = (abs(i - 2) + abs(j - 2) <= 2) ? 1 : 0;
}

// Exibe o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\nTabuleiro:\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 0)
                printf("~ "); // Água
            else if (tabuleiro[i][j] == 3)
                printf("N "); // Navio
            else if (tabuleiro[i][j] == 5)
                printf("* "); // Habilidade
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    int cone[5][5], cruz[5][5], octaedro[5][5];

    inicializarTabuleiro(tabuleiro);

    // Posiciona navios
    posicionarHorizontal(tabuleiro, 1, 1);
    posicionarVertical(tabuleiro, 5, 2);
    posicionarDiagonalPrincipal(tabuleiro, 0, 7);
    posicionarDiagonalSecundaria(tabuleiro, 6, 9);

    // Cria e aplica habilidades
    criarCone(cone);
    aplicarHabilidade(tabuleiro, cone, 3, 3); // origem no meio do tabuleiro

    criarCruz(cruz);
    aplicarHabilidade(tabuleiro, cruz, 5, 5);

    criarOctaedro(octaedro);
    aplicarHabilidade(tabuleiro, octaedro, 7, 4);

    exibirTabuleiro(tabuleiro);
    return 0;
}
