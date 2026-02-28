#include <stdint.h>
#include <stdio.h>

typedef struct Node Node;
struct Node
{

    Node *prev;
    Node *next;
};

#define SUDOKU_ROW_SIZE 8
#define SUDOKU_COL_SIZE 8
#define SUDOKU_BOARD_SIZE (SUDOKU_ROW_SIZE * SUDOKU_COL_SIZE)

typedef struct Sudoku_Board
{
    uint8_t cells[8 * 8];
} Sudoku_Board;

Sudoku_Board solve(Sudoku_Board board)
{
    (void)board;
    return (Sudoku_Board){0};
}

void print(Sudoku_Board board)
{
    for (int64_t y = 0; y < SUDOKU_ROW_SIZE; ++y)
    {
        for (int64_t x = 0; x < SUDOKU_COL_SIZE; ++x)
        {
            printf("%u, ", board.cells[y * SUDOKU_ROW_SIZE + x]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(void)
{
    Sudoku_Board input_board = {0};
    Sudoku_Board solved_board = solve(input_board);
    print(solved_board);
    // GOAL: main idea is, whenever you're solving the board and you have to make a guess,
    // instead of making a guess, spawn N threads for all N possibilities
    return 0;
}