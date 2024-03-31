/**
 * @brief Program to play Super Tic-Tac-Toe, a variation of tic-tac-toe where players need to complete a grid in order to claim a square of the main grid ('super grid')
 *
 * @author Powan
 * @version 2.1.3
 */

#include "./includes.h"

/****************************************************/
/****************************************************/
/***|         Prototypes Initialisation          |***/
/****************************************************/
/****************************************************/

/* Miscellaneous */

void errors(int);
void clearTerminal();
void loading_animation();
void mainMenu();
void rules();
void namePlayer(char *);
void generateXboxName(char *ptrGamertag);

/* Super Grid & Grids related stuff */

void initSuperGrid(struct Grid superGrid[ROW][COLUMN]);
int gridComplete(struct Grid superGrid[ROW][COLUMN], char);
bool isGridDraw(struct Grid superGrid[ROW][COLUMN], char letter);
int superGridComplete(struct Grid superGrid[ROW][COLUMN]);
void PrintGrid(struct Grid superGrid[ROW][COLUMN]);

/* Inputs */

void inputWhichGrid(char *);
void inputWhichCell(int *);
char takeTurn(struct Grid superGrid[ROW][COLUMN], int, char, int *, int *);

/* Bots */

int setDifficulty();
char easyBotTurn(struct Grid superGrid[ROW][COLUMN], char letter, int *ptrBotRow, int *ptrBotCol);
char mediumBotTurn(struct Grid superGrid[ROW][COLUMN], char letter, int *ptrBotRow, int *ptrBotCol);
char hardBotTurn(struct Grid superGrid[ROW][COLUMN], char letter, int *ptrBotRow, int *ptrBotCol);

/* Main Game Funcitons */

void match1P();
void match2P();
void mainScreen();

/****************************************************/
/****************************************************/
/**************|         MAIN         |**************/
/****************************************************/
/****************************************************/

int main()
{
    mainScreen();

    return EXIT_SUCCESS;
}

/****************************************************/
/****************************************************/
/*****|         Prototypes definitions         |*****/
/****************************************************/
/****************************************************/

/* Miscellaneous */

/**
 * @brief Prints the error messages.
 *
 * @details Prints the error messages depending on the error code.
 *
 * @param code Error code, int.
 */
void errors(int code)
{
    switch (code)
    {
    case DEBUG: /* Prints a message to know if a set checkpoint has been reached or if the code is broken there */
        printf(RED "Successfully reached checkpoint.\n" RESET);
        break;

    case INPUT_TOO_LONG:
        printf(RED "Error! " RESET "The " MAGENTA "input" RESET " is " MAGENTA "too long" RESET ".\nTry again: \n");
        break;

    case NON_INT_INPUT:
        printf(RED "Error! " RESET "Please " MAGENTA "input" RESET " an " MAGENTA "integer" RESET ".\nTry again: \n");
        break;

    case INT_OUT_OF_RANGE:
        printf(RED "Error! " RESET "Please " MAGENTA "input" RESET " an integer " MAGENTA "between 1 & 3" RESET ".\nTry again: \n");
        break;

    case NON_CHAR_INPUT:
        printf(RED "Error! " RESET "Please " MAGENTA "input" RESET " a " MAGENTA "character" RESET ".\nTry again: \n");
        break;

    case CHAR_INPUT_UNRECONIZED:
        printf(RED "Error! " RESET "Please " MAGENTA "input" RESET " a character included " MAGENTA "between A & I" RESET ".\nTry again: \n");
        break;

    case CELL_TAKEN:
        printf(RED "Error! " RESET "That " MAGENTA "cell" RESET " has already been " MAGENTA "claimed" RESET ".\nTry again: \n");
        break;

    case GRID_TAKEN:
        printf(RED "Error! " RESET "That " MAGENTA "grid" RESET " has already been " MAGENTA "claimed" RESET ".\nTry again: \n");
        break;

    case PLAYER_ID: /* If this error is reached, the program can't continue without errors, so exits it before crashing. */
        printf(RED "There was an error with the players' IDs... Exiting");
        loading_animation();
        exit(EXIT_FAILURE);
        break;

    case UNEXPECTED: /* If this error is reached, a part of the code didn't run properly and a condition wasn't completed even though it should have been (Ex in giveMemeName(){}). */
        printf(RED "Unexpected error... Exiting");
        loading_animation();
        exit(EXIT_FAILURE);
        break;

    default: /* This error is not supposed to happen, so exits the program. */
        printf(RED "Error within the errors() function... Exiting");
        loading_animation();
        exit(EXIT_FAILURE);
        break;
    }
}

/**
 * @brief Clears the terminal screen.
 *
 * @details Clears the terminal screen using "\033[2J\033[1;1H".
 */
void clearTerminal()
{
    printf(CLEAR_TERMINAL);
}

/**
 * @brief Prints a little loading animation.
 *
 * @details Prints a "." every second, 3 times.
 */
void loading_animation()
{
    /* Cuz it looks cool 😎 */
    for (int _ = 0; _ < 3; _++)
    {
        fflush(stdout);
        sleep(1);
        printf(".");
    }
    fflush(stdout);
    sleep(1);
    printf("\n");
}

/**
 * @brief Prints the initial mainMenu message.
 *
 * @details Prints the main menu message and asks the user to choose one of the options.
 */
void mainMenu()
{
    clearTerminal();
    printf(BLUE " ____  _  _  ____  ____  ____    ____  __  ___     ____  __    ___     ____  __  ____ \n");
    printf("/ ___)/ )( \\(  _ \\(  __)(  _ \\  (_  _)(  )/ __)___(_  _)/  \\  / __)___(_  _)/  \\(  __)\n");
    printf("\\___ \\) \\/ ( ) __/ ) _)  )   /    )(   )(( (__(___) )( /    \\( (__(___) )( (    )) _) \n");
    printf("(____/\\____/(__)  (____)(__\\_)   (__) (__)\\___)    (__)\\_/\\_/ \\___)    (__) \\__/(____)\n");
    printf("                                                                   By @powan.5(Discord)\n");
    printf("\n");
    printf("\t\tWELCOME!\n");
    printf("\n");
    printf(RED "\t[1]  Rules\n" RESET);
    printf(RED "\t[2]  Start a game (1P)\n" RESET);
    printf(RED "\t[3]  Start a match (2P)\n" RESET);
    printf(RED "\t[0]  Exit\n" RESET);
    printf("\n");
}

/**
 * @brief Prints the rules of the Super Tic-Tac-Toe.
 *
 * @details The rules are the same as the original Tic-Tac-Toe, but with a new grid size comming with some new rules.
 */
void rules()
{
    clearTerminal();
    printf(BLUE " ____  _  _  ____  ____  ____    ____  __  ___     ____  __    ___     ____  __  ____ \n");
    printf("/ ___)/ )( \\(  _ \\(  __)(  _ \\  (_  _)(  )/ __)___(_  _)/  \\  / __)___(_  _)/  \\(  __)\n");
    printf("\\___ \\) \\/ ( ) __/ ) _)  )   /    )(   )(( (__(___) )( /    \\( (__(___) )( (    )) _) \n");
    printf("(____/\\____/(__)  (____)(__\\_)   (__) (__)\\___)    (__)\\_/\\_/ \\___)    (__) \\__/(____)\n");
    printf("                                                                   By @powan.5(Discord)\n");
    printf("\n");
    printf("                                                                                      \n");
    printf(RED "                                        RULES                                        \n" RESET);
    printf("\n");
    printf("The game starts with a move in any of the nine 3x3 grids, chosen by Player 1. (From A to I)\n");
    printf("\n");
    printf("The opponent must play in the corresponding cell of the larger grid, \n");
    printf("based off of in which cell of the small grid the previous player played in.\n");
    printf("\n");
    printf("Winning a small grid awards that grid to the player and determines the opponent's next move.\n");
    printf("\n");
    printf("To win the game, you have to win three small grids in a row horizontally, vertically, or diagonally.\n");
    printf("\n");
    printf("If a player is meant to play in an already won smaller grid,\n");
    printf("they can choose any open cell from any of the available grids.\n");
    printf("\n");
    printf("The game continues until a player wins the larger grid.\n");
    printf("\n");
    printf("If one of the small grid is full but is a draw,\n");
    printf("said grid will be reseted after a turn for players to continue playing.\n");
    printf("\n");
    printf(GREEN "[Press ENTER to continue] ");
    while (getchar() != '\n')
        ;
}

