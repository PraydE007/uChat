#include "client.h"

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
    char *image = malloc(sizeof(char) * size);
    int status = 0;
    int fd_open = open(file, O_RDONLY);
    char *file_name = get_file_name(file);
    char *result;
    char *login = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));

    memset(image, '\0', size);
    status = read(fd_open, image, size);
    json_object *jobj = json_object_new_object();
    json_object *j_type = json_object_new_string("File");
    json_object *j_name = json_object_new_string(file_name);
    json_object *j_size = json_object_new_string(mx_itoa(size));
    json_object *j_login = json_object_new_string(login);
    json_object *j_chat = json_object_new_string(gui->send_to);
    json_object *j_key = json_object_new_string(gui->key);
    json_object_object_add(jobj, "Type", j_type);
    json_object_object_add(jobj, "Message", j_name);
    json_object_object_add(jobj, "Size", j_size);
    json_object_object_add(jobj, "Login", j_login);
    json_object_object_add(jobj, "Chat_name", j_chat);
    json_object_object_add(jobj, "Security_key", j_key);
    result = (char *)json_object_to_json_string(jobj);

    if (file) {
        mx_p_own_img(gui->l_messages, file, gui->send_to);
        write(sockfd, result, MX_MAX_BYTES);
        send(sockfd, image, size, MSG_WAITALL);
    }
    close(fd_open);
}

void mx_send_image(const char *file, int sockfd, t_s_glade *gui) {
    struct stat lt;
    int file_size = 0;

    stat(file, &lt);
    file_size = lt.st_size;
    write_file(sockfd, (char *)file, file_size, gui);
}
