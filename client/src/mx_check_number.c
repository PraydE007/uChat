#include "client.h"

int mx_check_number(const char *number, int j) {
    if (number[0] == '+') {
        while (isdigit(number[j])) {
            j++;
            if (strlen(number) == 13)
                return 0;
        }
    }
    return 1;
}
