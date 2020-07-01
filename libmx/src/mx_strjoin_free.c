#include "../inc/libmx.h"

char *mx_strjoin_free(char *s1, const char *s2) {
    char *join = NULL;
    int i;

    if (s1 == NULL && s2 == NULL) 
        return NULL;
    else if (s1 == NULL) 
        join = mx_strdup(s2);
    else if (s2 == NULL)
        join = mx_strdup(s1);
    else {
        join = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
        for (i = 0; i < mx_strlen(s1); i++)
            join[i] = s1[i];
        for (int j = 0; j < mx_strlen(s2); j++, i++)
            join[i] = s2[j];
        join[i] = '\0';
    }
    mx_strdel(&s1);
    return join;
}
