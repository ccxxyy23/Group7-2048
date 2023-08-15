#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h> 
#include <string.h>


#define ANSI_COLOR_RED     "\x1b[31m"  // red
#define ANSI_COLOR_GREEN   "\x1b[32m"  // green
#define ANSI_COLOR_YELLOW  "\x1b[33m"  // yellow
#define ANSI_COLOR_RESET   "\x1b[0m"   // format reset
#define ANSI_COLOR_BOLD    "\x1b[1m"   // bold
#define ANSI_COLOR_UNDERLINE "\x1b[4m" // underline
#define ANSI_COLOR_ITALIC   "\x1b[3m"  // italic
#define ANSI_COLOR_CYAN    "\x1b[36m"  // cyan
#define ANSI_COLOR_BLUE    "\x1b[34m"  // blue
#define ANSI_COLOR_MAGENTA "\x1b[35m"  // magenta




#define SIZE 4

int MAX_GRID = SIZE;
int map[SIZE][SIZE];
bool flag = false;
int score = 0;
int highestScore = 0;

void printMap() { //Kay
    // Print the top border
    printf(ANSI_COLOR_CYAN "+------+------+------+------+\n");

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(ANSI_COLOR_CYAN  "|");
            if (map[i][j] == 0) {
                printf("      ");
            } else {
                                switch (map[i][j]) {
                    case 2:
                        printf(ANSI_COLOR_BOLD ANSI_COLOR_YELLOW " %-4d " ANSI_COLOR_RESET, map[i][j]);
                        break;
                    case 4:
                        printf(ANSI_COLOR_BOLD ANSI_COLOR_BLUE " %-4d " ANSI_COLOR_RESET, map[i][j]);
                        break;
                    case 8:
                        printf(ANSI_COLOR_BOLD ANSI_COLOR_GREEN " %-4d " ANSI_COLOR_RESET, map[i][j]);
                        break;
                    case 16:
                        printf(ANSI_COLOR_BOLD ANSI_COLOR_RED " %-4d " ANSI_COLOR_RESET, map[i][j]);
                        break;
                    case 32:
                        printf(ANSI_COLOR_BOLD ANSI_COLOR_MAGENTA " %-4d " ANSI_COLOR_RESET, map[i][j]);
                        break;
                    case 64:
                        printf(ANSI_COLOR_BOLD ANSI_COLOR_CYAN " %-4d " ANSI_COLOR_RESET, map[i][j]);
                        break;
                    case 128:
                        printf(ANSI_COLOR_BOLD ANSI_COLOR_YELLOW " %-4d " ANSI_COLOR_RESET, map[i][j]);
                        break;
                    case 256:
                        printf(ANSI_COLOR_BOLD ANSI_COLOR_BLUE " %-4d " ANSI_COLOR_RESET, map[i][j]);
                        break;
                    // Add more cases for other numbers if needed
                    default:
                        printf(ANSI_COLOR_BOLD ANSI_COLOR_GREEN " %-4d " ANSI_COLOR_RESET, map[i][j]);
                }
            }
        }
        printf(ANSI_COLOR_CYAN "|\n");

        // Print the middle border
        printf(ANSI_COLOR_CYAN "+------+------+------+------+\n");
    }
}


void printScore() { //Kay
    printf(ANSI_COLOR_BOLD ANSI_COLOR_CYAN "Current score: " ANSI_COLOR_RESET);
    // Use ANSI escape sequences to color and style fraction parts
    printf(ANSI_COLOR_BOLD ANSI_COLOR_CYAN "%d" ANSI_COLOR_RESET "\n", score);
}

//create a random number at the empty position
void Createnumber() { //Kay
    while (true) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (map[x][y] == 0) {
            map[x][y] = (rand() % 2 + 1) * 2; // Generate either 2 or 4
            break;
        }
    }
}

// instuction
void printInstructions() {//Kay
    printf("=== 2048 Game Instructions ===\n");
    printf("Use the following keys to play the game:\n");
    printf("1. 'w' or 'W': Move tiles up\n");
    printf("2. 's' or 'S': Move tiles down\n");
    printf("3. 'a' or 'A': Move tiles left\n");
    printf("4. 'd' or 'D': Move tiles right\n");
    printf("5. 'q' or 'Q': Quit the game\n");
    printf("5. 'p' or 'P' to QUIT the game\n");
    printf("Combine tiles with the same number to get to 2048 and win!\n");
    printf("==============================\n\n");
}

void printGameOverScreen() {//Kay
    printf(ANSI_COLOR_BOLD ANSI_COLOR_RED);
    printf("\n"
           "  _____                         ____                 \n"
           " / ____|                       / __ \\                \n"
           "| |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ \n"
           "| | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__|\n"
           "| |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |   \n"
           " \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|   \n\n"
          );
    printf(ANSI_COLOR_RESET);
}

