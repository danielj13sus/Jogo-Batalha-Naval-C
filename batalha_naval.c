#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#define BOARD_SIZE 10
#define SHIP_SIZE 3
#define SKILL_MATRIX_SIZE 7 

typedef enum {
    WATER = 0,
    SHIP = 3,
    SKILL_AREA = 5
} BoardCell;

void initialize_board(int board[BOARD_SIZE][BOARD_SIZE]);
int place_ship(int board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_col, int size, char orientation);

void generate_cone_skill(int matrix[SKILL_MATRIX_SIZE][SKILL_MATRIX_SIZE], int size);
void generate_cross_skill(int matrix[SKILL_MATRIX_SIZE][SKILL_MATRIX_SIZE], int size);
void generate_octahedron_skill(int matrix[SKILL_MATRIX_SIZE][SKILL_MATRIX_SIZE], int size);
void apply_skill_on_board(int board[BOARD_SIZE][BOARD_SIZE], const int skill_matrix[SKILL_MATRIX_SIZE][SKILL_MATRIX_SIZE], int skill_size, int origin_r, int origin_c);

void display_board(const int board[BOARD_SIZE][BOARD_SIZE]);


/**
 * @brief
 */
int main(void) {
    int board[BOARD_SIZE][BOARD_SIZE];
    int skill_matrix[SKILL_MATRIX_SIZE][SKILL_MATRIX_SIZE];

    initialize_board(board);
    place_ship(board, 0, 0, SHIP_SIZE, 'H');
    place_ship(board, 2, 9, SHIP_SIZE, 'V');
    place_ship(board, 2, 1, SHIP_SIZE, 'D');
    place_ship(board, 1, 6, SHIP_SIZE, 'A');

    printf("Tabuleiro inicial com navios:\n");
    display_board(board);
    printf("\n");

    printf("Aplicando áreas de efeito das habilidades...\n");

    generate_cone_skill(skill_matrix, SKILL_MATRIX_SIZE);
    apply_skill_on_board(board, skill_matrix, SKILL_MATRIX_SIZE, 2, 5);

    generate_cross_skill(skill_matrix, SKILL_MATRIX_SIZE);
    apply_skill_on_board(board, skill_matrix, SKILL_MATRIX_SIZE, 7, 7);

    generate_octahedron_skill(skill_matrix, SKILL_MATRIX_SIZE);
    apply_skill_on_board(board, skill_matrix, SKILL_MATRIX_SIZE, 6, 1);

    printf("\nTabuleiro final com navios e áreas de habilidades aplicadas:\n");
    display_board(board);

    return EXIT_SUCCESS;
}

/**
 * @brief 
 */
void generate_cone_skill(int matrix[SKILL_MATRIX_SIZE][SKILL_MATRIX_SIZE], int size) {
    memset(matrix, 0, size * size * sizeof(int));
    int center_col = size / 2;
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (c >= center_col - r && c <= center_col + r) {
                matrix[r][c] = 1;
            }
        }
    }
}

/**
 * @brief
 */
void generate_cross_skill(int matrix[SKILL_MATRIX_SIZE][SKILL_MATRIX_SIZE], int size) {
    memset(matrix, 0, size * size * sizeof(int));
    int center = size / 2;
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (r == center || c == center) {
                matrix[r][c] = 1;
            }
        }
    }
}

/**
 * @brief 
 */
void generate_octahedron_skill(int matrix[SKILL_MATRIX_SIZE][SKILL_MATRIX_SIZE], int size) {
    memset(matrix, 0, size * size * sizeof(int));
    int center = size / 2;
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (abs(r - center) + abs(c - center) <= center) {
                matrix[r][c] = 1;
            }
        }
    }
}

/**
 * @brief 
 * @param origin_r 
 * @param origin_c 
 */
void apply_skill_on_board(int board[BOARD_SIZE][BOARD_SIZE], const int skill_matrix[SKILL_MATRIX_SIZE][SKILL_MATRIX_SIZE], int skill_size, int origin_r, int origin_c) {
    int skill_center = skill_size / 2;

    for (int sr = 0; sr < skill_size; sr++) {
        for (int sc = 0; sc < skill_size; sc++) {
            if (skill_matrix[sr][sc] == 1) {
                int board_r = origin_r + (sr - skill_center);
                int board_c = origin_c + (sc - skill_center);

                if (board_r >= 0 && board_r < BOARD_SIZE &&
                    board_c >= 0 && board_c < BOARD_SIZE) {
                    board[board_r][board_c] = SKILL_AREA;
                }
            }
        }
    }
}

void initialize_board(int board[BOARD_SIZE][BOARD_SIZE]) {
    memset(board, 0, BOARD_SIZE * BOARD_SIZE * sizeof(int));
}

void display_board(const int board[BOARD_SIZE][BOARD_SIZE]) {
    printf("   ");
    for(int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", i);
    }
    printf("\n--+--------------------\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d | ", i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            char symbol = '?';
            switch(board[i][j]) {
                case WATER:      symbol = '~'; break;
                case SHIP:       symbol = 'N'; break;
                case SKILL_AREA: symbol = '*'; break;
            }
            printf("%c ", symbol);
        }
        printf("\n");
    }
}

int place_ship(int board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_col, int size, char orientation) {
     if (start_row < 0 || start_col < 0) return 0;
    switch (orientation) {
        case 'H': if (start_col + size > BOARD_SIZE || start_row >= BOARD_SIZE) return 0; break;
        case 'V': if (start_row + size > BOARD_SIZE || start_col >= BOARD_SIZE) return 0; break;
        case 'D': if (start_row + size > BOARD_SIZE || start_col + size > BOARD_SIZE) return 0; break;
        case 'A': if (start_row + size > BOARD_SIZE || start_col - size < -1) return 0; break;
        default: return 0;
    }
    for (int i = 0; i < size; i++) {
        int r = start_row, c = start_col;
        switch (orientation) {
            case 'H': c += i; break; case 'V': r += i; break;
            case 'D': r += i; c += i; break; case 'A': r += i; c -= i; break;
        }
        if (board[r][c] != WATER) return 0;
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