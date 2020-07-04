#include "client.h"

int get_rand(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

// OLD FUNCTION
void mx_push_message(GtkWidget *lst, const char *msg, const char *owner) {
    (void)owner;
    if (get_rand(0, 1))
        mx_p_own(lst, msg);
    else
        mx_p_owned(lst, msg);
}
