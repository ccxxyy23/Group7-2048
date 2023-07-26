#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 4

int MAX_GRID = SIZE;
int map[SIZE][SIZE];
bool flag = false;
int score = 0;

void printMap() {
    // Print the top border
    printf("+");
    for (int i = 0; i < SIZE; i++) {
        printf("----+");
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("|");
            if (map[i][j] == 0) {
                printf("    ");
            } else {
                printf("%-4d", map[i][j]);
            }
        }
        printf("|\n");

        // Print the middle border
        printf("+");
        for (int j = 0; j < SIZE; j++) {
            printf("----+");
        }
        printf("\n");
    }
}

void printScore() {
    printf("Current score: %d\n\n", score);
}

//create a random number at the empty position
void Createnumber() {
    while (true) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (map[x][y] == 0) {
            map[x][y] = (rand() % 2 + 1) * 2; // Generate either 2 or 4
            break;
        }
    }
}

void moveup(){
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

void movedown() {
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

void moveleft() {
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

void moveright() {
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

int judgeover() {
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

void Gamejudge() {
    if (flag == true) {
        Createnumber();
        flag = false;
    }
}

void GameControl1() {
    char key;
    printf("next step: w/W s/S a/A d/D \n");
    scanf(" %c", &key); // Add a space before %c to consume any leading whitespace

    switch (key) {
        case 'w':
        case 'W':
            moveup();
            break;
        case 's':
        case 'S':
            movedown();
            break;
        case 'a':
        case 'A':
            moveleft();
            break;
        case 'd':
        case 'D':
            moveright();
            break;
        case 'q':
        case 'Q':
            printf("Exiting the program...\n");
            exit(0); 
        default:
            printf("Invalid key. Try again.\n");
    }
}

int main() {

    printf("Welcome to Game 2048! Would you like to play now? Y/N\n");
    char key;
    scanf(" %c", &key); // Add a space before %c to consume any leading whitespace
    switch (key) {
        case 'y':
        case 'Y':
            moveup();
            break;
        case 'n':
        case 'N':
            exit(0);
        default:
            printf("Invalid key. Try again.\n");
    }


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

    while (true) {
        GameControl1();
        Gamejudge();
        printMap();
        printScore();
        
        int judgeover_val = judgeover();
        if (judgeover_val == 0) {
            printf("You lose the game.\n");
            break;
        } else if (judgeover_val == 2) {
            printf("Congratulations! You win.\n");
            break;
        }
    }

    return 0;
}






