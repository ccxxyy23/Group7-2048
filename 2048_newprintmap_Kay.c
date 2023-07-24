/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 4

int MAX_GRID = SIZE;
int map[SIZE][SIZE];
bool flag = false;

void printMap() {
    // Print the top border
    printf("+");
    for (int i = 0; i < SIZE; i++) {
        printf("-----+");
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("|");
            if (map[i][j] == 0) {
                printf("     ");
            } else {
                printf("%-5d", map[i][j]);
            }
        }
        printf("|\n");

        // Print the middle border
        printf("+");
        for (int j = 0; j < SIZE; j++) {
            printf("-----+");
        }
        printf("\n");
    }
}


bool isAvailable() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (map[i][j] == 0) {
                return true; // 如果有空格子，返回true
            }
        }
    }
    return false; // 所有格子都填满了，返回false
}


bool isFull() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (map[i][j] == 0) {
                return false; // 如果有空格子，返回false
            }
        }
    }
    return true; // 所有格子都填满了，返回true
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
                }
                // if the two numbers equal, add together
                if(map[temp][i] == map[begin][i]) {
                    map[temp][i] += map[begin][i];
                    map[begin][i] = 0;
                    temp++;
                }
                // if not equal, move to the temp which is the place of temp + 1
                // notice if the temp+1 is not the current place, release
                else{
                    map[temp + 1][i] = map[begin][i];
                    if ((temp + 1) != begin) {
                        map[begin][i] = 0;
                    }
                    temp++;
                }
                flag = true;
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
                } else if (map[temp][j] == map[i][j]) {
                    map[temp][j] += map[i][j];
                    map[i][j] = 0;
                    temp--;
                } else {
                    map[temp - 1][j] = map[i][j];
                    if (temp - 1 != i) {
                        map[i][j] = 0;
                    }
                    temp--;
                }
                flag = true;
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
                } else if (map[i][temp] == map[i][j]) {
                    map[i][temp] += map[i][j];
                    map[i][j] = 0;
                    temp++;
                } else {
                    map[i][temp + 1] = map[i][j];
                    if (temp + 1 != j) {
                        map[i][j] = 0;
                    }
                    temp++;
                }
                flag = true;
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
                } else if (map[i][temp] == map[i][j]) {
                    map[i][temp] += map[i][j];
                    map[i][j] = 0;
                    temp--;
                } else {
                    map[i][temp - 1] = map[i][j];
                    if (temp - 1 != j) {
                        map[i][j] = 0;
                    }
                    temp--;
                }
                flag = true;
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

    int gameStatus = judgeover();
    if (gameStatus == 2) {
        printf("Congratulations! You win.\n");
        exit(0);
    } else if (gameStatus == 0) {
        if (!isAvailable()) {
            printf("Game Over. No more moves!\n");
            exit(0);
        }
    }
}


void GameControl1() {
    char key;
    bool validMove = false;
    printf("next step: w/W s/S a/A d/D \n");
    
    while (!validMove) {
        scanf(" %c", &key); // Add a space before %c to consume any leading whitespace
        getchar(); // Consume the newline character

        switch (key) {
            case 'w':
            case 'W':
                moveup();
                validMove = true;
                break;
            case 's':
            case 'S':
                movedown();
                validMove = true;
                break;
            case 'a':
            case 'A':
                moveleft();
                validMove = true;
                break;
            case 'd':
            case 'D':
                moveright();
                validMove = true;
                break;
            default:
                printf("Invalid input. Please enter a valid move: ");
                break;
        }
    }
}


int main() {
    srand(time(NULL)); // Initialize random seed

    // Initialize the game map
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            map[i][j] = 0;
        }
    }

    Createnumber();
    Createnumber();
    printMap();

    while (true) {
        GameControl1();
        Gamejudge();
        printMap();
        
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
