#include "client.h"
/*
static void write_file(int socket, char *path, int size) {
    char *image = mx_strnew(size);
    int bytes = 0;
    int fd_open = open(path, O_RDONLY);
    printf("PATH - %s\n", path);
    int buf_size = size;
    int least_b = 0;

    if (size <= 1024)
        bytes = size;
    else {
        bytes = 1024;
        least_b = size % 1024;
    }
//    printf("TEST = %s\n", test);
    printf("open file- %d, size §- %d\n", fd_open, buf_size);
    memset(image, 0, 1024);
    while (buf_size > 0) {
        size = read(fd_open, image, bytes);

        json_object *jobj = json_object_new_object();
        json_object *j_type = json_object_new_string("Picture");
//        json_object *j_pic = json_object_new_string_len(image, bytes);
        json_object *j_pic = json_object_new_string_len(image, 1024);
        json_object *j_size = json_object_new_string(mx_itoa(bytes));
        json_object_object_add(jobj, "Type", j_type);
        json_object_object_add(jobj, "Data", j_pic);
        json_object_object_add(jobj, "Size", j_size);
        char *result = (char *)json_object_to_json_string(jobj);
//        printf("RESULT = %s\n", result);
//        printf("JSON LEN = %lu\n", strlen(result));
        printf("SIZE = %lu\n", strlen(result));
//    write(1, image, 43388);
//    write(1, result, 43388);

        send(socket, result, strlen(result), 0);
        buf_size = buf_size - 1024;
        if (buf_size < 1024)
            bytes = least_b;
        if (size == -1)
            break;
        memset(image, 0, 1024);
    }
    printf("now here\n");
    close(fd_open);
}*/
<<<<<<< HEAD
static void write_file(int sockfd, char *file, int size) {
    char *image = mx_strnew(size);
=======

static char *get_file_name(char *file) {
    char *res = mx_strnew(mx_strlen(file));
    int count_slash = 0;
    int count_res = 0;
    if(file) {
        for (int i = 0; i < mx_strlen(file); i++) {
            if (file[i] == '/')
                count_slash = i;
        }
        count_slash++;
        while(file[count_slash]) {
            res[count_res] = file[count_slash];
            count_slash++;
            count_res++;
        }
    }
    return res;

}

static void write_file(int sockfd, char *file, int size, t_s_glade *gui) {
    char image[size];
    int status = 0;
    int fd_open = open(file, O_RDONLY);
    char *file_name = get_file_name(file);
    char *result = NULL;
    char *login = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));

    printf("NAME : %s\n", file_name);
    status = read(fd_open, image, size);
    printf("SIZE = %d\n", size);
    json_object *jobj = json_object_new_object();
    json_object *j_type = json_object_new_string("File");
    json_object *j_name = json_object_new_string(file_name);
    json_object *j_size = json_object_new_string(mx_itoa(size));
    json_object *j_login = json_object_new_string(login);
    json_object *j_chat = json_object_new_string(gui->send_to);
    json_object *j_key = json_object_new_string(gui->key);
    json_object_object_add(jobj, "Type", j_type);
    json_object_object_add(jobj, "Name", j_name);
    json_object_object_add(jobj, "Size", j_size);
    json_object_object_add(jobj, "Login", j_login);
    json_object_object_add(jobj, "Chat_name", j_chat);
    json_object_object_add(jobj, "Security_key", j_key);
    result = (char *)json_object_to_json_string(jobj);
    if (file) {
        mx_p_own(gui->l_messages, "!!FILE!!", login);
        printf("ReSULT = %s\n", result);
        send(sockfd, result, strlen(result), 0);
        printf("OTPRAVIL\n");
        send(sockfd, image, size, 0);
    }
    close(fd_open);
}


//static void write_file(int sockfd, char *file, int size) {
//    char *image = mx_strnew(size);
//    int status = 0;
//    int fd_open = open(file, O_RDONLY);
//
//    printf("SIZE = %d\n", size);
//    status = read(fd_open, image, size);
//    write(1, image, 43388);
//    send(sockfd, image, size, 0);
//}

void mx_send_image(const char *file, int sockfd, t_s_glade *gui) {
    struct stat lt;
    int file_size = 0;

    stat(file, &lt);
    file_size = lt.st_size;
    write_file(sockfd, (char *)file, file_size, gui);
}
