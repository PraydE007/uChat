#include "client.h"

static const char *json_to_str(json_object *jobj, char *key) {
    const char *value = NULL;

    value = json_object_get_string(json_object_object_get(jobj, key));
    return value;
}

gboolean mx_recieve_image(void *data) {
    t_s_glade *gui = (t_s_glade *) data;
    json_object *jobj = json_tokener_parse(gui->recv_data);
    const char *name = json_to_str(jobj, "File_message");
    // const char *sender = json_to_str(jobj, "Sender");

    int file_size = json_object_get_int(json_object_object_get(jobj, "File_size"));
    char *bunfer = malloc(sizeof(char) * file_size);
    printf("%s\n", "TEST1");
    recv(gui->sockfd, bunfer, file_size, MSG_WAITALL);
    printf("%s\n", "TEST2");

    int potok = open(name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            // recv(sockbd.sockfd, bunfer, size, MSG_WAITALL);
    write(potok, bunfer, file_size);
    close(potok);
    return 0;
}
