#include "client.h"

char *mx_cat_message(char *message) {
    char *res = NULL;
    int count_space = mx_strlen(message) / 65;
    int count = 0;

    if (count_space == 0) {
        printf("%s\n", "TEST1");
        return message;
    }
    if (mx_strlen(message) < 65) {
        printf("%s\n", "TEST2");
        return message;
    }
    res = mx_strnew(mx_strlen(message) + count_space);
    for (int i = 0; message[i]; i++) {
        if (i % 65 == 0 && i != 0 && message[i] != ' ') {
            res[count] = ' ';
            count++;
        }
        res[count] = message[i];
        count++;
    }
    printf("%s\n", res);
    return res;
}
