#include <stdio.h>
#include <string.h>
#define SIZE 5
char playfairMatrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};
void findPosition(char ch, int *row, int *col) {
    if (ch == 'J') 
        ch = 'I';

    for (*row = 0; *row < SIZE; (*row)++) {
        for (*col = 0; *col < SIZE; (*col)++) {
            if (playfairMatrix[*row][*col] == ch)
                return;
        }
    }
}
void encryptDigraph(char digraph[2], char cipher[2]) {
    int row1, col1, row2, col2;

    findPosition(digraph[0], &row1, &col1);
    findPosition(digraph[1], &row2, &col2);
    if (row1 == row2) {
        cipher[0] = playfairMatrix[row1][(col1 + 1) % SIZE];
        cipher[1] = playfairMatrix[row2][(col2 + 1) % SIZE];
    }
    else if (col1 == col2) {
        cipher[0] = playfairMatrix[(row1 + 1) % SIZE][col1];
        cipher[1] = playfairMatrix[(row2 + 1) % SIZE][col2];
    }
    else {
        cipher[0] = playfairMatrix[row1][col2];
        cipher[1] = playfairMatrix[row2][col1];
    }
}
void playfairEncrypt(char *message) {
    int i, j;
    char digraph[2], cipher[2];
    for (i = 0; i < strlen(message); i += 2) {
        if (message[i] == message[i + 1]) {
            message[i + 1] = 'X';
        }
    }
    for (i = 0; i < strlen(message); i += 2) {
        digraph[0] = message[i];
        digraph[1] = message[i + 1];

        encryptDigraph(digraph, cipher);

        printf("%c%c %c%c ", digraph[0], digraph[1], cipher[0], cipher[1]);
    }
}

int main() {
    char message[] = "MUSTSEEYOUOVERCADOGANWESTCOMINGATONCE";
    
    printf("Original Message: %s\n", message);
    
    printf("Encrypted Message: ");
    playfairEncrypt(message);
    
    return 0;
}
