#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void createPlayfairMatrix(char key[], char matrix[SIZE][SIZE]) {
    int i, j;
    int k = 0;
    int keyLen = strlen(key);
    char usedChars[26] = {0};
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            matrix[i][j] = ' ';
        }
    }
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (k < keyLen) {
                char c = toupper(key[k]);
                if (c == 'J') c = 'I';
                if (usedChars[c - 'A'] == 0) {
                    matrix[i][j] = c;
                    usedChars[c - 'A'] = 1;
                    k++;
                }
            }
        }
    }
    char currentChar = 'A';
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ' ') {
                while (usedChars[currentChar - 'A'] != 0) {
                    currentChar++;
                }
                matrix[i][j] = currentChar;
                usedChars[currentChar - 'A'] = 1;
            }
        }
    }
}
void findPosition(char matrix[SIZE][SIZE], char c, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (matrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void playfairEncrypt(char matrix[SIZE][SIZE], char message[]) {
    int len = strlen(message);
    int i,j;
    for (i = 0; i < len; i++) {
        if (message[i] == ' ') {
            for (j = i; j < len; j++) {
                message[j] = message[j + 1];
            }
            len--;
        }
    }
    if (len % 2 != 0) {
        message[len] = 'X';
        len++;
    }
    for (i = 0; i < len; i += 2) {
        int row1, col1, row2, col2;
        char a = toupper(message[i]);
        char b = toupper(message[i + 1]);

        findPosition(matrix, a, &row1, &col1);
        findPosition(matrix, b, &row2, &col2);
        if (row1 == row2) {
            col1 = (col1 + 1) % SIZE;
            col2 = (col2 + 1) % SIZE;
        }
        else if (col1 == col2) {
            row1 = (row1 + 1) % SIZE;
            row2 = (row2 + 1) % SIZE;
        }
        else {
            int temp = col1;
            col1 = col2;
            col2 = temp;
        }

        printf("%c%c%c%c", matrix[row1][col1], matrix[row2][col2], ' ', ' ');
    }
}

int main() {
    char key[] = "MFHIJKUNOPQZVWXYELARGBDSTBC";
    char matrix[SIZE][SIZE];
    createPlayfairMatrix(key,matrix);

    char message[] = "Must see you over Cadogan West. Coming at once.";
    playfairEncrypt(matrix, message);

    return 0;
}
