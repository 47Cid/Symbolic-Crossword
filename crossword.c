#include <stdio.h>
#include <klee/klee.h>

#define SIZE 3
#define BLANKS 4

void printPuzzle(char puzzle[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", puzzle[i][j]);
        }
        printf("\n");
    }
}

void getInput(char puzzle[SIZE][SIZE], char solution[BLANKS], int index) {
    // Get user input for the puzzle
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if(puzzle[i][j] == '.'){
                printf("Enter value for puzzle[%d][%d]: ", i, j);
                char a; 
                klee_make_symbolic(&a, sizeof(a), "a");
                puzzle[i][j] = a;

                //scanf(" %c", &puzzle[i][j]);
                printPuzzle(puzzle);

                if (puzzle[i][j] == solution[index]) {
                    printf("Correct!\n");
                    klee_assert(0);  
                } else {
                    printf("Incorrect. Expected: %c\n", solution[i]);
                }

                return;
            }
        }
    }
}

int main() {
    int i = 0;

    char solution[BLANKS] = {'N', 'G', 'O', 'W'};
    char puzzle[SIZE][SIZE] = {
        {'C', 'A', '.'},
        {'A', '.', 'E'},
        {'N', '.', '.'},
    };

    printPuzzle(puzzle);

    while (i <= BLANKS){
        getInput(puzzle, solution, i);
        i++;
    }

    return 0;
}
