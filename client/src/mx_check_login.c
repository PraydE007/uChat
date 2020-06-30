#include "client.h"

int mx_check_login(const char *login, int j) {
    if (isalpha(login[0]) || isdigit(login[0])) {
        for (; login[j]; j++) {
            if (!isalpha(login[j]) && !isdigit(login[j]))
                return 1;
        }
        return 0;
    }
    return 1;
}
