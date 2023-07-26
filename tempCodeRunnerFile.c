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