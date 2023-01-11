#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

char generate_random_char() {
    int r = rand();
    if (r % 2 == 0) {
        // Génère un chiffre (0-9)
        return '0' + (r % 10);
    } else {
        // Génère une lettre (A-Z ou a-z)
        return 'A' + (r % 26);
    }
}

// Génère et retourne un UID aléatoire de 8 caractères
char* generate_uid() {
    // Crée un tableau de 9 caractères (8 pour l'UID + 1 pour le caractère de fin de chaîne)
    char *uid = (char*) malloc(9);
    int i;
    // Génère les 8 caractères de l'UID
    for (i = 0; i < 8; i++) {
        uid[i] = generate_random_char();
    }
    // Ajoute un caractère de fin de chaîne
    uid[8] = '\0';
    return uid;
}

// Fonction de chiffrement de César qui prend en entrée un message en clair (plaintext)
// et un décalage (shift). Le message est modifié en place pour qu'il soit chiffré.
void encrypt(char *plaintext, int shift) {
    int i;
    // Détermine la longueur du message
    int length = strlen(plaintext);
    // Parcours tous les caractères du message
    for (i = 0; i < length; i++) {
        char c = plaintext[i];
        // Si le caractère est une lettre minuscules, décale-le de "shift" places
        if (c >= 'a' && c <= 'z') {
            c = (c - 'a' + shift) % 26 + 'a';
        }
        // Si le caractère est une lettre majuscule, décale-le de "shift" places
        else if (c >= 'A' && c <= 'Z') {
            c = (c - 'A' + shift) % 26 + 'A';
        }
        // Remplace le caractère dans le message par le caractère décalé
        plaintext[i] = c;
    }
}

// Fonction de déchiffrement de César qui prend en entrée un message chiffré (ciphertext)
// et un décalage (shift). Le message est modifié en place pour qu'il soit déchiffré.
void decrypt(char *ciphertext, int shift) {
    int i;
    // Détermine la longueur du message
    int length = strlen(ciphertext);
    // Parcours tous les caractères du message
    for (i = 0; i < length; i++) {
        char c = ciphertext[i];
        // Si le caractère est une lettre minuscules, décale-le de "shift" places en arrière
        if (c >= 'a' && c <= 'z') {
            c = (c - 'a' - shift + 26) % 26 + 'a';
        }
        // Si le caractère est une lettre majuscule, décale-le de "shift" places en arrière
        else if (c >= 'A' && c <= 'Z') {
            c = (c - 'A' - shift + 26) % 26 + 'A';
        }
        // Remplace le caractère dans le message par le caractère décalé
        ciphertext[i] = c;
    }
}