#include "server.h"

static void write_file(int sockfd, char *file, int size) {
    char *image = mx_strnew(size);
printf("file!!! = %s\n", file);
    int fd_open = open(file, O_RDONLY);
    int status = 0;

    status = read(fd_open, image, size);
printf("SIZE = %d\n", size);//
printf("status = %d\n", status);//
printf("SOCKET = %d\n", sockfd);//
printf("image = %s\n", image);//
    if (status >= 0)
        send(sockfd, image, size, 0);
    close(fd_open);
    mx_strdel(&image);
}

void mx_send_image_from_server(const char *file, int sockfd, int size) {
    json_object *j_result = json_object_new_object();
    const char *answer = NULL;
    struct stat lt;
    int file_size = 0;

    stat(file, &lt);
    file_size = lt.st_size;
printf("file_size = %d\n", file_size);
printf("size = %d\n", size);
    if (file_size == size)
        write_file(sockfd, (char *)file, file_size);
    else {
        mx_add_str_to_js(j_result, "Answer", "The file is broken!");
        answer = json_object_to_json_string(j_result);
        send(sockfd, answer, mx_strlen(answer), 0);
    }
}