/**
 * @brief Asks the User for a CHAR input, for his pseudo.
 *
 * @details The pseudo can't be longer than 20 characters, if the intput is '*', a random pseudo will be given to the player.
 *
 * @param ptrInput Pointer of the input variable.
 *
 * @see generateXBoxName()
 */
void namePlayer(char *ptrInput)
{
    bool condition = false;

    while (getchar() != '\n')
        ;

    do
    {
        char input[20] = "";

        fgets(input, sizeof(input), stdin);

        /*-- Makes sures the input is not longer than 20 --*/

        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n')
        {
            input[strlen(input) - 1] = '\0';
        }
        else
        {
            errors(INPUT_TOO_LONG);
            while (getchar() != '\n')
                ;
            continue;
        }

        /*-- Gives the pseudo for the player --*/

        if (input[0] == '*') /* Gets a random pseudo to the player if he so desires */
        {
            gamertag name;
            srand(time(NULL));

            int method = rand() % 3;

            switch (method)
            {
            case 0:
                strcpy(name, consonant[(rand() % 19)]);
                for (int nb = 0; nb < 2; nb++)
                {
                    strcat(name, vowels[(rand() % 5)]);
                    strcat(name, consonant[(rand() % 19)]);
                }

                name[0] = toupper(name[0]);

                strcpy(ptrInput, name);
                condition = true;
                break;

            case 1:
                strcpy(name, vowels[(rand() % 5)]);
                for (int nb = 0; nb < 2; nb++)
                {
                    strcat(name, consonant[(rand() % 19)]);
                    strcat(name, vowels[(rand() % 5)]);
                }

                name[0] = toupper(name[0]);

                strcpy(ptrInput, name);
                condition = true;
                break;

            case 2:;
                gamertag xboxGamertag;
                generateXboxName(xboxGamertag);
                strcpy(ptrInput, xboxGamertag);
                condition = true;
                break;

            default:
                errors(UNEXPECTED);
                break;
            }

            if ((rand() % 100) == 69) /* 1/100 chance of giving a meme name cuz ahah funni :) */
            {
                srand(time(NULL));
                strcpy(ptrInput, memeNames[(rand() % nbOfMemeNames)]);
            }
        }

        else /* Gives the chosen pseudo otherwise */
        {
            strcpy(ptrInput, input);
            condition = true;
        }
    } while (!condition);
}

/**
 * @brief Generate an Xbox-like gamertag.
 *
 * @details Generate an Xbox-like gamertag with a random flair, prefix, main name and flair again.
 *
 * @returns CHAR*, the generated gamertag.
 */
void generateXboxName(char *ptrGamertag)
{
    gamertag gamertag;
    srand(time(NULL));
    int randomFlair = (rand() % nbFlaires);

    char flair1[3];
    char prefix[20];
    char mainName[20];
    char flair2[3];
    strcpy(flair1, Flairs[randomFlair][0]);
    strcpy(prefix, Prefixes[(rand() % nbPrefixes)]);
    strcpy(mainName, MainName[(rand() % nbMainName)]);
    strcpy(flair2, Flairs[randomFlair][1]);

    strcat(gamertag, flair1);
    strcat(gamertag, prefix);
    strcat(gamertag, mainName);
    strcat(gamertag, flair2);

    strcpy(ptrGamertag, gamertag);
}

/* Super Grid & Grids related stuff */

/**
 * @brief Initialise 'the super grid's grids values with '.'.
 *
 * @details Initialise 'the super grid's grids values with '.'.
 *
 * @param superGrid Game's grid.
 */
void initSuperGrid(struct Grid superGrid[ROW][COLUMN])
{
    for (int row = 0; row < ROW; row++)
    {
        for (int col = 0; col < COLUMN; col++)
        {
            for (int gridRow = 0; gridRow < ROW; gridRow++)
            {
                for (int gridCol = 0; gridCol < COLUMN; gridCol++)
                {
                    superGrid[row][col].grid[gridRow][gridCol] = '.';
                }
            }
        }
    }
}

/**
 * @brief Checks if the given grid inside 'super grid' is complete.
 *
 * @details Checks if the given grid inside'super grid' is complete. If so, it returns the player/bot who won the grid.
 *
 * @param superGrid Game's grid.
 * @param letter Letter of the grid to check, gives the index of said grid.
 * @returns 1 if Player1 has finished it, 2 if Player2 did, DEFAULT otherwise.
 */
int gridComplete(struct Grid superGrid[ROW][COLUMN], char letter)
{
    int p1_diagL2R, p1_diagR2L, p1_row, p1_col;
    int p2_diagL2R, p2_diagR2L, p2_row, p2_col;

    for (int row = 0; row < ROW; row++)
    {
        for (int col = 0; col < COLUMN; col++)
        {

            /* Finds the index of the current playing grid inside of 'super grid' */

            if (letter == LETTERS[row][col])
            {
                /*-- Checks the diagonals --*/

                p1_diagL2R = 0, p1_diagR2L = 0, p2_diagL2R = 0, p2_diagR2L = 0;

                for (int diag = 0, invDiag = 2; diag < DIAG; diag++, invDiag--)
                {
                    /* Checks the diagonal from (0,0) to (2,2) for if P1 won */

                    if (superGrid[row][col].grid[diag][diag] == 'X')
                    {
                        p1_diagL2R++;
                    }
                    else

                        /* Checks the diagonal from (0,0) to (2,2) for if P2 won */

                        if (superGrid[row][col].grid[diag][diag] == 'O')
                        {
                            p2_diagL2R++;
                        }

                    /* Checks the diagonal from (0,2) to (2,0) for if P1 won */

                    if (superGrid[row][col].grid[diag][invDiag] == 'X')
                    {
                        p1_diagR2L++;
                    }
                    else

                        /* Checks the diagonal from (0,2) to (2,0) for if P2 won */

                        if (superGrid[row][col].grid[diag][invDiag] == 'O')
                        {
                            p2_diagR2L++;
                        }
                }

                /*-- Checks the lines (Rows and Columns) --*/

                for (int gridRow = 0; gridRow < ROW; gridRow++)
                {
                    p1_row = 0, p2_row = 0;
                    p1_col = 0, p2_col = 0;

                    for (int gridCol = 0; gridCol < COLUMN; gridCol++)
                    {

                        /* Checks each rows for if P1 won */

                        if (superGrid[row][col].grid[gridRow][gridCol] == 'X')
                        {
                            p1_row++;
                        }
                        else

                            /* Checks each rows for if P2 won */

                            if (superGrid[row][col].grid[gridRow][gridCol] == 'O')
                            {
                                p2_row++;
                            }

                        /* Checks each columns for if P1 won */

                        if (superGrid[row][col].grid[gridCol][gridRow] == 'X')
                        {
                            p1_col++;
                        }
                        else

                            /* Checks each columns for if P2 won */

                            if (superGrid[row][col].grid[gridCol][gridRow] == 'O')
                            {
                                p2_col++;
                            }

                        /*-- Checks if a player won --*/

                        if (p1_diagR2L == 3 || p1_diagL2R == 3 || p1_row == 3 || p1_col == 3)
                        {
                            return P1;
                        }
                        else

                            if (p2_diagR2L == 3 || p2_diagL2R == 3 || p2_row == 3 || p2_col == 3)
                        {
                            return P2;
                        }
                    }
                }
            }
        }
    }
    return DEFAULT;
}

