#include "client.h"

void *mx_client_recv(void *data) {
    int n = 0;
    t_s_glade *gui = *(t_s_glade **)data;
    char *answer = NULL;
    json_object *jobj;

    while (true) {
        bzero(gui->buffer, MX_MAX_BYTES);
        n = recv(gui->sockfd, gui->buffer, MX_MAX_BYTES, 0);
        if (n <= 0)
            continue;
        jobj = json_tokener_parse(gui->buffer);
        gui->recv_data = strdup(gui->buffer);
        printf("RECV DATA: %s\n", gui->recv_data);
        answer = (char *)json_object_get_string(json_object_object_get(jobj, "Answer"));
        if (!mx_strcmp(answer, "Private message history!")) {
            gui->if_contact = 1;
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_success_history, gui, 0);
        }
        if (!mx_strcmp(answer, "Public message history!")) {
            gui->if_contact = 0;
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_success_history, gui, 0);
        }
        if (!mx_strcmp(answer, "You have logged in!")) {
            gui->if_contact = 2;
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
        if (!mx_strcmp(answer, "The contact was added!"))
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_success_add_contact, gui, 0);
        if (!mx_strcmp(answer, "Receive_message")) {
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_success_message, gui, 0);
        }
        if (!mx_strcmp(answer, "Public_receive_message"))
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_success_public_message, gui, 0);
        if (!mx_strcmp(answer, "The chat was created!"))
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_success_add_contact, gui, 0);
        if (!mx_strcmp(answer, "The user was added to the chat!"))
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_success_members_list, gui, 0);
        if (!mx_strcmp(answer, "You were added to the chat"))
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_success_invited, gui, 0);
        if (!mx_strcmp(answer, "The contact was deleted!"))
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_success_update_contacts, gui, 0);
        if (!mx_strcmp(answer, "The chat was deleted!"))
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_success_update_contacts, gui, 0);
        if (!mx_strcmp(answer, "Login or password is incorrect!"))
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_error_logging, gui, 0);
        if (!mx_strcmp(answer, "A chat or an user with such name already exists!!"))
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_error_create_chat, gui, 0);
        if (!mx_strcmp(answer, "There is no such user in the uchat!"))
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_error_find_user, gui, 0);
        if (!mx_strcmp(answer, "Chat profile info!"))
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_success_members_list, gui, 0);
        if (!mx_strcmp(answer, "The contact was deleted from the chat!"))
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_success_members_list, gui, 0);
        if (!mx_strcmp(answer, "Contact profile info!"))
            gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_success_profile_info, gui, 0);
    }
    return NULL;
}
