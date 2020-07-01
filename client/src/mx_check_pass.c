#include "client.h"

int mx_check_pass(const char *pass, int j) {
    if (isalpha(pass[0]) || isdigit(pass[0])) {
        for (; pass[j]; j++) {
            if (!isalpha(pass[j]) && !isdigit(pass[j]))
                return 1;
        }
        return 0;
    }
    return 1;
}