void printWinScreen() {//Kay
    printf(ANSI_COLOR_BOLD ANSI_COLOR_GREEN);
    printf("\n"
           " __     __          __          __         _ \n"
           " \\ \\   / /          \\ \\        / (_)      | |\n"
           "  \\ \\_/ /__  _   _   \\ \\  /\\  / / _ _ __  | |\n"
           "   \\   / _ \\| | | |   \\ \\/  \\/ / | | '_ \\ |_|\n"
           "    | | (_) | |_| |    \\  /\\  /  | | | | | _ \n"
           "    |_|\\___/ \\__,_|     \\/  \\/   |_|_| |_||_|\n\n"
           );
    printf(ANSI_COLOR_RESET);
}

void printTitleScreen() {//Kay
    printf(ANSI_COLOR_BOLD ANSI_COLOR_GREEN);
    printf("\n"
           " 2222     0000    44  44    8888 \n"
           "22  22   00  00   44  44   88  88\n"
           "   22    00  00   444444    8888 \n"
           "  22     00  00       44   88  88\n"
           "222222    0000        44    8888\n"
           "\n");

}

void clearScreen() {//Kay
    printf("\x1b[2J");
    printf("\x1b[H");
}


void printGameState() {//Kay
    clearScreen(); // Clear the screen before printing the updated grid
    printTitleScreen();
    printMap();
    printScore();

    // Print the highest score below the current score
    if (score > highestScore) {
        highestScore = score;
    }
    printf(ANSI_COLOR_BOLD ANSI_COLOR_YELLOW "Highest score: %d\n" ANSI_COLOR_RESET, highestScore);
}

void moveup(){ //Xinyao
    int i, begin;
    // i refers to colomn
    for (i = 0; i < 4; i++) {
        // every turn back to the first row
        int temp = 0;
        for (begin = 1; begin < 4; begin++) {
            // when number exists, move
            if (map[begin][i] != 0) {
                // if the temp position has no number, make it the current number
                // and release the original one
                if(map[temp][i] == 0) {
                    map[temp][i] = map[begin][i];
                    map[begin][i] = 0;
                    flag = true;
                }
                // if the two numbers equal, add together
                if(map[temp][i] == map[begin][i]) {
                    map[temp][i] += map[begin][i];
                    map[begin][i] = 0;
                    score += map[temp][i];
                    flag = true;
                    temp++;
                }
                    // if not equal, move to the temp which is the place of temp + 1
                    // notice if the temp+1 is not the current place, release
                else{
                    map[temp + 1][i] = map[begin][i];
                    if ((temp + 1) != begin) {
                        map[begin][i] = 0;
                        flag = true;
                    }
                    temp++;
                }
            }
        }
    }
}

void movedown() {//Xinyao
    int i, j;
    for (j = 0; j < MAX_GRID; j++) {
        int temp = MAX_GRID - 1;
        for (i = MAX_GRID - 2; i >= 0; i--) {
            if (map[i][j] != 0) {
                if (map[temp][j] == 0) {
                    map[temp][j] = map[i][j];
                    map[i][j] = 0;
                    flag = true;
                } else if (map[temp][j] == map[i][j]) {
                    map[temp][j] += map[i][j];
                    map[i][j] = 0;
                    temp--;
                    score += map[temp][j];
                    flag = true;
                } else {
                    map[temp - 1][j] = map[i][j];
                    if (temp - 1 != i) {
                        map[i][j] = 0;
                        flag = true;
                    }
                    temp--;
                }
            }
        }
    }
}

void moveleft() {//Xinyao
    int i, j;
    for (i = 0; i < MAX_GRID; i++) {
        int temp = 0;
        for (j = 1; j < MAX_GRID; j++) {
            if (map[i][j] != 0) {
                if (map[i][temp] == 0) {
                    map[i][temp] = map[i][j];
                    map[i][j] = 0;
                    flag = true;
                } else if (map[i][temp] == map[i][j]) {
                    map[i][temp] += map[i][j];
                    score += map[i][temp];
                    map[i][j] = 0;
                    temp++;
                    flag = true;
                } else {
                    map[i][temp + 1] = map[i][j];
                    if (temp + 1 != j) {
                        map[i][j] = 0;
                        flag = true;
                    }
                    temp++;
                }
            }
        }
    }
}

void moveright() {//Xinyao
    int i, j;
    for (i = 0; i < MAX_GRID; i++) {
        int temp = MAX_GRID - 1;
        for (j = MAX_GRID - 2; j >= 0; j--) {
            if (map[i][j] != 0) {
                if (map[i][temp] == 0) {
                    map[i][temp] = map[i][j];
                    map[i][j] = 0;
                    flag = true;
                } else if (map[i][temp] == map[i][j]) {
                    map[i][temp] += map[i][j];
                    score += map[i][temp];
                    map[i][j] = 0;
                    temp--;
                    flag = true;
                } else {
                    map[i][temp - 1] = map[i][j];
                    if (temp - 1 != j) {
                        map[i][j] = 0;
                        flag = true;
                    }
                    temp--;
                }
            }
        }
    }
}

