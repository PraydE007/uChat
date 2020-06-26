#include <server.h>

int mx_create_log() {
    int file_descr = 0;

    file_descr = open("uchat_server.log", O_CREAT | O_RDWR | O_APPEND, S_IREAD | S_IWRITE);
    return file_descr;
}
