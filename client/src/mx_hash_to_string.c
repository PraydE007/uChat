#include "client.h"

char *mx_hash_to_string(unsigned char *hash) {
    char *string = (char *)malloc(sizeof(char) * SHA512_DIGEST_LENGTH + 1);
    int a;
    int count = 0;
    char MAS[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                    'a', 'b', 'c', 'd', 'e', 'f'};

    for (int i = 0; i < 32; i++) {
        a = hash[i] / 16;
        string[count++] = MAS[a];
        a = hash[i] % 16;
        string[count++] = MAS[a];
    }
    string[SHA512_DIGEST_LENGTH + 1] = '\0';
    return string;
}

char *mx_hash(char *pass) {
    unsigned char sha512[SHA512_DIGEST_LENGTH];
    char *hash;

    asprintf(&hash, "%s", pass);
    SHA512((unsigned char *)hash, strlen(hash), sha512);
    free(hash);
    return mx_hash_to_string(sha512);
}