void Gamejudge() {//Xinyao
    if (flag == true) {
        Createnumber();
        flag = false;
    }
}

int judgeover() {//Chole
    int i, j;

    /** if there is an empty grid, game is not over, return 1.
     * if there is a 2048 grid, the player wins, return 2.
    */
    for (i = 0; i < MAX_GRID; i++) {
        for (j = 0; j < MAX_GRID; j++) {
            if (map[i][j] == 2048) {
                return 2;
            }
            if (map[i][j] == 0) {
                return 1;
            }
        }
    }

    /** When two horizontally adjacent grids have the same number,
    the game is not over, return 1 */
    for (i = 0; i < MAX_GRID; i++) {
        for (j = 0; j < MAX_GRID - 1; j++) {
            if (map[i][j] == map[i][j + 1]) {
                return 1;
            }
        }
    }

    /** When two vertically adjacent grids have the same number,
    the game is not over, return 1 */
    
    for (j = 0; j < MAX_GRID; j++) {
        for (i = 0; i < MAX_GRID - 1; i++) {
            if (map[i][j] == map[i + 1][j]) {
                return 1;
            }
        }
    }

    // No empty grids and no adjacent grids with the same number, game is over, return 0
    return 0;
}



void GameControl1() { //Chole
    char key;
    while (1) {
        printf(ANSI_COLOR_BOLD ANSI_COLOR_GREEN "Next step: " ANSI_COLOR_RESET);
        scanf(" %c", &key); // Added a space before %c to consume any white-space characters

        // Clear input buffer to ensure getchar() works properly for the pause
        while ((getchar()) != '\n');

        clearScreen();
        
        switch (toupper(key)) {
            case 'W':
                moveup();
                break;
            case 'S':
                movedown();
                break;
            case 'A':
                moveleft();
                break;
            case 'D':
                moveright();
                break;
            case 'Q':
                return;
            case 'P': // Pause the game
                printf(ANSI_COLOR_BOLD ANSI_COLOR_YELLOW "Game Paused! Press any key to continue...\n" ANSI_COLOR_RESET);
                getchar(); // Wait for user input
                printGameState();
                continue; // Continue to the next iteration without checking the rest
            default:
                printf("Invalid Key! Please use a valid key.\n");
                printInstructions();
                continue;
        }

        Gamejudge();

        printGameState();

        int status = judgeover();
        if (status == 0) {
            printGameOverScreen();
            return;
        } else if (status == 2) {
            printWinScreen();
            return;
        }
    }
}





// Function to load the highest score from a file
void loadHighestScore() { //Chole
    FILE *file = fopen("highest_score.txt", "r");
    if (file != NULL) {
        fscanf(file, "%d", &highestScore);
        fclose(file);
    }
}

// Function to save the highest score to a file
void saveHighestScore() { //Chole
    FILE *file = fopen("highest_score.txt", "w");
    if (file != NULL) {
        fprintf(file, "%d", highestScore);
        fclose(file);
    }
}




int main() { //Silva
    printTitleScreen();
    printf(ANSI_COLOR_BOLD ANSI_COLOR_YELLOW "Welcome to Game 2048!" ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_UNDERLINE "Would you like to play now? Y/N/HELP\n" ANSI_COLOR_RESET);
    char input[10];   // Character array to store user input
    while (true) {
        scanf("%s", input);
        if (strcmp(input, "y") == 0 || strcmp(input, "Y") == 0) {
            break; // Start the game
        } else if (strcmp(input, "n") == 0 || strcmp(input, "N") == 0) {
            printf("Exiting the program...\n");
            exit(0);
        } else if (strcmp(input, "help") == 0 || strcmp(input, "HELP") == 0) {
            printInstructions();
            printf("Would you like to play now? Y/N\n");
        } else {
            printf("Invalid key. Try again.\n");
        }
    }

    printf(ANSI_COLOR_ITALIC "Get ready for some fun!\n" ANSI_COLOR_RESET);

    // Initialize the game map
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            map[i][j] = 0;
        }
    }

    Createnumber();
    Createnumber();
    printMap();
    printScore();
    loadHighestScore(); // Load the highest score from the file
    printGameState();

    while (true) {
        GameControl1();
        Gamejudge();
        printGameState();

        int judgeover_val = judgeover();
        if (judgeover_val == 0) {
            printGameOverScreen();
            // Check if the current score is higher than the highest score
            if (score > highestScore) {
                highestScore = score;
                printf(ANSI_COLOR_BOLD ANSI_COLOR_YELLOW "New Highest Score: %d\n" ANSI_COLOR_RESET, highestScore);
                // Save the new highest score to the file
                saveHighestScore();
            } else {
                printf(ANSI_COLOR_BOLD ANSI_COLOR_YELLOW "Highest Score: %d\n" ANSI_COLOR_RESET, highestScore);
            }

            break;
        } else if (judgeover_val == 2) {
            printWinScreen();
            break;
        }
    }

    return 0;
}