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
    mx_printstr(file);
    mx_printstr("\n");
    char *image = malloc(sizeof(char) * size);
    int status = 0;
    mx_printstr("xzcxz\n");
    int fd_open = open(file, O_RDONLY);
    mx_printstr("PPPPPP\n");
    char *file_name = get_file_name(file);
    char *result = NULL;
    char *login = (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_l_login));

    memset(image, '\0', size);
    printf("NAME : %s\n", file_name);
    status = read(fd_open, image, size);
    printf("gui-login = %s\n", (char *)gtk_entry_get_text(GTK_ENTRY(gui->e_l_login)));
    printf("SIZE = %d\n", size);
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
        printf("ReSULT = %s\n", result);
        /// ВАЖНО ДЕЛАТЬ ПЕРВЫЙ СЕНД НА ВСЮ ПАМЯТЬ СТЕКА(БУФФЕРА В ДУПРОЦЕССИНГЕ), ЧТО БЫ ПАМЯТЬ НЕ ПЕРЕКРАИВАЛАСЬ
        /// И ФАЙЛЫ ПЕРЕДАВАЛИСЬ ПОЛНОСТЬЮ. НА КЛИНТЕ СОКЕТ = 3 А НА СЕРВЕРЕ СОКЕТ = 6. ТАК И ДОЛЖНО БЫТЬ?
        /// ПИШИТЕ НЕ СТЕСНЯЙТЕСЬ  =*
        send(sockfd, result, MX_MAX_BYTES, 0);
        printf("OTPRAVIL\n");
        send(sockfd, image, size, 0);

    }
    close(fd_open);
}

void mx_send_image(const char *file, int sockfd, t_s_glade *gui) {
    struct stat lt;
    int file_size = 0;

    stat(file, &lt);
    file_size = lt.st_size;
    printf("SOCKET = %d\n", sockfd);
    write_file(sockfd, (char *)file, file_size, gui);
}
