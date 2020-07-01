#include "server.h"
static void if_disconnect(t_sockbd sockbd) {
    write (sockbd.log_sescr, "User ", 5);
    write (sockbd.log_sescr, mx_itoa(sockbd.sockfd), 1);
    write (sockbd.log_sescr, " Disconnected\n", 14);
    close(sockbd.sockfd);
}

static void log_add_info(t_sockbd sockbd, json_object *jobj) {
    write (sockbd.log_sescr, "Taked ", 6);
    write (sockbd.log_sescr, json_object_to_json_string(jobj),
        strlen(json_object_to_json_string(jobj)));
    write (sockbd.log_sescr, " from socket: ", 14);
    write (sockbd.log_sescr, mx_itoa(sockbd.sockfd), 1);
    write (sockbd.log_sescr, "\n", 1);
}

void *mx_doprocessing (void *data) {
    t_sockbd sockbd = *(t_sockbd *)data;
    int n;
    char buffer[2048];
    // const char *answer = NULL;
    json_object *jobj = json_object_new_object();
    json_object *j_result = json_object_new_object();
    json_object *j_socket = NULL;
    char *login = NULL;

    while (true) {
        bzero(buffer,2048);
        n = recv(sockbd.sockfd, buffer, sizeof(buffer), 0);
        printf("%s\n", buffer);
        j_socket = json_object_new_int(sockbd.sockfd);
        //n = send(sockbd.sockfd, buffer, sizeof(buffer), 0);
        if (n <= 0) {
            if_disconnect(sockbd);
            mx_status_change(sockbd.bd, login, sockbd.sockfd, 0);
            break;
        }
        jobj = json_tokener_parse(buffer);
        json_object_object_add(jobj,"Socket", j_socket);
        log_add_info(sockbd, jobj);
        if (!mx_strcmp(mx_json_to_str(jobj, "Type"), "Logging")) { //
            sockbd.login = mx_json_to_str(jobj, "Login"); //
            login = mx_strdup(sockbd.login); //
        } //
        ///////// Затычка для добавления контактов
        if (!mx_strcmp(mx_json_to_str(jobj, "Type"), "Add_contact")) { //
            // sockbd.login = mx_json_to_str(jobj, "Login"); //
            // login = mx_strdup(sockbd.login); //
            printf("%s\n", buffer);
            continue;
        } //
        ///////// Конец затычки для добавления контактов

        ///////// Затычка для профиля
        if (!mx_strcmp(mx_json_to_str(jobj, "Type"), "Get_Profile")) { //
            // sockbd.login = mx_json_to_str(jobj, "Login"); //
            // login = mx_strdup(sockbd.login); //
            json_object *j_test_jobj = json_object_new_object();
            json_object *j_test_Answer = json_object_new_string("Sucsess");
            json_object *j_test_Login = json_object_new_string("TEST_LOGIN");
            json_object *j_test_Email = json_object_new_string("TEST_EMAIL");
            json_object *j_test_Number = json_object_new_string("TEST_NUMBER");
            json_object_object_add(j_test_jobj,"Answer_profile", j_test_Answer);
            json_object_object_add(j_test_jobj,"Login", j_test_Login);
            json_object_object_add(j_test_jobj,"Email", j_test_Email);
            json_object_object_add(j_test_jobj,"Number", j_test_Number);
            json_object_object_add(j_test_jobj,"Socket", j_socket);

            n = send(sockbd.sockfd, json_object_to_json_string(j_test_jobj), mx_strlen(json_object_to_json_string(j_test_jobj)), 0);
            continue;
        } //
         ///////// Конец затычки для профиля

        //printf("char *login: %s\n", login); //
        j_result = mx_dbase_handler(jobj, sockbd.bd); //
        //json_object_put(jobj); //
        //printf("json_object_to_json_string(j_result): %s\n", json_object_to_json_string(j_result)); //
        // answer = json_object_get_string(j_result); //
        // n = send(sockbd.sockfd, answer, mx_strlen(answer),  0);
        if (!mx_strcmp(mx_json_to_str(j_result, "Answer"), MX_LOG_MES))
            n = send(sockbd.sockfd, MX_LOG_MES, mx_strlen(MX_LOG_MES),  0);
        else if (!mx_strcmp(mx_json_to_str(j_result, "Answer"), MX_REG_MES))
            n = send(sockbd.sockfd, MX_REG_MES, mx_strlen(MX_REG_MES),  0);
        else if (!mx_strcmp(mx_json_to_str(j_result, "Answer"), MX_LOG_ERR))
            n = send(sockbd.sockfd, MX_LOG_ERR, mx_strlen(MX_LOG_ERR),  0);
        else if (!mx_strcmp(mx_json_to_str(j_result, "Answer"), MX_REG_ERR))
            n = send(sockbd.sockfd, MX_REG_ERR, mx_strlen(MX_REG_ERR),  0);
        json_object_put(j_result);
        if (n <= 0) {
            mx_status_change(sockbd.bd, login, sockbd.sockfd, 0);
            break;
        }
    }
    mx_strdel(&login);
    return 0;
}