/**
 * @brief Checks if the given grid inside 'super grid' is full but is a draw.
 *
 * @details If a grid is full but is a draw, resets the grid so the game is forced to be won by someone.
 *
 * @param superGrid Game's grid.
 * @param letter Letter of the grid to check, gives the index of said grid.
 * @returns bool, true if the grid is a draw, false otherwise.
 */
bool isGridDraw(struct Grid superGrid[ROW][COLUMN], char letter)
{
    for (int row = 0; row < ROW; row++)
    {
        for (int col = 0; col < COLUMN; col++)
        {
            /* Finds the index of the current playing grid inside of 'super grid' */
            if (letter == LETTERS[row][col])
            {
                for (int gridRow = 0; gridRow < ROW; gridRow++)
                {
                    for (int gridCol = 0; gridCol < COLUMN; gridCol++)
                    {
                        if (superGrid[row][col].grid[gridRow][gridCol] == '.')
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

/**
 * @brief Checks if the 'super grid' is completed, so if the game finished.
 *
 * @details Checks if the 'super grid' is completed, so if the game finished, and returns the winner. Based on the gridComplete() function.
 *
 * @param superGrid Game's grid.
 * @returns 1 if Player1 has won, 2 if Player2 did, 0 otherwise.
 *
 * @see gridComplete()
 */
int superGridComplete(struct Grid superGrid[ROW][COLUMN])
{
    int p1_superDiagL2R, p1_superDiagR2L, p1_superRow, p1_superCol;
    int p2_superDiagL2R, p2_superDiagR2L, p2_superRow, p2_superCol;

    for (int row = 0; row < ROW; row++)
    {
        p1_superRow = 0, p2_superRow = 0;
        p1_superCol = 0, p2_superCol = 0;

        for (int col = 0; col < COLUMN; col++)
        {
            p1_superDiagL2R = 0, p1_superDiagR2L = 0, p2_superDiagL2R = 0, p2_superDiagR2L = 0;

            /*-- Checks the diagonals --*/
            for (int diag = 0, invDiag = 2; diag < DIAG; diag++, invDiag--)
            {
                /* Checks the diagonal from (0,0) to (2,2) for if P1 won */

                if (gridComplete(superGrid, LETTERS[diag][diag]) == P1)
                {
                    p1_superDiagL2R++;
                }
                else

                    /* Checks the diagonal from (0,0) to (2,2) for if P2 won */

                    if (gridComplete(superGrid, LETTERS[diag][diag]) == P2)
                    {
                        p2_superDiagL2R++;
                    }

                /* Checks the diagonal from (0,2) to (2,0) for if P1 won */

                if (gridComplete(superGrid, LETTERS[diag][invDiag]) == P1)
                {
                    p1_superDiagR2L++;
                }
                else

                    /* Checks the diagonal from (0,2) to (2,0) for if P2 won */

                    if (gridComplete(superGrid, LETTERS[diag][invDiag]) == P2)
                    {
                        p2_superDiagR2L++;
                    }
            }

            /*-- Checks the lines (Rows and Columns) --*/

            /* Checks each rows for if P1 won */

            if (gridComplete(superGrid, LETTERS[row][col]) == P1)
            {
                p1_superRow++;
            }
            else

                /* Checks each rows for if P2 won */

                if (gridComplete(superGrid, LETTERS[row][col]) == P2)
                {
                    p2_superRow++;
                }

            /* Checks each columns for if P1 won */

            if (gridComplete(superGrid, LETTERS[col][row]) == P1)
            {
                p1_superCol++;
            }
            else

                /* Checks each columns for if P2 won */

                if (gridComplete(superGrid, LETTERS[col][row]) == P2)
                {
                    p2_superCol++;
                }

            /*-- Checks if a player won --*/

            if (p1_superDiagL2R == 3 || p1_superDiagR2L == 3 || p1_superRow == 3 || p1_superCol == 3)
            {
                return P1;
            }
            else

                if (p2_superDiagL2R == 3 || p2_superDiagR2L == 3 || p2_superRow == 3 || p2_superCol == 3)
            {
                return P2;
            }

            /* If the game is a draw */
            int completedCells = 0;
            if (isGridDraw(superGrid, LETTERS[row][col]))
            {
                completedCells++;
            }
            if (completedCells == 9)
            {
                return DRAW;
            }
        }
    }
    return DEFAULT;
}

/**
 * @brief Prints the game's grid in the terminal.
 *
 * @details Prints the game's grid in the terminal, nothing too fancy here.
 *
 * @param superGrid Game's grid.
 */
void PrintGrid(struct Grid superGrid[ROW][COLUMN])
{
    clearTerminal();
    printf(BLUE " ____  _  _  ____  ____  ____    ____  __  ___     ____  __    ___     ____  __  ____ \n");
    printf("/ ___)/ )( \\(  _ \\(  __)(  _ \\  (_  _)(  )/ __)___(_  _)/  \\  / __)___(_  _)/  \\(  __)\n");
    printf("\\___ \\) \\/ ( ) __/ ) _)  )   /    )(   )(( (__(___) )( /    \\( (__(___) )( (    )) _) \n");
    printf("(____/\\____/(__)  (____)(__\\_)   (__) (__)\\___)    (__)\\_/\\_/ \\___)    (__) \\__/(____)\n");
    printf("                                                                   By @powan.5(Discord)\n" RESET);
    printf("\n\n\n");

    /*-- Output template --*/

    gridBlocks BLOCS = {
        {/* Main grid */
         YELLOW "|" GREEN " %c  " CYAN " 1   2   3 " GREEN "  %c " RESET,
         YELLOW "|" BLUE "   +---+---+---+   " RESET,
         YELLOW "| 1 | %c | %c | %c | 1 ",
         YELLOW "|" BLUE "   +---+---+---+   " RESET,
         YELLOW "| 2 | %c | %c | %c | 2 ",
         YELLOW "|" BLUE "   +---+---+---+   " RESET,
         YELLOW "| 3 | %c | %c | %c | 3 ",
         YELLOW "|" BLUE "   +---+---+---+   " RESET,
         YELLOW "|" GREEN " %c  " CYAN " 1   2   3 " GREEN "  %c "},
        {/* Grid completed by P1 */
         YELLOW "| " RED "                  " RESET,
         YELLOW "| " RED "                  " RESET,
         YELLOW "| " RED "      \\   /       " RESET,
         YELLOW "| " RED "       \\ /        " RESET,
         YELLOW "| " RED "        X         " RESET,
         YELLOW "| " RED "       / \\        " RESET,
         YELLOW "| " RED "      /   \\       " RESET,
         YELLOW "| " RED "                  " RESET,
         YELLOW "| " RED "                  " RESET},
        {/* Grid completed by P2 */
         YELLOW "| " BLUE "                  " RESET,
         YELLOW "| " BLUE "                  " RESET,
         YELLOW "| " BLUE "    /-------\\     " RESET,
         YELLOW "| " BLUE "    |       |     " RESET,
         YELLOW "| " BLUE "    |       |     " RESET,
         YELLOW "| " BLUE "    |       |     " RESET,
         YELLOW "| " BLUE "    \\-------/     " RESET,
         YELLOW "| " BLUE "                  " RESET,
         YELLOW "| " BLUE "                  " RESET}};

    /**-- Main loop --*/
    for (int superRow = 0; superRow < ROW; superRow++)
    {
        printf(YELLOW "+-------------------+-------------------+-------------------+\n"); /* Dividers for the 'super grid' */
        for (int blocRowIndex = 0; blocRowIndex < 9; blocRowIndex++)
        {
            for (int superCol = 0; superCol < COLUMN; superCol++)
            {
                switch (gridComplete(superGrid, LETTERS[superRow][superCol])) /* Checks if a player has won a square of the 'super grid' or not */
                {
                /* Prints the square if a player has won it */
                case P1:
                    printf("%s", BLOCS[P1][blocRowIndex]);
                    break;

                case P2:
                    printf("%s", BLOCS[P2][blocRowIndex]);
                    break;

                /* Prints the square if neither of the players has won it */
                default:
                    if (blocRowIndex == 0 || blocRowIndex == 8) /* "| %c   1   2   3   %c |" */
                    {
                        char printableLine[70] = "";
                        sprintf(printableLine, BLOCS[0][blocRowIndex], LETTERS[superRow][superCol], LETTERS[superRow][superCol]);
                        printf("%s", printableLine);
                        break;
                    }
                    else

                        if (blocRowIndex == 1 || blocRowIndex == 3 || blocRowIndex == 5 || blocRowIndex == 7) /* "|   +---+---+---+   |" */
                    {
                        printf("%s", BLOCS[0][blocRowIndex]);
                        break;
                    }

                    else /* "| [nb] | %c | %c | %c | [nb] |" */
                    {
                        printf(YELLOW "| " CYAN "%d " RESET, (blocRowIndex / 2));

                        for (int tinyCol = 0; tinyCol < COLUMN; tinyCol++)
                        {
                            printf(BLUE "| " RESET "%c ", superGrid[superRow][superCol].grid[(blocRowIndex / 2) - 1][tinyCol]);
                        }

                        printf(BLUE "| " CYAN "%d ", blocRowIndex / 2);
                        break;
                    }
                    break;
                }
            }
            printf(YELLOW "|\n" RESET);
        }
    }
    printf(YELLOW "+-------------------+-------------------+-------------------+\n\n" RESET);
}

/* Inputs */

/**
 * @brief Asks the User for a CHAR input in order to choose where to play in the 'super grid'.
 *
 * @details The function will ask the user for a CHAR input in order to choose where to play in the 'super grid'.
 *
 * @param ptrInput Pointer of the input variable.
 */
void inputWhichGrid(char *ptrLetter)
{
    printf("in which grid do you wish to play (From 'A' to 'I'): \n");

    bool condition = false;

    do
    {
        char input[2];

        fgets(input, sizeof(input), stdin);
        fflush(stdin);

        /*-- Main loop, checks if the user's input is correct --*/

        int temp;
        if (sscanf(input, "%d", &temp) != false) /* Checks if the user inputed an int */
        {
            errors(NON_CHAR_INPUT);
        }

        /* Checks if it's a correct letter */
        for (int row = 0; row < ROW + 1; row++)
        {
            for (int col = 0; col < COLUMN + 1; col++)
            {
                char upperInput = toupper(input[0]);
                if (upperInput == LETTERS[row][col]) /* if it is, outputs it, */
                {
                    *ptrLetter = upperInput;
                    condition = true;
                }
            }
        }

        /* prints an error otherwise, asking the user to try again */
        if (!condition)
        {
            errors(CHAR_INPUT_UNRECONIZED);
        }

    } while (!condition);
}

/**
 * @brief Asks the User for an INT input in order to choose where to play in the grid inside the 'super grid'.
 *
 * @details The user can only input a number between 1 and 3 to choose a cell inside the grid.
 *
 * @param ptrInput Pointer of the input variable.
 */
void inputWhichCell(int *ptrInput)
{
    printf("(From 1 to 3): \n");

    bool condition = false;

    do
    {
        char input[3] = "";
        int value;

        fgets(input, sizeof(input), stdin);
        fflush(stdin);

        /*-- Makes sures the input is not longer than 3 --*/

        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n')
        {
            input[strlen(input) - 1] = '\0';
        }
        else
        {
            errors(INPUT_TOO_LONG);
            while (getchar() != '\n')
                ;
            continue;
        }

        /*-- Main loop, checks if the user's input is correct --*/

        if (sscanf(input, "%d", &value) != false) /* Convert the STR to INT, prints error if it doesn't work */
        {
            if (value >= 1 && value <= 3) /* Checks if it's a correct number, */
            {
                value--;
                *ptrInput = value; /* attributes it to the variable if correct, */
                condition = true;
            }
            else /* prints an error otherwise, asking the user to try again */
            {
                errors(INT_OUT_OF_RANGE);
                continue;
            }
        }
        else
        {
            errors(NON_INT_INPUT);
            continue;
        }
    } while (!condition);
}

/**
 * @brief Have a player take his turn and play.
 *
 * @details The player takes his turn and play in the grid inside the 'Super Grid'. Returns the letter of the next player/bot to play in.
 *
 * @param superGrid Game's grid.
 * @param player The players id, to know if it's 'X'or'O's turn.
 * @param letter Letter used to know the grifd in where the player plays.
 * @param ptrPlayerRow Pointer of the row where the player plays.
 * @param ptrPlayerCol Pointer of the column where the player plays.
 *
 * @returns CHAR, letter for the next player to play in.
 *
 * @see inputWhichCell(), inputWhichGrid()
 */
char takeTurn(struct Grid superGrid[ROW][COLUMN], int player, char letter, int *ptrPlayerRow, int *ptrPlayerCol)
{
    /*-- Finds the indexs of the letter --*/
    int superGridRow, superGridColumn;

    bool foundLetter = false;
    for (int row = 0; row < ROW + 1 || !foundLetter; row++)
    {
        for (int col = 0; col < COLUMN + 1 || !foundLetter; col++)
        {
            if (LETTERS[row][col] == letter)
            {
                superGridRow = row;
                superGridColumn = col;
                foundLetter = true;
            }
        }
    }

    /*-- Asks row & column, and checks if it's a correct cell to play in --*/

    bool turnCompleted = false;
    int row = -1, column = -1;
    int preventFails = 0;

    while (getchar() != '\n')
        ;
    do
    {
        /* Asks for row & column, makes it from [1-3] to [0-2] */

        printf(RESET "Please give the" CYAN " row index ");
        inputWhichCell(&row);
        printf(RESET "Please give the" CYAN " column index ");
        inputWhichCell(&column);

        /* Checks if the chosen cell is available */

        if (superGrid[superGridRow][superGridColumn].grid[row][column] == '.') /* If it is, changes it to the player's letter */
        {

            if (player == P1)
            {
                /* X */
                *ptrPlayerRow = row;
                *ptrPlayerCol = column;
                turnCompleted = true;
            }
            else if (player == P2)
            {
                /* O */
                *ptrPlayerRow = row;
                *ptrPlayerCol = column;
                turnCompleted = true;
            }

            else /* In case there somehow is an error with the players' IDs */
            {
                errors(PLAYER_ID);
            }
        }

        else /* Prints an error otherwise */
        {
            errors(CELL_TAKEN);
            preventFails++;
        }

        if (preventFails == 9) /* If the player fails to intput a cell 9 times, it gives up and makes a random move for you :) */
        { /* Mainly to prevent softlocks in case of a bug */
            letter = easyBotTurn(superGrid, letter, ptrPlayerRow, ptrPlayerCol);
            turnCompleted = true;
        }
    } while (!turnCompleted);

    return LETTERS[row][column];
}

/* Bot Functions */

/**
 * @brief Sets the difficulty of the bot via a menu.
 *
 * @details Prints the menu and asks the user for an input to choose the bot's difficulty.
 *
 * @returns INT, the difficulty of the bot.
 */
int setDifficulty()
{
    int choice = DEFAULT;

    clearTerminal();
    printf(BLUE " ____  _  _  ____  ____  ____    ____  __  ___     ____  __    ___     ____  __  ____ \n");
    printf("/ ___)/ )( \\(  _ \\(  __)(  _ \\  (_  _)(  )/ __)___(_  _)/  \\  / __)___(_  _)/  \\(  __)\n");
    printf("\\___ \\) \\/ ( ) __/ ) _)  )   /    )(   )(( (__(___) )( /    \\( (__(___) )( (    )) _) \n");
    printf("(____/\\____/(__)  (____)(__\\_)   (__) (__)\\___)    (__)\\_/\\_/ \\___)    (__) \\__/(____)\n");
    printf("                                                                   By @powan.5(Discord)\n");
    printf("\n");
    printf("                                                                                      \n");
    printf("                      " GREEN "Weclome to a 1 Player match against a bot" RESET "                      \n");
    printf("\n");
    printf("Please select a difficulty for the bot: \n");
    printf("\n");
    printf(RED "\t[1]  Easy\n" RESET);
    printf(RED "\t[2]  Medium\n" RESET);
    printf(RED "\t[3]  Hard\n" RESET);
    printf(RED "\t[0]  Go back to Main menu\n" RESET);
    printf("\n");
    printf("Please enter your choice: ");

    do
    {
        scanf("%d", &choice);
    } while (choice != EASY && choice != MEDIUM && choice != HARD && choice != MENU);

    return choice;
}

/**
 * @brief Have the bot take its turn and play RANDOMLY.
 *
 * @details The bot plays randomly.
 *
 * @param superGrid Game's grid.
 * @param letter Letter used to know the grid in which the bot plays.
 * @param ptrBotRow Pointer to store the row index of the bot's move.
 * @param ptrBotCol Pointer to store the column index of the bot's move.
 */
char easyBotTurn(struct Grid superGrid[ROW][COLUMN], char letter, int *ptrBotRow, int *ptrBotCol)
{
    /* Get available cells */
    int availableCells[9];
    int count = 0;

    /* Finds the current playing grid */
    bool foundLetter = false;
    int superGridRow, superGridColumn;
    for (int letterRow = 0; letterRow < ROW && !foundLetter; letterRow++)
    {
        for (int letterColumn = 0; letterColumn < COLUMN && !foundLetter; letterColumn++)
        {
            if (letter == LETTERS[letterRow][letterColumn])
            {
                foundLetter = true;
                superGridRow = letterRow;
                superGridColumn = letterColumn;
            }
        }
    }

    /* Finds available cells */
    for (int gridRow = 0; gridRow < ROW; gridRow++)
    {
        for (int gridCol = 0; gridCol < COLUMN; gridCol++)
        {
            if (superGrid[superGridRow][superGridColumn].grid[gridRow][gridCol] == '.')
            {
                availableCells[count] = gridRow * COLUMN + gridCol;
                count++;
            }
        }
    }

    /* Choose random available cell */
    srand(time(NULL));
    int randIndex = rand() % count;
    int chosenRow = availableCells[randIndex] / COLUMN;
    int chosenCol = availableCells[randIndex] % COLUMN;

    /* Plays the turn */
    *ptrBotRow = chosenRow;
    *ptrBotCol = chosenCol;

    printf("I'm going to make a move at" RED " (%d, %d)" RESET "!\n", chosenRow + 1, chosenCol + 1);

    return LETTERS[chosenRow][chosenCol];
}

/**
 * @brief Have the bot take its turn and play a move, either easy or hard.
 *
 * @details The bot will play a move based on a random choice between easy and hard.
 *
 * @param superGrid Game's grid.
 * @param letter Letter used to know the grid in which the bot plays.
 * @param ptrBotRow Pointer to store the row index of the bot's move.
 * @param ptrBotCol Pointer to store the column index of the bot's move.
 *
 */
char mediumBotTurn(struct Grid superGrid[ROW][COLUMN], char letter, int *ptrBotRow, int *ptrBotCol)
{
    /* As the bot is based on a random choice between easy and hard, it will play randomly one of the 2 */
    sleep(1);
    srand(time(NULL));
    int choice = rand() % 3;
    switch (choice)
    {
    case 1:
        /* Hard Bot move */
        return hardBotTurn(superGrid, letter, ptrBotRow, ptrBotCol);
        break;

    default:
        /* Easy Bot move */
        return easyBotTurn(superGrid, letter, ptrBotRow, ptrBotCol);
        break;
    }
    /* It just works shut up */
}

/**
 * @brief Have the bot take its turn and play the best move.
 *
 * @details This function is based on the minimax algorithm. It is a recursive function that will find the best move and have the bot play it.
 *
 * @param superGrid Game's grid.
 * @param letter Letter used to know the grid in which the bot plays.
 * @param ptrBotRow Pointer to store the row index of the bot's move.
 * @param ptrBotCol Pointer to store the column index of the bot's move.
 *
 */
char hardBotTurn(struct Grid superGrid[ROW][COLUMN], char letter, int *ptrBotRow, int *ptrBotCol)
{
    int chosenRow = 4, chosenCol = 4;

    /* Finds the current playing grid */
    bool foundLetter = false;
    int superGridRow, superGridColumn;
    for (int letterRow = 0; letterRow < ROW && !foundLetter; letterRow++)
    {
        for (int letterColumn = 0; letterColumn < COLUMN && !foundLetter; letterColumn++)
        {
            if (letter == LETTERS[letterRow][letterColumn])
            {
                foundLetter = true;
                superGridRow = letterRow;
                superGridColumn = letterColumn;
            }
        }
    }

    /*-- Chooses a tactical available cell --*/
    bool foundCell = false;

    while (!foundCell)
    {
        /*-- Checks if a player is close to winning --*/

        /* Checks the Rows and Columns */
        for (int row = 0; row < ROW; row++)
        {
            for (int col = 0; col < COLUMN; col++)
            {
                /* Checks the row for if P2 is close to winning */
                if (superGrid[superGridRow][superGridColumn].grid[row][col] == 'O')
                {
                    int p2_row = 0;
                    for (int rowCheck = 0; rowCheck < ROW; rowCheck++)
                    {
                        if (superGrid[superGridRow][superGridColumn].grid[rowCheck][col] == 'O')
                        {
                            p2_row++;
                        }
                        if (p2_row == 2)
                        {
                            for (int rowCheck = 0; rowCheck < ROW; rowCheck++)
                            {
                                if (superGrid[superGridRow][superGridColumn].grid[rowCheck][col] == '.')
                                {
                                    chosenRow = rowCheck;
                                    chosenCol = col;
                                    foundCell = true;
                                }
                            }
                        }
                    }
                }

                /* Checks the column for if P2 is close to winning */
                if (superGrid[superGridRow][superGridColumn].grid[row][col] == 'O')
                {
                    int p2_col = 0;
                    for (int colCheck = 0; colCheck < COLUMN; colCheck++)
                    {
                        if (superGrid[superGridRow][superGridColumn].grid[row][colCheck] == 'O')
                        {
                            p2_col++;
                        }
                        if (p2_col == 2)
                        {
                            for (int colCheck = 0; colCheck < COLUMN; colCheck++)
                            {
                                if (superGrid[superGridRow][superGridColumn].grid[row][colCheck] == '.')
                                {
                                    chosenRow = row;
                                    chosenCol = colCheck;
                                    foundCell = true;
                                }
                            }
                        }
                    }
                }

                /* Checks the row for if P1 is close to winning */
                if (superGrid[superGridRow][superGridColumn].grid[row][col] == 'X')
                {
                    int p1_row = 0;
                    for (int rowCheck = 0; rowCheck < ROW; rowCheck++)
                    {
                        if (superGrid[superGridRow][superGridColumn].grid[rowCheck][col] == 'X')
                        {
                            p1_row++;
                        }
                        if (p1_row == 2)
                        {
                            for (int rowCheck = 0; rowCheck < ROW; rowCheck++)
                            {
                                if (superGrid[superGridRow][superGridColumn].grid[rowCheck][col] == '.')
                                {
                                    chosenRow = rowCheck;
                                    chosenCol = col;
                                    foundCell = true;
                                }
                            }
                        }
                    }
                }

                /* Checks the column for if P1 is close to winning */
                if (superGrid[superGridRow][superGridColumn].grid[row][col] == 'X')
                {
                    int p1_col = 0;
                    for (int colCheck = 0; colCheck < COLUMN; colCheck++)
                    {
                        if (superGrid[superGridRow][superGridColumn].grid[row][colCheck] == 'X')
                        {
                            p1_col++;
                        }
                        if (p1_col == 2)
                        {
                            for (int colCheck = 0; colCheck < COLUMN; colCheck++)
                            {
                                if (superGrid[superGridRow][superGridColumn].grid[row][colCheck] == '.')
                                {
                                    chosenRow = row;
                                    chosenCol = colCheck;
                                    foundCell = true;
                                }
                            }
                        }
                    }
                }
            }
        }

        /* Checks the Diagonals */
        for (int diag = 0, invDiag = 2; diag < DIAG; diag++, invDiag--)
        {
            /* Checks the diagonal from (0,0) to (2,2) for if P2 is close to winning */
            if (superGrid[superGridRow][superGridColumn].grid[diag][diag] == 'O')
            {
                int p2_diagL2R = 0;
                for (int diagCheck = 0; diagCheck < DIAG; diagCheck++)
                {
                    if (superGrid[superGridRow][superGridColumn].grid[diagCheck][diagCheck] == 'O')
                    {
                        p2_diagL2R++;
                    }
                    if (p2_diagL2R == 2)
                    {
                        for (int diagCheck = 0; diagCheck < DIAG; diagCheck++)
                        {
                            if (superGrid[superGridRow][superGridColumn].grid[diagCheck][diagCheck] == '.')
                            {
                                chosenRow = diagCheck;
                                chosenCol = diagCheck;
                                foundCell = true;
                            }
                        }
                    }
                }
            }

            /* Checks the diagonal from (0,2) to (2,0) for if P2 is close to winning */
            if (superGrid[superGridRow][superGridColumn].grid[diag][invDiag] == 'O')
            {
                int p2_diagR2L = 0;
                for (int diagCheck = 0; diagCheck < DIAG; diagCheck++)
                {
                    if (superGrid[superGridRow][superGridColumn].grid[diagCheck][invDiag] == 'O')
                    {
                        p2_diagR2L++;
                    }
                    if (p2_diagR2L == 2)
                    {
                        for (int diagCheck = 0; diagCheck < DIAG; diagCheck++)
                        {
                            if (superGrid[superGridRow][superGridColumn].grid[diagCheck][invDiag] == '.')
                            {
                                chosenRow = diagCheck;
                                chosenCol = invDiag;
                                foundCell = true;
                            }
                        }
                    }
                }
            }

            /* Checks the diagonal from (0,0) to (2,2) for if P1 is close to winning */
            if (superGrid[superGridRow][superGridColumn].grid[diag][diag] == 'X')
            {
                int p1_diagL2R = 0;
                for (int diagCheck = 0; diagCheck < DIAG; diagCheck++)
                {
                    if (superGrid[superGridRow][superGridColumn].grid[diagCheck][diagCheck] == 'X')
                    {
                        p1_diagL2R++;
                    }
                    if (p1_diagL2R == 2)
                    {
                        for (int diagCheck = 0; diagCheck < DIAG; diagCheck++)
                        {
                            if (superGrid[superGridRow][superGridColumn].grid[diagCheck][diagCheck] == '.')
                            {
                                chosenRow = diagCheck;
                                chosenCol = diagCheck;
                                foundCell = true;
                            }
                        }
                    }
                }
            }

            /* Checks the diagonal from (0,2) to (2,0) for if P1 is close to winning */
            if (superGrid[superGridRow][superGridColumn].grid[diag][invDiag] == 'X')
            {
                int p1_diagR2L = 0;
                for (int diagCheck = 0; diagCheck < DIAG; diagCheck++)
                {
                    if (superGrid[superGridRow][superGridColumn].grid[diagCheck][invDiag] == 'X')
                    {
                        p1_diagR2L++;
                    }
                    if (p1_diagR2L == 2)
                    {
                        for (int diagCheck = 0; diagCheck < DIAG; diagCheck++)
                        {
                            if (superGrid[superGridRow][superGridColumn].grid[diagCheck][invDiag] == '.')
                            {
                                chosenRow = diagCheck;
                                chosenCol = invDiag;
                                foundCell = true;
                            }
                        }
                    }
                }
            }
        }

        /* If no winning/counter cells were found, checks for tactical moves (center and corners) */
        while (!foundCell)
        {
            bool checked00 = false, checked11 = false, checked02 = false, checked20 = false, checked22 = false;

            srand(time(NULL));
            int randChoice = rand() % 5;
            switch (randChoice)
            {
            case 0:
                if (superGrid[superGridRow][superGridColumn].grid[1][1] == '.' && !checked11)
                {
                    chosenRow = 1;
                    chosenCol = 1;
                    foundCell = true;
                    checked11 = true;
                }
                break;

            case 1:
                if (superGrid[superGridRow][superGridColumn].grid[0][0] == '.' && !checked00)
                {
                    chosenRow = 0;
                    chosenCol = 0;
                    foundCell = true;
                    checked00 = true;
                }
                break;

            case 2:
                if (superGrid[superGridRow][superGridColumn].grid[0][2] == '.' && !checked02)
                {
                    chosenRow = 0;
                    chosenCol = 2;
                    foundCell = true;
                    checked02 = true;
                }
                break;

            case 3:
                if (superGrid[superGridRow][superGridColumn].grid[2][0] == '.' && !checked20)
                {
                    chosenRow = 2;
                    chosenCol = 0;
                    foundCell = true;
                    checked20 = true;
                }
                break;

            case 4:
                if (superGrid[superGridRow][superGridColumn].grid[2][2] == '.' && !checked22)
                {
                    chosenRow = 2;
                    chosenCol = 2;
                    foundCell = true;
                    checked22 = true;
                }
                break;

            default:
                fflush(stdout);
                sleep(1);
                break;
            }
            if (checked00 && checked11 && checked02 && checked20 && checked22)
            {
                break;
            }
        }

        /*-- Plays the turn in the chosen cell --*/

        /* If a tactical move is avilable, plays the turn in that cell*/
        if (foundCell)
        {
            printf("AHAH! I've found a tactical move!\n");
            printf("I'm going to make a move at" RED " (%d, %d)" RESET "!\n", chosenRow + 1, chosenCol + 1);

            /* Playes the turn */
            *ptrBotRow = chosenRow;
            *ptrBotCol = chosenCol;
        }

        /* If no tactical moves were found, makes a random move */
        else
        {
            return easyBotTurn(superGrid, letter, ptrBotRow, ptrBotCol);
            foundCell = true;
        }
    }

    return LETTERS[chosenRow][chosenCol];
}

/**
 * @brief Have the bot choose a letter.
 *
 * @details Have the bot "choose" a random letter.
 *
 * @param superGrid The grid to check for taken cells.
 * @param ptrLetter The letter to be chosen.
 */
void botChooseLetter(struct Grid superGrid[ROW][COLUMN], char *ptrLetter)
{
    int availableCells[9];
    int count = 0;

    /* Finds available cells */
    for (int gridRow = 0; gridRow < ROW; gridRow++)
    {
        for (int gridCol = 0; gridCol < COLUMN; gridCol++)
        {
            if (gridComplete(superGrid, LETTERS[gridRow][gridCol]) == DEFAULT)
            {
                availableCells[count] = gridRow * COLUMN + gridCol;
                count++;
            }
        }
    }

    srand(time(NULL));
    int randIndex = rand() % count;
    int randRow = availableCells[randIndex] / COLUMN;
    int randCol = availableCells[randIndex] % COLUMN;
    *ptrLetter = LETTERS[randRow][randCol];
}

/****************************************************/
/****************************************************/
/******|         Main Game Functions          |******/
/****************************************************/
/****************************************************/

/**
 * @brief Runs a single player match against a BOT opponent.
 *
 * @details The function is the main function of the 1 player match with a bot. It takes care of the game's flow and the player/bot's turns.
 *
 * @see takeTurn(), setDifficulty(), [difficulty]BotTurn(), botChooseLetter()
 */
void match1P()
{
    clearTerminal();

    int difficulty = setDifficulty();

    if (difficulty == MENU)
    {
        mainScreen();
    }

    char rematch = 'N';
    int player = 1, playedRow = 0, playedCol = 0;
    int turns = 0;
    char letter = 'Z';
    int winCondition = DEFAULT;

    struct Grid superGrid[ROW][COLUMN];
    initSuperGrid(superGrid);

    /* Get the pseudo for the players & bot */
    gamertag playerName;
    gamertag botName;

    clearTerminal();
    printf("Player, please choose you pseudo ('*' for a random one): \n");
    namePlayer(playerName);

    /* Get the pseudo for the bot */
    srand(time(NULL));
    int botPseudo = rand() % (nbBotNames / 3);
    switch (difficulty)
    {
    case EASY:
        strcpy(botName, BotNames[botPseudo]);
        break;

    case MEDIUM:
        strcpy(botName, BotNames[botPseudo + 5]);
        break;

    case HARD:
        strcpy(botName, BotNames[botPseudo + 10]);
        break;

    default:
        errors(UNEXPECTED);
        break;
    }

    printf("%s will play 'X'\n", playerName);
    printf("%s will play 'O'\n", botName);

    fflush(stdout);
    sleep(5);

    do
    {
        turns++;

        fflush(stdout);
        PrintGrid(superGrid);

        /* Checks which player's turn it is */
        if (player == P1)
        {
            printf(RED "%s" RESET "(X) to play, ", playerName);
        }
        else if (player == P2)
        {
            printf(RED "%s" RESET "(O) to play, ", botName);
        }

        /* If the game has just started */
        if (letter == 'Z')
        {
            inputWhichGrid(&letter);
        }
        else

            /* If the supposed grid to play in is completed */
            if (gridComplete(superGrid, letter) != DEFAULT)
            {
                printf(RED "The supposed grid already full" RESET ", so ");
                if (player == P1)
                {
                    inputWhichGrid(&letter);
                }
                else

                    if (player == P2)
                {
                    printf("I'm going to play in the");
                    botChooseLetter(superGrid, &letter);
                    printf(" '%c' grid.\n", letter);
                    sleep(5);
                }

                while (gridComplete(superGrid, letter) != DEFAULT)
                {
                    errors(GRID_TAKEN);
                    inputWhichGrid(&letter);
                }
            }

            /* Reminds which grid the player is in */
            else
            {
                printf("\nYou are playing in the '%c' grid.\n\n", letter);
            }

        /* Finds the letter indexs */
        bool foundLetter = false;
        int superGridRow, superGridColumn;

        for (int letterRow = 0; letterRow < ROW && !foundLetter; letterRow++)
        {
            for (int letterColumn = 0; letterColumn < COLUMN && !foundLetter; letterColumn++)
            {
                if (letter == LETTERS[letterRow][letterColumn])
                {
                    foundLetter = true;
                    superGridRow = letterRow;
                    superGridColumn = letterColumn;
                }
            }
        }

        /* If the grid got full but not won by any, resets it after the next player's turn */
        if (isGridDraw(superGrid, letter) && gridComplete(superGrid, letter) == DEFAULT)
        {
            for (int row = 0; row < ROW; row++)
            {
                for (int col = 0; col < COLUMN; col++)
                {
                    superGrid[superGridRow][superGridColumn].grid[row][col] = '.';
                }
            }
            PrintGrid(superGrid);
        }

        if (player == P1)
        {
            letter = takeTurn(superGrid, player, letter, &playedRow, &playedCol);
        }
        else

            if (player == P2)
        {
            printf("Thinking");
            loading_animation();

            switch (difficulty)
            {
            case EASY:
                letter = easyBotTurn(superGrid, letter, &playedRow, &playedCol);
                break;

            case MEDIUM:
                letter = mediumBotTurn(superGrid, letter, &playedRow, &playedCol);
                break;

            case HARD:
                letter = hardBotTurn(superGrid, letter, &playedRow, &playedCol);
                break;

            default:
                errors(UNEXPECTED);
                break;
            }
            sleep(3);
        }

        /* Takes care of asigning the correct player's symbol and switching players */
        switch (player)
        {
        case P1:
            superGrid[superGridRow][superGridColumn].grid[playedRow][playedCol] = 'X';
            player = P2;
            break;

        case BOT:
            superGrid[superGridRow][superGridColumn].grid[playedRow][playedCol] = 'O';
            player = P1;
            break;

        default:
            errors(PLAYER_ID);
            break;
        }

        /* Checks if the game has been won */
        winCondition = superGridComplete(superGrid);
    } while (winCondition == DEFAULT);

    PrintGrid(superGrid);
    printf("You played for %d turns.\n", turns);

    printf("Do you want to play again ? [Y]/[N] ");
    scanf("%c", &rematch);
    rematch = toupper(rematch);
    if (rematch == 'Y')
    {
        clearTerminal();
        printf("Reinitialising");
        loading_animation();
        match1P();
    }
}

/**
 * @brief Runs a 2 player match with alternating turns.
 *
 * @details The function is the main function of the 2 player match. It takes care of the game's flow and the player's turns.
 *
 * @see takeTurn()
 */
void match2P()
{
    clearTerminal();

    char rematch = 'N';
    int player = 1, playedRow = 0, playedCol = 0;
    int turns = 0;
    char letter = 'Z';
    int winCondition = DEFAULT;

    struct Grid superGrid[ROW][COLUMN];
    initSuperGrid(superGrid);

    /* Get the pseudo for both players */
    gamertag nameP1;
    gamertag nameP2;

    while (getchar() != '\n')
        ; /* Clears entry buffer */
    printf("Player 1, please choose you pseudo ('*' for a random one): \n");
    namePlayer(nameP1);
    sleep(1);
    printf("Player 2, please choose you pseudo ('*' for a random one): \n");
    namePlayer(nameP2);

    printf("%s will play 'X' & ", nameP1);
    printf("%s will play 'O'\n", nameP2);

    fflush(stdout);
    sleep(5);

    do
    {
        turns++;

        fflush(stdout);
        PrintGrid(superGrid);

        /* Checks which player's turn it is */
        if (player == P1)
        {
            printf(RED "%s" RESET "(X) to play, ", nameP1);
        }
        else if (player == P2)
        {
            printf(RED "%s" RESET "(O) to play, ", nameP2);
        }

        /* If the game has just started */
        if (letter == 'Z')
        {
            inputWhichGrid(&letter);
        }
        else

            /* If the supposed grid to play in is completed */
            if (gridComplete(superGrid, letter) != DEFAULT)
            {
                printf("The supposed grid already full, so ");
                inputWhichGrid(&letter);

                while (gridComplete(superGrid, letter) != DEFAULT)
                {
                    errors(GRID_TAKEN);
                    inputWhichGrid(&letter);
                }
            }

            /* Reminds which grid the player is in */
            else
            {
                printf("\nYou are playing in the '%c' grid.\n\n", letter);
            }

        /* Finds the letter indexs */
        bool foundLetter = false;
        int superGridRow, superGridColumn;

        for (int letterRow = 0; letterRow < ROW && !foundLetter; letterRow++)
        {
            for (int letterColumn = 0; letterColumn < COLUMN && !foundLetter; letterColumn++)
            {
                if (letter == LETTERS[letterRow][letterColumn])
                {
                    foundLetter = true;
                    superGridRow = letterRow;
                    superGridColumn = letterColumn;
                }
            }
        }

        /* If the grid got full but not won by any, resets it after the next player's turn */
        if (isGridDraw(superGrid, letter) && gridComplete(superGrid, letter) == DEFAULT)
        {
            for (int row = 0; row < ROW; row++)
            {
                for (int col = 0; col < COLUMN; col++)
                {
                    superGrid[superGridRow][superGridColumn].grid[row][col] = '.';
                }
            }
            PrintGrid(superGrid);
        }

        letter = takeTurn(superGrid, player, letter, &playedRow, &playedCol);

        /* Takes care of asigning the correct player's symbol and switching players */
        switch (player)
        {
        case P1:
            superGrid[superGridRow][superGridColumn].grid[playedRow][playedCol] = 'X';
            player = P2;
            break;

        case P2:
            superGrid[superGridRow][superGridColumn].grid[playedRow][playedCol] = 'O';
            player = P1;
            break;

        default:
            errors(PLAYER_ID);
            break;
        }

        /* Checks if the game has been won */
        winCondition = superGridComplete(superGrid);
    } while (winCondition == DEFAULT);

    PrintGrid(superGrid);
    printf("You played for %d turns.\n", turns);

    printf("Do you want to play again ? [Y]/[N] ");
    scanf("%c", &rematch);
    rematch = toupper(rematch);
    if (rematch == 'Y')
    {
        clearTerminal();
        printf("Reinitialising");
        loading_animation();
        match2P();
    }
}

/**
 * @brief Runs a match with only bots.
 *
 * @details The function is the main function of the bot match. It takes care of the game's flow and the bots' turns.
 *
 * @see setDifficulty(), [difficulty]BotTurn(), botChooseLetter()
 */
void botVsBotMatch()
{
    clearTerminal();
    printf("You will shortly be prompted to choose the difficulty for both bots, hence why the \"choose difficulty screen\" showing up twice.\n");
    fflush(stdout);
    sleep(10);

    /*-- Variables --*/
    int difficultyBot_1 = setDifficulty();
    int difficultyBot_2 = setDifficulty();

    char *botName_1 = "Fred";
    char *botName_2 = "Jeremy";

    char playAgain = 'N';
    int player = 1, playedRow = 0, playedCol = 0;
    int turns = 0;
    char letter = 'Z';
    int winCondition = DEFAULT;

    struct Grid superGrid[ROW][COLUMN];
    initSuperGrid(superGrid);

    /*-- Clears the terminal --*/
    clearTerminal();

    /*-- Prints the bots' difficulty --*/
    printf("Bot 1 difficulty: %d\n", difficultyBot_1);
    printf("Bot 2 difficulty: %d\n", difficultyBot_2);

    /*-- Prints the bots' names --*/
    printf("%s will play 'X' & ", botName_1);
    printf("%s will play 'O'\n", botName_2);

    fflush(stdout);
    sleep(5);

    /*-- Main loop --*/
    do
    {
        turns++;

        fflush(stdout);
        PrintGrid(superGrid);

        /* Checks if the game has been won */
        winCondition = superGridComplete(superGrid);
        if (winCondition != DEFAULT)
        {
            break;
        }

        if (letter == 'Z')
        {
            botChooseLetter(superGrid, &letter);
        }
        else

            if (gridComplete(superGrid, letter) != DEFAULT)
        {
            botChooseLetter(superGrid, &letter);
        }

        /* Finds the letter indexs */
        bool foundLetter = false;
        int superGridRow, superGridColumn;

        for (int letterRow = 0; letterRow < ROW && !foundLetter; letterRow++)
        {
            for (int letterColumn = 0; letterColumn < COLUMN && !foundLetter; letterColumn++)
            {
                if (letter == LETTERS[letterRow][letterColumn])
                {
                    foundLetter = true;
                    superGridRow = letterRow;
                    superGridColumn = letterColumn;
                }
            }
        }

        /* If the grid got full but not won by any, resets it after the next player's turn */
        if (isGridDraw(superGrid, letter) && gridComplete(superGrid, letter) == DEFAULT)
        {
            for (int row = 0; row < ROW; row++)
            {
                for (int col = 0; col < COLUMN; col++)
                {
                    superGrid[superGridRow][superGridColumn].grid[row][col] = '.';
                }
            }
            PrintGrid(superGrid);
        }

        switch (player)
        {
        case P1:
            switch (difficultyBot_1)
            {
            case EASY:
                letter = easyBotTurn(superGrid, letter, &playedRow, &playedCol);
                break;

            case MEDIUM:
                letter = mediumBotTurn(superGrid, letter, &playedRow, &playedCol);
                break;

            case HARD:
                letter = hardBotTurn(superGrid, letter, &playedRow, &playedCol);
                break;

            default:
                errors(UNEXPECTED);
                break;
            }
            break;

        case P2:
            switch (difficultyBot_2)
            {
            case EASY:
                letter = easyBotTurn(superGrid, letter, &playedRow, &playedCol);
                break;

            case MEDIUM:
                letter = mediumBotTurn(superGrid, letter, &playedRow, &playedCol);
                break;

            case HARD:
                letter = hardBotTurn(superGrid, letter, &playedRow, &playedCol);
                break;

            default:
                errors(UNEXPECTED);
                break;
            }
            break;

        default:
            errors(PLAYER_ID);
            break;
        }

        /* Takes care of asigning the correct player's symbol and switching players */
        switch (player)
        {
        case P1:
            superGrid[superGridRow][superGridColumn].grid[playedRow][playedCol] = 'X';
            player = P2;
            break;

        case P2:
            superGrid[superGridRow][superGridColumn].grid[playedRow][playedCol] = 'O';
            player = P1;
            break;

        default:
            errors(PLAYER_ID);
            break;
        }

        /* Checks if the game has been won */
        winCondition = superGridComplete(superGrid);

        fflush(stdout);
        sleep(1);
    } while (winCondition == DEFAULT);

    PrintGrid(superGrid);
    printf("The bots played for %d turns.\n", turns);

    printf("Do you want to play again ? [Y]/[N] ");
    while (getchar() != '\n')
        ;
    scanf("%c", &playAgain);
    playAgain = toupper(playAgain);
    if (playAgain == 'Y')
    {
        clearTerminal();
        printf("Reinitialising");
        loading_animation();
        botVsBotMatch();
    }
}

/**
 * @brief Main function, runs the game.
 *
 * @details This function is the main function of the game. Calls the main menu and the match functions.
 *
 * @see mainMenu(), match1P(), match2P(), botVsBotMatch()
 */
void mainScreen()
{
    /*-- Variables --*/
    int choice = DEFAULT;

    mainMenu();

    /*-- Main loop --*/
    do
    {
        printf("Please input your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        /*-- Exit --*/
        case EXIT:
            printf("Exiting");
            loading_animation();
            exit(EXIT_SUCCESS);
            break;

            /****************************************************/
            /**************|         Rules        |**************/
            /****************************************************/

        case RULES:
            rules();
            char PressEnterToContinue = 0;
            while (PressEnterToContinue != '\r' && PressEnterToContinue != '\n')
            {
                PressEnterToContinue = getchar();
            }
            choice = DEFAULT;
            mainMenu();
            break;

            /****************************************************/
            /*************|     1 Player match     |*************/
            /****************************************************/

        case MATCH_1P:
            clearTerminal();
            printf("Initialising");
            loading_animation();

            match1P(); /* Calls the 1P match function that does it all */

            choice = DEFAULT;
            mainMenu();
            break;

            /****************************************************/
            /**************|    2 Players match    |*************/
            /****************************************************/

        case MATCH_2P:
            clearTerminal();
            printf("Initialising");
            loading_animation();

            match2P(); /* Calls the 2P match function that does it all */

            choice = DEFAULT;
            mainMenu();
            break;

        case SECRET:
            clearTerminal();
            printf("Initialising");
            loading_animation();

            botVsBotMatch(); /* Calls the bot vs bot match function that does it all */

            choice = DEFAULT;
            mainMenu();
            break;

        default:
            choice = DEFAULT;
            mainMenu();
            break;
        }

    } while (choice == DEFAULT);
}
