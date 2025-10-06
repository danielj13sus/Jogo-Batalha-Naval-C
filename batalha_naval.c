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

    printf("Iniciando a preparação do tabuleiro de Batalha Naval...\n");

    if (!place_ship(board, 2, 2, SHIP_SIZE, 'H')) {
        fprintf(stderr, "Erro: Falha ao posicionar o navio horizontal!\n");
        return EXIT_FAILURE;
    }


    if (!place_ship(board, 5, 5, SHIP_SIZE, 'V')) {
        fprintf(stderr, "Erro: Falha ao posicionar o navio vertical!\n");
        return EXIT_FAILURE;
    }

    
    printf("\nTabuleiro com navios posicionados:\n");
    display_board(board);

    return EXIT_SUCCESS;
}

/**
 * @brief
 * @param board 
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
 * @param board
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
 * @param board
 * @param start_row 
 * @param start_col 
 * @param size 
 * @param orientation 
 * @return
 */
int place_ship(int board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_col, int size, char orientation) {

    if (orientation == 'H') {
        if (start_col + size > BOARD_SIZE || start_col < 0 || start_row < 0 || start_row >= BOARD_SIZE) {
            printf("Validação falhou: Navio horizontal fora dos limites.\n");
            return 0;
        }
    } else if (orientation == 'V') {
        if (start_row + size > BOARD_SIZE || start_row < 0 || start_col < 0 || start_col >= BOARD_SIZE) {
            printf("Validação falhou: Navio vertical fora dos limites.\n");
            return 0;
        }
    } else {
        return 0;
    }

    for (int i = 0; i < size; i++) {
        if (orientation == 'H') {
            if (board[start_row][start_col + i] != WATER) {
                printf("Validação falhou: Sobreposição de navios detectada.\n");
                return 0;
            }
        } else {
            if (board[start_row + i][start_col] != WATER) {
                printf("Validação falhou: Sobreposição de navios detectada.\n");
                return 0;
            }
        }
    }

    for (int i = 0; i < size; i++) {
        if (orientation == 'H') {
            board[start_row][start_col + i] = SHIP;
        } else {
            board[start_row + i][start_col] = SHIP;
        }
    }

    return 1;
}