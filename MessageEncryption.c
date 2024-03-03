#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int private_key;
int public_key;
int length;
int n;

int is_prime(int n) {

    if (n <= 1)
        return 0;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int random_prime(int min, int max) {

    srand(time(NULL));

    int p;

    do {
        p = rand() % (max - min + 1) + min;
    } while (!is_prime(p));

    return p;
}

int gcd(int a, int b) {

    int rest;
    while(1) {
        rest = a % b;
        if(rest == 0) return b;
        a = b;
        b = rest;
    }
}

// Creating Keys
void setKeys() {

    int prime1 = random_prime(100, 150);
    int prime2;
    do{
        prime2 = random_prime(100, 150);
    }while(prime1 == prime2);

    n = prime1 * prime2;

    int e = 2;
    int phi = (prime1 - 1) * (prime2 - 1) / gcd(prime1 - 1, prime2 - 1);

    while (e < phi) {
        if (gcd(e, phi) == 1)
            break;
        else
            e++;
    }
    public_key = e;

    int d = 2;
    while (1) {
        if ((d * e) % phi == 1) {
            break;
        }
        d++;
    }
    private_key = d;
}

// Encrypting Message
long long int encrypt(int message) {
    int e = public_key;
    long long int encrpyted_text = 1;

    while (e--) {
        encrpyted_text *= message;
        encrpyted_text %= n;
    }
    return encrpyted_text;
}

// Decrypting Message
long long int decrypt(int encrpyted_text) {

    int d = private_key;
    long long int decrypted = 1;
    while (d--) {
        decrypted *= encrpyted_text;
        decrypted %= n;
    }
    return decrypted;
}

int *encoder(char *message) {

    length = strlen(message);
    int *coded = (int *)malloc(sizeof(int) * length);

    printf("\nThe encoded message(encrypted by public key)\n");
    for (int i = 0; i < length; i++) {
        coded[i] = encrypt((int)message[i]);
        printf("%d ", coded[i]);
    }

    return coded;
}

void decoder(int *encoded) {

    char *string_decoded = malloc(sizeof(char) * (length + 1));
    int i;
    printf("\n");

    for (i = 0; i < length; i++) {
        int decrypted = decrypt(encoded[i]);
        printf("%d ", decrypted);
        string_decoded[i] = decrypted;
    }
    string_decoded[i] = '\0';

    printf("\n\nThe decoded message(decrypted by private key):\n%s\n", string_decoded);
    free(string_decoded);
    free(encoded);
}

int main() {

    setKeys();
    char * message;
    message = "I want to shoot a seagull.";
    printf("Initial message:  %s", message);
    printf("\n");

    int * encoded_message = encoder(message);
    decoder(encoded_message);

    return 0;
}

