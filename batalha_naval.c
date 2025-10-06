#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 10
#define SHIP_SIZE 3

typedef enum {
    WATER = 0,
    SHIP = 3
} BoardCell;

void initialize_board(int board[BOARD_SIZE][BOARD_SIZE]);
void display_board(const int board[BOARD_SIZE][BOARD_SIZE]);
int place_ship(int board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_col, int size, char orientation);

/**
 * @brief
 */
int main(void) {
    int board[BOARD_SIZE][BOARD_SIZE];

    initialize_board(board);

    printf("Iniciando a preparação do tabuleiro de Batalha Naval (Nível Intermediário)...\n");

    if (!place_ship(board, 0, 0, SHIP_SIZE, 'H')) {
        fprintf(stderr, "Erro: Falha ao posicionar o navio Horizontal!\n");
        return EXIT_FAILURE;
    }

    if (!place_ship(board, 2, 9, SHIP_SIZE, 'V')) {
        fprintf(stderr, "Erro: Falha ao posicionar o navio Vertical!\n");
        return EXIT_FAILURE;
    }

    if (!place_ship(board, 2, 1, SHIP_SIZE, 'D')) {
        fprintf(stderr, "Erro: Falha ao posicionar o navio Diagonal!\n");
        return EXIT_FAILURE;
    }

    if (!place_ship(board, 1, 6, SHIP_SIZE, 'A')) {
        fprintf(stderr, "Erro: Falha ao posicionar o navio Anti-Diagonal!\n");
        return EXIT_FAILURE;
    }

    printf("\nTabuleiro com 4 navios posicionados:\n");
    display_board(board);

    return EXIT_SUCCESS;
}

/**
 * @brief 
 */
void initialize_board(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = WATER;
        }
    }
}

/**
 * @brief
 */
void display_board(const int board[BOARD_SIZE][BOARD_SIZE]) {
    printf("   ");
    for(int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", i);
    }
    printf("\n--+--------------------\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d | ", i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief 
 * @param orientation
 * @return 
 */
int place_ship(int board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_col, int size, char orientation) {

    if (start_row < 0 || start_col < 0) return 0; 

    switch (orientation) {
        case 'H':
            if (start_col + size > BOARD_SIZE || start_row >= BOARD_SIZE) return 0;
            break;
        case 'V':
            if (start_row + size > BOARD_SIZE || start_col >= BOARD_SIZE) return 0;
            break;
        case 'D':
            if (start_row + size > BOARD_SIZE || start_col + size > BOARD_SIZE) return 0;
            break;
        case 'A':
            if (start_row + size > BOARD_SIZE || start_col - size < -1) return 0;
            break;
        default:
            fprintf(stderr, "Orientação '%c' inválida.\n", orientation);
            return 0;
    }

    for (int i = 0; i < size; i++) {
        int r = start_row, c = start_col;
        switch (orientation) {
            case 'H': c += i; break;
            case 'V': r += i; break;
            case 'D': r += i; c += i; break;
            case 'A': r += i; c -= i; break;
        }
        if (board[r][c] != WATER) {
            fprintf(stderr, "Validação falhou: Sobreposição de navios detectada em (%d, %d).\n", r, c);
            return 0;
        }
    }

    for (int i = 0; i < size; i++) {
        switch (orientation) {
            case 'H': board[start_row][start_col + i] = SHIP; break;
            case 'V': board[start_row + i][start_col] = SHIP; break;
            case 'D': board[start_row + i][start_col + i] = SHIP; break;
            case 'A': board[start_row + i][start_col - i] = SHIP; break;
        }
    }

    return 1;
}