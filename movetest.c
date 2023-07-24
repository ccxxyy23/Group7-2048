#include <stdio.h>

#define SIZE 4

int map[SIZE][SIZE] = {
    {2, 2, 4, 2},
    {2, 2, 4, 8},
    {4, 8, 0, 8},
    {16, 16, 16, 16}
};

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
                // the final number of this grid can be added to the total score
                if(map[temp][i] == map[begin][i]) {
                    map[temp][i] += map[begin][i];
                    map[begin][i] = 0;
                    // add this line to avoid redundant merge
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
            }
        }
    }
}

void printMap() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%-5d", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


int main() {
    printf("Before moving up:\n");
    printMap();

    moveup();

    printf("After moving up:\n");
    printMap();

    return 0;
}
