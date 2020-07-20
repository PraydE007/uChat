#include "client.h"

static int get_rand(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

void mx_push_message(GtkWidget *lst, const char *msg, const char *owner) {
    if (get_rand(0, 1))
        mx_p_own(lst, msg, owner);
    else
        mx_p_owned(lst, msg, owner);
}
