#include <stdio.h>

#define N 9

// The puzzle state
typedef struct 
{
    int cells[N][N];
    int fixed[N][N];
} GameBoard;

/*
 * -----------------------------------------------------------------------------
 * Function: display
 * Description: Prints the Sudoku grid to the console with formatting to 
 * visually separate the 3x3 subgrids.
 * -----------------------------------------------------------------------------
 */
void display(GameBoard *g)
{
    printf("\n    1 2 3   4 5 6   7 8 9\n");
    printf("  +-------+-------+-------+\n");
    for (int r = 0; r < N; r++)
    {
        printf("%d | ", r + 1);
        for (int c = 0; c < N; c++)
        {
            if (g->cells[r][c] == 0) printf(". ");
            else printf("%d ", g->cells[r][c]);

            if ((c + 1) % 3 == 0) printf("| ");
        }
        printf("\n");
        if ((r + 1) % 3 == 0) printf("  +-------+-------+-------+\n");
    }
}

/*
 * -----------------------------------------------------------------------------
 * Function: checkSafety
 * Description: Validates if placing a specific number at a given row and 
 * column is legal according to Sudoku rules. Checks the row, column, and 
 * the 3x3 subgrid.
 * -----------------------------------------------------------------------------
 */
int checkSafety(GameBoard *g, int r, int c, int val)
{
    // Scan Row & Col
    for (int k = 0; k < N; k++)
    {
        if (g->cells[r][k] == val) return 0;
        if (g->cells[k][c] == val) return 0;
    }

    // Scan 3x3 Box
    int boxR = (r / 3) * 3;
    int boxC = (c / 3) * 3;
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (g->cells[boxR + i][boxC + j] == val) return 0;
        }
    }
    return 1;
}

/*
 * -----------------------------------------------------------------------------
 * Function: isSolved
 * Description: Checks if the entire board is filled. Since move validation 
 * happens during input, a full board implies a solved puzzle.
 * -----------------------------------------------------------------------------
 */
int isSolved(GameBoard *g)
{
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            if (g->cells[r][c] == 0) return 0;
    return 1;
}

/*
 * -----------------------------------------------------------------------------
 * Function: main
 * Description: Initializes the puzzle with hardcoded data and runs the 
 * interactive game loop allowing the user to input moves.
 * -----------------------------------------------------------------------------
 */
int main()
{
    // Initializer using a flat layout for source data
    int startData[N][N] = {
        {5,3,0, 0,7,0, 0,0,0}, {6,0,0, 1,9,5, 0,0,0}, {0,9,8, 0,0,0, 0,6,0},
        {8,0,0, 0,6,0, 0,0,3}, {4,0,0, 8,0,3, 0,0,1}, {7,0,0, 0,2,0, 0,0,6},
        {0,6,0, 0,0,0, 2,8,0}, {0,0,0, 4,1,9, 0,0,5}, {0,0,0, 0,8,0, 0,7,9}
    };

    GameBoard game;

    // Setup board
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            game.cells[i][j] = startData[i][j];
            game.fixed[i][j] = (startData[i][j] != 0);
        }
    }

    int rInput, cInput, vInput;

    printf("=== TERMINAL SUDOKU ===\n");
    printf("Input Format: ROW COL NUMBER (e.g., 1 1 5)\n");
    printf("Enter '0 0 0' to exit.\n");

    while (1)
    {
        display(&game);
        
        if (isSolved(&game)) 
        {
            printf("\n>>> PUZZLE COMPLETE! Great job. <<<\n");
            break;
        }

        printf("Action > ");
        if (scanf("%d %d %d", &rInput, &cInput, &vInput) != 3)
        {
            printf("!! Bad Input. Expecting integers.\n");
            while(getchar() != '\n'); // clear buffer
            continue;
        }

        if (rInput == 0 && cInput == 0 && vInput == 0) 
        {
            printf("Bye.\n");
            break;
        }

        // Adjust 1-based index to 0-based
        int r = rInput - 1;
        int c = cInput - 1;

        if (r < 0 || r >= N || c < 0 || c >= N || vInput < 1 || vInput > 9)
        {
            printf("!! Out of bounds.\n");
            continue;
        }

        if (game.fixed[r][c])
        {
            printf("!! Locked cell.\n");
            continue;
        }

        if (!checkSafety(&game, r, c, vInput))
        {
            printf("!! Logic Error: Number exists in row, col, or box.\n");
            continue;
        }

        game.cells[r][c] = vInput;
        printf(">> Updated.\n");
    }

    return 0;
}