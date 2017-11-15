/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n", DIM_MIN, DIM_MIN, DIM_MAX,
            DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("For the win !!!!!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{

    // example:

    // for each row
    //     for each column
    //         set value for tile

    // int grid[0][0] = 8;
    // int grid[0][1] = 7;
    // ...
    // int grid[2][1] = 1;
    // int grid[2][2] = 0;

    // Easy peasy!

    // This starts with the biggest tile possible
    int bignum = d * d - 1;

    // This fills in the 2D array
    while (bignum >= 0)
    {
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {

                // This assigns number according to my example above.
                board[i][j] = bignum;
                bignum--;
            }
        }
    }

    // Swap 1 and 2 on even d boards (row d-1 and columns d-2 and d-3)
    if (d == 4 || d == 6 || d == 8)
    {


        // int temps = board[d - 1][d - 2];
        board[d - 1][d - 2] = 2;
        board[d - 1][d - 3] = 1;
    }

}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // Draw's the board so the user can see it
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == 0)
            {
                printf("__");
            }
            else
            {
                printf("%2i ", board[i][j]);
            }

        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{

    // User choice location needs to be saved
    int userchoiceR;
    int userchoiceC;

    // Zero location needs to be saved
    int zeroR;
    int zeroC;

    // Iterating through the board
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            if (board[r][c] == 0)
            {
                zeroR = r;
                zeroC = c;
            }
            if (board[r][c] == tile)
            {
                userchoiceR = r;
                userchoiceC = c;
            }
        }
    }

    // First check if we are in the same row...
    if (zeroR == userchoiceR)
    {
        // Now check if we are within one column
        if (zeroC - userchoiceC == 1 || zeroC - userchoiceC == -1)
        {
            // Now swap userchoice with 0
            board[zeroR][zeroC] = tile;
            board[userchoiceR][userchoiceC] = 0;
            return true;
        }
    }

    // Now swap C's and R's
    if (zeroC == userchoiceC)
    {
        // Now check if we are within one row
        if (zeroR - userchoiceR == 1 || zeroR - userchoiceR == -1)
        {
            // Now swap userchoice with 0
            board[zeroR][zeroC] = tile;
            board[userchoiceR][userchoiceC] = 0;
            return true;
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    int counter = 1;

    // Iterate over board to check values
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {

            // A win is determined by numbers in order so board[i][j] should equal counter at every step.
            if (board[i][j] != counter)
            {
                return false;
            }
            else if (board[i][j] == counter)
            {
                // If we actually get to the biggest number it means we have won.
                if (counter == d * d - 1)
                {
                    return true;
                }

                counter++;
            }
        }
    }

    return false;
}
