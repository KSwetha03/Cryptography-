#include <stdio.h>
#include <string.h>
void polySubstitution(char *plaintext, char *key) {
 int plainLen = strlen(plaintext);
 int keyLen = strlen(key);
 for (int i = 0; i < plainLen; i++) {
 int keyOffset = key[i % keyLen] - 'A';
 if (isalpha(plaintext[i])) {
 char base = islower(plaintext[i]) ? 'a' : 'A';
 char shiftedChar = (plaintext[i] - base + keyOffset) % 26 + base;
 printf("%c", shiftedChar);
 } else {
 printf("%c", plaintext[i]);
 }
 }
}
int main() {
 char plaintext[100];
 char key[100];
 printf("Enter the plaintext: ");
 fgets(plaintext, sizeof(plaintext), stdin);
 plaintext[strcspn(plaintext, "\n")] = '\0'; 
 printf("Enter the key: ");
 fgets(key, sizeof(key), stdin);
 key[strcspn(key, "\n")] = '\0'; 
 printf("Encrypted text: ");
 polySubstitution(plaintext, key);
 printf("\n");
 return 0;
}
