#include <stdio.h>
#include <string.h>
void hillCipherEncrypt(int key[3][3], char plaintext[], char ciphertext[]) {
	int i,j,k;
    int len = strlen(plaintext);
    for (i = 0; i < len; i += 3) {
        int block[3] = {0};
        for (j = 0; j < 3 && i + j < len; j++) {
            block[j] = plaintext[i + j] - 'A';
        }
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                ciphertext[i + j] += key[j][k] * block[k];
            }
            ciphertext[i + j] = (ciphertext[i + j] % 26 + 26) % 26; 
            ciphertext[i + j] += 'A';
        }
    }
}
void hillCipherDecrypt(int key[3][3], char ciphertext[], char decryptedtext[]) {
	int i,j,k;
    int len = strlen(ciphertext);
    int determinant = key[0][0] * (key[1][1] * key[2][2] - key[1][2] * key[2][1]) -
                     key[0][1] * (key[1][0] * key[2][2] - key[1][2] * key[2][0]) +
                     key[0][2] * (key[1][0] * key[2][1] - key[1][1] * key[2][0]);

    int determinantInverse = 0;
    for (i = 0; i < 26; i++) {
        if ((determinant * i) % 26 == 1) {
            determinantInverse = i;
            break;
        }
    }

    int adjugate[3][3] = {
        {key[1][1] * key[2][2] - key[1][2] * key[2][1], key[0][2] * key[2][1] - key[0][1] * key[2][2], key[0][1] * key[1][2] - key[0][2] * key[1][1]},
        {key[1][2] * key[2][0] - key[1][0] * key[2][2], key[0][0] * key[2][2] - key[0][2] * key[2][0], key[0][2] * key[1][0] - key[0][0] * key[1][2]},
        {key[1][0] * key[2][1] - key[1][1] * key[2][0], key[0][1] * key[2][0] - key[0][0] * key[2][1], key[0][0] * key[1][1] - key[0][1] * key[1][0]}
    };
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            adjugate[i][j] = (adjugate[i][j] % 26 + 26) % 26;
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            adjugate[i][j] = (adjugate[i][j] * determinantInverse) % 26;
        }
    }

    for (i = 0; i < len; i += 3) {
        int block[3] = {0};
        for (j = 0; j < 3 && i + j < len; j++) {
            block[j] = ciphertext[i + j] - 'A';
        }
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                decryptedtext[i + j] += adjugate[j][k] * block[k];
            }
            decryptedtext[i + j] = (decryptedtext[i + j] % 26 + 26) % 26; 
            decryptedtext[i + j] += 'A'; 
        }
    }
}

int main() {
    int key[3][3] = {
        {6, 24, 1},
        {13, 16, 10},
        {20, 17, 15}
    };

    char plaintext[] = "HELLOHILLCIPHER";
    char ciphertext[100] = {0};
    char decryptedtext[100] = {0};

    printf("Original message: %s\n", plaintext);
    hillCipherEncrypt(key, plaintext, ciphertext);
    printf("Encrypted message: %s\n", ciphertext);
    hillCipherDecrypt(key, ciphertext, decryptedtext);
    printf("Decrypted message: %s\n", decryptedtext);

    return 0;
}
