#include "client.h"

char *mx_cat_message(char *message) {
    char *res = NULL;
    int count_space = mx_strlen(message) / 60;
    int count = 0;

    if (count_space == 0)
        return message;
    if (mx_strlen(message) < 60)
        return message;
    res = mx_strnew(mx_strlen(message) + count_space);
    for (int i = 0; message[i]; i++) {
        if (i % 60 == 0 && i != 0 && message[i] != ' ') {
            res[count] = ' ';
            count++;
        }
        res[count] = message[i];
        count++;
    }
    return res;
}
