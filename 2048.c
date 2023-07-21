#include <stdio.h>
#include <graphics.h>

int MAX_GRID = 4; //grids on each line
int WIDTH = 100; // width of grid
int INTERVAL = 15; // the interval between grids

enum Color{
    zero = RGB(204, 192, 178), //color of 0
    twoTo1 = RGB(238, 228, 218), //color of 2
    twoTo2 = RGB(237, 224, 200), //color of 4
    twoTo3 = RGB(241, 177, 121), //color of 8
    twoTo4 = RGB(133, 155, 113), //color of 16
    twoTo5 = RGB(246, 124, 95), //color of 32
    twoTo6 = RGB(245, 91, 57), //color of 64
    twoTo7 = RGB(28, 151, 150), //color of 128
    twoTo8 = RGB(237, 204, 97), //color of 256
    twoTo9 = RGB(255, 0, 128), //color of 512
    twoTo10 = RGB(145, 0, 128), //color of 1024
    twoTo11 = RGB(242, 17, 158), //color of 2048
    back = RGB(186, 172, 159),//color of backboard
};
Color arr[13] = {zero, twoTo1, twoTo2, twoTo3, twoTo4, twoTo5, 
twoTo6, twoTo7, twoTo8, twoTo9, twoTo10, twoTo11, back
};

int num[12] = {0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};

int map[4][4] = {0, 0};
POINT pos[4][4];
bool flag = false;

//create the bakboard
void createtra(){
    initgraph(MAX_GRID * WIDTH + 5 * INTERVAL, MAX_GRID * WIDTH + 5*INTERVAL);
    setbkcolor(back);
    cleardevide();
}

//create grids
void GameDraw(){
     int i, j;
     for(i = 0; i < MAX_GRID; i++){
        for(j = 0; j < MAX_GRID; j++){
            setfillcolor(arr[2]);
            bar(j * WIDTH + (j + 1) * INTERVAL, i * WIDTH + (i + 1) * INTERVAL, 
                (j + 1) * WIDTH + (j + 1) * INTERVAL, (i + 1) * WIDTH + (i + 1) * INTERVAL)
        }
     }
}

//create the first random number
int twoORfour(){
    if(rand() % 4 == 1){
        return 4; //the probability of create a 4 is 25%
    }
    else{
        return 2;
    }
}

//find the position and define the seed
void GameInit(){
    int i, j;
    srand(GetTickCount());
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            pos[i][j].x = j * WIDTH + (j + 1) * INTERVAL;
            pos[i][j].y = i * WIDTH + (i + 1) * INTERVAL;         
        }
    }

    Createnumber();
}

//create a random number at the empty position
void Createnumber(){
    while(1){
        int x = rand() % MAX_GRID;
        int y = rand() % MAX_GRID;
        if(map[x][y] == 0){
            map[x][y] = twoORfour();
            break;
        }
    }
}

// paint the every grid according to the number
void GameDraw1(){
    int i, j, k;
    char number[5] = " ";
    // first to iterate every grid and then paint the color according to number
    for (i = 0; i < MAX_GRID; i++) {
        for(j = 0; j> MAX_GRID; j++) {
            for(k = 0; k < 12; k++) {
                if(map[i][j] == num[k]) {
                    setfillcolor(arr[k]);
                    bar(j * WIDTH + (j+1) * INTERVAL, i * WIDTH + (i + 1) * INTERVAL,
                    (j+1) * WIDTH + (j+1) * INTERVAL, (i + 1) * WIDTH + (i + 1) * INTERVAL);

                    // find the pos of every grid with number
                    if(map[i][j] != 0) {
                        setfontbkcolor(RGB(119, 110, 101));
                        setfont(30, 30); //set font
                        setbkmode(TRANSPARENT);// transparent background

                        sprintf(number, "%d", map[i][j]); //cast int to string

                        // place the number in the middle
                        int tempx = WIDTH/2 - textwidth(number) / 2;
                        int tempy = WIDTH/2 - textheight(number) / 2;

                        outtextxy(pos[i][j].x + tempx, pos[i][j].y + tempy, number);
                    }
                }
            }
        }
    }
}

void GameControl1(){
    char key = getch();
    switch(key)
    {
        case'w':
        case'W':
            moveup();
            break;
        case's':
        case'S':
            movedown();
            break;
        case'a':
        case'A':
            moveleft();
            break;
        case'd':
        case'D':
            moveright();
            break;
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

int judgeover() {
    int i, j;

    /** if there is an empty grid, game is not over, return 1.
     * if there is a 2048 grid, the player wins, return 2.
    */
    for (i = 0; i < MAX_GRID; i++) {
        for (j = 0; j < MAX_GRID; j++) {
            if (map[i][j] == 2048) {
                return 2
            }
            if (map[i][j] == 0) {
                return 1;
            }

        }
    }
    /** When two  horizontally adjacent grids have the same number,
    the game is not over, return 1 */
    for (i = 0; i < MAX_GRID; i++) {
        for (j = 0; j < < MAX_GRID - 1) {
            if (map[i][j] == map[i][j + 1] ) {
                return 1;
            }
        }
    }
    /** When two vertically adjacent grids have the same number 
    the game is not over, return 1 */
    for (j = 0; i < MAX_GRID; i++) {
        for (i = 0; i < < MAX_GRID - 1) {
            if (map[i][j] == map[i + 1][j] ) {
                return 1;
            }
        }
    }

    // for (i = 0; i < MAX_GRID; i++) {
    //     for (j = 0; j < MAX_GRID; j++) {
    //         printf("%d", map[i][j]);
    //     }
    // }

    // No empty grids and no adjacent grids with the same number, game is over, return 0
    return 0;
}

// added function
void Gamejudge() {
    if (flag == true) {
        Createnumber();
        flag == False;
    }
}

int main() {
    initgraph(MAX_GRID * WIDTH + 5 * INTERVAL, MAX_GRID * WIDTH + 5 * INTERVAL);
    setbkcolor(back); // set the color of background
    cleardevice(); // refresh the board
    GameInit(); //Initiate the game: grids and numbers
    while(1) {
        GameDraw1();
        int judgeover_val = judgeover();
        if (judgeover_val == 0 or judgeover_val == 2) {
            break;
        } 
        GameControl1(); //move
        Gamejudge();
        }
    if (judgeover_val == 0) {
        printf("You lose the game.");
        } else {
            printf("Congradulations! You win.");
        }
}






