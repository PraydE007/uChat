#include "client.h"


void *mx_client_recv(void *data) {
    int n = 0;
    t_s_glade *gui = *(t_s_glade **)data;
    char *answer = NULL;
    json_object *jobj;

    while (true) {
        bzero(gui->buffer, MX_MAX_BYTES);
        n = recv(gui->sockfd, gui->buffer, MX_MAX_BYTES, 0);
        jobj = json_tokener_parse(gui->buffer);
        gui->recv_data = strdup(gui->buffer);
        printf("RECV DATA: %s\n", gui->recv_data);
        answer = (char *)json_object_get_string(json_object_object_get(jobj, "Answer"));
        if (!mx_strcmp(answer, "You have logged in!")) {
            gui->key = (char *)json_object_get_string(json_object_object_get(jobj, "Security_key"));
            printf("%s\n", gui->recv_data);
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_success_logging, gui, 0);
        }
        if (!mx_strcmp(answer, "You have registered successfully!"))
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_success_registr, gui, 0);
        if (!mx_strcmp(answer, "Profile info!"))
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_success_profile, gui, 0);
        if (!mx_strcmp(answer, "Profile data are changed!"))
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_success_change_profile, gui, 0);
        if (!mx_strcmp(answer, "The password were changed!"))
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_success_change_passwd, gui, 0);
        else {
            continue;
        }

    }
    return NULL;
}
