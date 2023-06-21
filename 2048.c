#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4

int board[SIZE][SIZE];

// Function to initialize the board with zeros
void initializeBoard() {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

// Function to print the current state of the board
void printBoard() {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%d\t", board[i][j]);
        }
        printf("\n");
    }
}

// Function to add a new random number (2 or 4) to the board
void addRandomNumber() {
    int i, j;
    int emptyCells[SIZE * SIZE][2];
    int count = 0;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                emptyCells[count][0] = i;
                emptyCells[count][1] = j;
                count++;
            }
        }
    }

    if (count > 0) {
        int randomIndex = rand() % count;
        int randomValue = (rand() % 2 + 1) * 2; // Randomly choose 2 or 4
        int x = emptyCells[randomIndex][0];
        int y = emptyCells[randomIndex][1];
        board[x][y] = randomValue;
    }
}

// Function to handle the player's move
void makeMove(char direction) {
    // Implement the logic to move the tiles and merge them based on the direction

    // Example implementation for left movement:
    // ...
    // ...

    // After making the move, add a new random number to the board
    addRandomNumber();
}

int main() {
    // Seed the random number generator
    srand(time(0));

    // Initialize the board
    initializeBoard();

    // Add two initial random numbers
    addRandomNumber();
    addRandomNumber();

    // Game loop
    char move;
    while (1) {
        // Print the board
        printBoard();

        // Get the player's move
        printf("Enter your move (w: up, s: down, a: left, d: right, q: quit): ");
        scanf(" %c", &move);

        // Handle the player's move
        if (move == 'q') {
            break; // Quit the game
        } else {
            makeMove(move);
        }
    }

    return 0;
}