#include <stdint.h>
#include <stdio.h>

#define UNUSED(x) (void)(x)
#define STR_(x) #x
#define STR(x) STR_(x)

#define SUDOKU_ROW_SIZE 9
#define SUDOKU_COL_SIZE 9

typedef struct Sudoku_Board
{
    uint8_t cells[SUDOKU_ROW_SIZE * SUDOKU_COL_SIZE];
} Sudoku_Board;

Sudoku_Board solve(Sudoku_Board board)
{
    UNUSED(board);
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

bool boards_are_same(Sudoku_Board b1, Sudoku_Board b2)
{
    for (int64_t i = 0; i < (SUDOKU_COL_SIZE * SUDOKU_ROW_SIZE); ++i)
    {
        if (b1.cells[i] != b2.cells[i]) return false;
    }
    return true;
}

// clang-format off
#define TEST(board_unsolved, board_solved) \
do {\
    if (!boards_are_same(board_solved, solve(board_unsolved))) {printf("FAIL: %s \n", STR(board_unsolved));}\
    else {printf("PASS: %s\n", STR(board_unsolved));}\
} while (0)
// clang-format on

int main(void)
{
    // GOAL: main idea is, whenever you're solving the board and you have to make a guess,
    // instead of making a guess, spawn N threads for all N possibilities

    Sudoku_Board foo = (Sudoku_Board){
        .cells = {2, 0, 9, 0, 0, 4, 1, 0, 0,
                  0, 5, 6, 0, 0, 1, 0, 3, 0,
                  0, 0, 0, 6, 0, 0, 5, 7, 0,
                  0, 0, 0, 0, 0, 7, 0, 2, 3,
                  0, 0, 0, 2, 8, 6, 0, 0, 0,
                  5, 8, 0, 3, 0, 0, 0, 0, 0,
                  0, 2, 5, 0, 0, 3, 0, 0, 0,
                  0, 1, 0, 7, 0, 0, 2, 8, 0,
                  0, 0, 8, 4, 0, 0, 3, 0, 6},
    };
    print(foo);
    Sudoku_Board boo = solve(foo);
    print(boo);

    // https://www.chiark.greenend.org.uk/~sgtatham/puzzles/js/solo.html#3x3%23951663241816686
    Sudoku_Board trivial = (Sudoku_Board){
        .cells = {2, 0, 9, 0, 0, 4, 1, 0, 0,
                  0, 5, 6, 0, 0, 1, 0, 3, 0,
                  0, 0, 0, 6, 0, 0, 5, 7, 0,
                  0, 0, 0, 0, 0, 7, 0, 2, 3,
                  0, 0, 0, 2, 8, 6, 0, 0, 0,
                  5, 8, 0, 3, 0, 0, 0, 0, 0,
                  0, 2, 5, 0, 0, 3, 0, 0, 0,
                  0, 1, 0, 7, 0, 0, 2, 8, 0,
                  0, 0, 8, 4, 0, 0, 3, 0, 6},
    };
    Sudoku_Board trivial_solved = (Sudoku_Board){
        .cells = {2, 7, 9, 5, 3, 4, 1, 6, 8,
                  8, 5, 6, 9, 7, 1, 4, 3, 2,
                  3, 4, 1, 6, 2, 8, 5, 7, 9,
                  9, 6, 4, 1, 5, 7, 8, 2, 3,
                  1, 3, 7, 2, 8, 6, 9, 4, 5,
                  5, 8, 2, 3, 4, 9, 6, 1, 7,
                  4, 2, 5, 8, 6, 3, 7, 9, 1,
                  6, 1, 3, 7, 9, 5, 2, 8, 4,
                  7, 9, 8, 4, 1, 2, 3, 5, 6},
    };
    TEST(trivial, trivial_solved);

    // https://www.chiark.greenend.org.uk/~sgtatham/puzzles/js/solo.html#3x3db%23301316181552795
    Sudoku_Board basic = (Sudoku_Board){
        .cells = {0, 6, 0, 0, 0, 0, 0, 0, 7,
                  0, 0, 0, 0, 5, 0, 4, 2, 0,
                  0, 0, 0, 3, 8, 0, 0, 0, 0,
                  8, 0, 0, 5, 0, 0, 3, 0, 0,
                  7, 0, 4, 8, 0, 1, 5, 0, 2,
                  0, 0, 5, 0, 0, 7, 0, 0, 1,
                  0, 0, 0, 0, 4, 8, 0, 0, 0,
                  0, 7, 1, 0, 9, 0, 0, 0, 0,
                  2, 0, 0, 0, 0, 0, 0, 6, 0},
    };
    Sudoku_Board basic_solved = (Sudoku_Board){
        .cells = {5, 6, 2, 9, 1, 4, 8, 3, 7,
                  1, 8, 3, 7, 5, 6, 4, 2, 9,
                  4, 9, 7, 3, 8, 2, 1, 5, 6,
                  8, 1, 6, 5, 2, 9, 3, 7, 4,
                  7, 3, 4, 8, 6, 1, 5, 9, 2,
                  9, 2, 5, 4, 3, 7, 6, 8, 1,
                  6, 5, 9, 2, 4, 8, 7, 1, 3,
                  3, 7, 1, 6, 9, 5, 2, 4, 8,
                  2, 4, 8, 1, 7, 3, 9, 6, 5},
    };
    TEST(basic, basic_solved);

    // https://www.chiark.greenend.org.uk/~sgtatham/puzzles/js/solo.html#3x3di%23393367540336197
    Sudoku_Board intermediate = (Sudoku_Board){
        .cells = {0, 0, 0, 9, 0, 0, 4, 7, 0,
                  0, 0, 0, 0, 3, 0, 0, 5, 2,
                  0, 0, 5, 0, 0, 0, 0, 1, 0,
                  8, 0, 0, 0, 0, 0, 6, 0, 5,
                  0, 0, 0, 1, 0, 4, 0, 0, 0,
                  2, 0, 6, 0, 0, 0, 0, 0, 4,
                  0, 1, 0, 0, 0, 0, 8, 0, 0,
                  6, 8, 0, 0, 1, 0, 0, 0, 0,
                  0, 9, 7, 0, 0, 6, 0, 0, 0},
    };
    Sudoku_Board intermediate_solved = (Sudoku_Board){
        .cells = {1, 3, 8, 9, 5, 2, 4, 7, 6,
                  7, 6, 4, 8, 3, 1, 9, 5, 2,
                  9, 2, 5, 6, 4, 7, 3, 1, 8,
                  8, 4, 1, 7, 2, 3, 6, 9, 5,
                  3, 5, 9, 1, 6, 4, 2, 8, 7,
                  2, 7, 6, 5, 9, 8, 1, 3, 4,
                  5, 1, 2, 4, 7, 9, 8, 6, 3,
                  6, 8, 3, 2, 1, 5, 7, 4, 9,
                  4, 9, 7, 3, 8, 6, 5, 2, 1},
    };
    TEST(intermediate, intermediate_solved);

    // https://www.chiark.greenend.org.uk/~sgtatham/puzzles/js/solo.html#3x3da%23742908591016276
    Sudoku_Board advanced = (Sudoku_Board){
        .cells = {0, 0, 0, 0, 7, 9, 0, 0, 0,
                  0, 9, 0, 4, 8, 0, 2, 0, 0,
                  1, 0, 4, 0, 0, 0, 0, 0, 7,
                  5, 2, 0, 0, 4, 0, 8, 1, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 4, 8, 0, 5, 0, 0, 2, 3,
                  4, 0, 0, 0, 0, 0, 7, 0, 8,
                  0, 0, 5, 0, 6, 4, 0, 3, 0,
                  0, 0, 0, 3, 2, 0, 0, 0, 0},
    };
    Sudoku_Board advanced_solved = (Sudoku_Board){
        .cells = {2, 5, 6, 1, 7, 9, 3, 8, 4,
                  3, 9, 7, 4, 8, 6, 2, 5, 1,
                  1, 8, 4, 5, 3, 2, 6, 9, 7,
                  5, 2, 9, 7, 4, 3, 8, 1, 6,
                  6, 1, 3, 2, 9, 8, 4, 7, 5,
                  7, 4, 8, 6, 5, 1, 9, 2, 3,
                  4, 3, 2, 9, 1, 5, 7, 6, 8,
                  9, 7, 5, 8, 6, 4, 1, 3, 2,
                  8, 6, 1, 3, 2, 7, 5, 4, 9},
    };
    TEST(advanced, advanced_solved);

    // https://www.chiark.greenend.org.uk/~sgtatham/puzzles/js/solo.html#3x3de%23799494701579513
    Sudoku_Board extreme = (Sudoku_Board){
        .cells = {0, 0, 0, 4, 0, 1, 8, 0, 0,
                  0, 4, 3, 0, 0, 2, 0, 0, 9,
                  9, 0, 1, 0, 0, 0, 0, 0, 2,
                  4, 2, 9, 0, 3, 0, 1, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 7, 0, 5, 0, 9, 2, 6,
                  7, 0, 0, 0, 0, 0, 6, 0, 8,
                  6, 0, 0, 3, 0, 0, 2, 9, 0,
                  0, 0, 4, 2, 0, 6, 0, 0, 0},
    };
    Sudoku_Board extreme_solved = (Sudoku_Board){
        .cells = {2, 7, 5, 4, 9, 1, 8, 6, 3,
                  8, 4, 3, 5, 6, 2, 7, 1, 9,
                  9, 6, 1, 8, 7, 3, 4, 5, 2,
                  4, 2, 9, 6, 3, 8, 1, 7, 5,
                  5, 1, 6, 7, 2, 9, 3, 8, 4,
                  3, 8, 7, 1, 5, 4, 9, 2, 6,
                  7, 3, 2, 9, 1, 5, 6, 4, 8,
                  6, 5, 8, 3, 4, 7, 2, 9, 1,
                  1, 9, 4, 2, 8, 6, 5, 3, 7},
    };
    TEST(extreme, extreme_solved);

    // https://www.chiark.greenend.org.uk/~sgtatham/puzzles/js/solo.html#3x3du%23300835381977315
    Sudoku_Board unreasonable = (Sudoku_Board){
        .cells = {0, 9, 0, 0, 0, 4, 0, 0, 0,
                  1, 0, 4, 0, 9, 0, 0, 0, 0,
                  0, 6, 8, 1, 0, 0, 0, 0, 3,
                  4, 2, 0, 6, 0, 0, 0, 9, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 7, 0, 0, 0, 5, 0, 3, 2,
                  7, 0, 0, 0, 0, 9, 3, 2, 0,
                  0, 0, 0, 0, 1, 0, 4, 0, 7,
                  0, 0, 0, 8, 0, 0, 0, 1, 0},
    };
    Sudoku_Board unreasonable_solved = (Sudoku_Board){
        .cells = {2, 9, 7, 3, 6, 4, 8, 5, 1,
                  1, 3, 4, 5, 9, 8, 2, 7, 6,
                  5, 6, 8, 1, 2, 7, 9, 4, 3,
                  4, 2, 3, 6, 8, 1, 7, 9, 5,
                  6, 5, 9, 7, 3, 2, 1, 8, 4,
                  8, 7, 1, 9, 4, 5, 6, 3, 2,
                  7, 1, 6, 4, 5, 9, 3, 2, 8,
                  9, 8, 5, 2, 1, 3, 4, 6, 7,
                  3, 4, 2, 8, 7, 6, 5, 1, 9},
    };
    TEST(unreasonable, unreasonable_solved);

    return 0;
}