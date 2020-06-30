#include "client.h"

int check_mail_else_body(const char *mail, int i) {
    i++;
    if (isalpha(mail[i]) || isdigit(mail[i])) {
        while (isalpha(mail[i]) || isdigit(mail[i]))
            i++;
        if (mail[i] != '.')
            return 1;
        else {
            i++;
            if (isalpha(mail[i]) || isdigit(mail[i])) {
                while (isalpha(mail[i]) || isdigit(mail[i]))
                    i++;
                if (i == mx_strlen(mail))
                    return 0;
            }
        }
    }
    return 1;
}

int mx_check_mail(const char *mail, int i) {
    if (isalpha(mail[0]) || isdigit(mail[0])
        || mail[0] == '.' || mail[0] == '_') {
        while (isalpha(mail[i]) || isdigit(mail[i])
               || mail[i] == '.' || mail[i] == '_')
            i++;
        if (mail[i] != '@')
            return 1;
        else
            return check_mail_else_body(mail, i);
    }
    return 1;
}
