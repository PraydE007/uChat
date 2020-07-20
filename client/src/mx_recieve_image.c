#include "client.h"

void mx_recieve_image(char *json, t_s_glade *gui) {
    t_s_glade *gui = (t_s_glade *) data;
    json_object *jobj = json_tokener_parse(gui->recv_data);
    const char *name = json_to_str(jobj, "File_message");
    const char *sender = json_to_str(jobj, "Sender");
    int count = 0;
    int file_size = json_object_get_int(json_object_object_get(jobj, "File_size"));
    char *bunfer = malloc(sizeof(char) * size);

    recv(gui->sockfd, bunfer, size, MSG_WAITALL);

}
