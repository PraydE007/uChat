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

// static void send_mail(char *email, char *message) {
//     int fd = open("MAIL", O_CREAT | O_RDWR);
//     char cmd[1024];
//     // char *command[] = {"sendmail", email, NULL};

//     printf("SENDENDND !11!!1!!!!!\n");
//     write(fd, message, strlen(message));
//     sprintf(cmd, "zsh send.sh \"%s\" \"%s\"", message, email);
//     system(cmd);
//     system("rm -rf MAIL");
//     close(fd);
//    if (wpid == 0) {
//        close(pipe_des[0]);
//        dup2(pipe_des[1], 1);
//        if (execvp("sendmail", command) != -1) {
//            fprintf(stderr, "123\n");
//        }
//        else if (execvp("sendmail", command))
//    }
// }

//void *mx_doprocessing (void *data) {
//    t_sockbd sockbd = *(t_sockbd *)data;
//    char buffer[43388];
//    int n = 0;
//
//    bzero(buffer, 43388);
//    n = recv(sockbd.sockfd, buffer, 43388, 0);
//    mx_printstr("YA ZASHEL\n");
//    write(1, buffer, 43388);
//    int potok = open("/Users/ozahirnyi/uchat/test.png", O_RDWR | O_CREAT | O_APPEND, S_IWRITE | S_IREAD);
//    write(potok, buffer, 43388);
//    close(potok);
//    return NULL;
//}

//static int recv_image(int size, )

void *mx_doprocessing (void *data) {
    t_sockbd sockbd = *(t_sockbd *)data;
    int n = 0;
    char buffer[MX_MAX_BYTES];
    const char *answer = NULL;
    json_object *jobj = json_object_new_object();
    json_object *j_result = json_object_new_object();
    json_object *j_socket = NULL;
    char *login = NULL;

    // pthread_mutex_lock(&(sockbd.mutex));
    // sockbd.login = mx_js_to_str(jobj, "Login"); //
    // login = mx_strdup(sockbd.login); //
//    printf("SIZE = %d\n", size);
    //send_mail("ozahirny@gmail.com", "DAROVA EPT\n");
    printf("SOCKET SERVER = %d\n", sockbd.sockfd);
    while (true) {
//        bzero(buffer,MX_MAX_BYTES);
        n = recv(sockbd.sockfd, buffer, sizeof(buffer), 0);
//        printf("GET %s\n\n", buffer);

        //printf("%s\n", buffer);
        j_socket = json_object_new_int(sockbd.sockfd);
        //printf("buffer: %s\n", buffer);
        //n = send(sockbd.sockfd, buffer, sizeof(buffer), 0);
        if (n <= 0) {
            if_disconnect(sockbd);
            mx_user_deactivate(sockbd.bd, sockbd.sockfd);
            break;
        }
        jobj = json_tokener_parse(buffer);
        json_object_object_add(jobj,"Socket", j_socket);
        log_add_info(sockbd, jobj);
        ///////// Затычка для добавления контактов
        if (!mx_strcmp(mx_js_to_str(jobj, "Type"), "Sending")) { //
            // sockbd.login = mx_js_to_str(jobj, "Login"); //
            // login = mx_strdup(sockbd.login); //
            printf("%s\n", buffer);
            continue;
        } //
        //////// Затычка для отправления картинок
        if (!mx_strcmp(mx_js_to_str(jobj, "Type"), "File")) { //
            mx_printstr("YA ZASHEL\n");
            int size = mx_atoi(mx_js_to_str(jobj, "Size"));
            printf("SIZE = %d\n", size);
            char *bunfer = mx_strnew(size);
//            recv(sockbd.sockfd, bunfer, size, 0);
            int potok = open("server/test.png", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            read(sockbd.sockfd, bunfer, size);
            write(potok, bunfer, size);
            close(potok);
            continue;
        } //

        // if (!mx_strcmp(mx_js_to_str(jobj, "Type"), "Private_chat")) { //
        //     // sockbd.login = mx_js_to_str(jobj, "Login"); //
        //     // login = mx_strdup(sockbd.login); //
        //     printf("%s\n", buffer);
        //     continue;
        // } //

        if (!mx_strcmp(mx_js_to_str(jobj, "Type"), "Public_group")) { //
            // sockbd.login = mx_js_to_str(jobj, "Login"); //
            // login = mx_strdup(sockbd.login); //
            printf("%s\n", buffer);
            continue;
        } //
        ///////// Затычка для профиля
        // json_object *j_test_type = json_object_new_string("Chat");
        // json_object_object_add(jobj,"Type", j_test_type);
        // if (!mx_strcmp(mx_js_to_str(jobj, "Type"), "Chat")) { //
        //     // sockbd.login = mx_js_to_str(jobj, "Login"); //
        //     // login = mx_strdup(sockbd.login); //
        //     // json_object *j_test_jobj = json_object_new_object();
        //     // json_object *j_test_Answer = json_object_new_string("Sucsess");
        //     json_object *j_test_Login = json_object_new_string("AAA");
        //     json_object *j_test_Chat_name = json_object_new_string("Chisto potrindetb");
        //     // json_object *j_test_Mobile = json_object_new_string("TEST_MOBILE");
        // json_object *j_test_Security_key = json_object_new_string("cdef9e974ae775ea9b1472cedb108607127607e538b5c1ff8f9e461234");
        //     // json_object_object_add(jobj,"Answer", j_test_Answer);
        //     json_object_object_add(jobj,"Login", j_test_Login);
        //     // json_object_object_add(jobj,"Email", j_test_Email);
        //     // json_object_object_add(jobj,"Mobile", j_test_Mobile);
        //     json_object_object_add(jobj,"Chat_name", j_test_Chat_name);
        // json_object_object_add(jobj,"Security_key", j_test_Security_key);
        //     // n = send(sockbd.sockfd, json_object_to_json_string(jobj), mx_strlen(json_object_to_json_string(jobj)), 0); //
        //     // continue;
        // } //
        ///////// Конец затычки для профиля

        //printf("char *login: %s\n", login); //
        printf("json_object_to_json_string(jobj): %s\n", json_object_to_json_string(jobj));
        j_result = mx_dbase_handler(jobj, sockbd.bd); //
        //json_object_put(jobj); //
        //printf("json_object_to_json_string(j_result): %s\n", json_object_to_json_string(j_result)); //
        answer = json_object_to_json_string(j_result); //
        printf("ANSWER : %s\n\n", answer);
        n = send(sockbd.sockfd, answer, mx_strlen(answer),  0);

        // if (!mx_strcmp(mx_js_to_str(j_result, "Answer"), MX_LOG_MES))
        //     n = send(sockbd.sockfd, MX_LOG_MES, mx_strlen(MX_LOG_MES),  0);
        // else if (!mx_strcmp(mx_js_to_str(j_result, "Answer"), MX_REG_MES))
        //     n = send(sockbd.sockfd, MX_REG_MES, mx_strlen(MX_REG_MES),  0);
        // else if (!mx_strcmp(mx_js_to_str(j_result, "Answer"), MX_CONT_MES))
        //     n = send(sockbd.sockfd, MX_CONT_MES, mx_strlen(MX_CONT_MES),  0);
        // else if (!mx_strcmp(mx_js_to_str(j_result, "Answer"), MX_LOG_ERR))
        //     n = send(sockbd.sockfd, MX_LOG_ERR, mx_strlen(MX_LOG_ERR),  0);
        // else if (!mx_strcmp(mx_js_to_str(j_result, "Answer"), MX_REG_CHAT_ERR))
        //     n = send(sockbd.sockfd, MX_REG_CHAT_ERR, mx_strlen(MX_REG_CHAT_ERR),  0);
        // else if (!mx_strcmp(mx_js_to_str(j_result, "Answer"), MX_CHEAT_MESSAGE))
        //     n = send(sockbd.sockfd, MX_CHEAT_MESSAGE, mx_strlen(MX_CHEAT_MESSAGE),  0);
        // else if (!mx_strcmp(mx_js_to_str(j_result, "Answer"), MX_CONT_ERR))
        //     n = send(sockbd.sockfd, MX_CONT_ERR, mx_strlen(MX_CONT_ERR),  0);
        // else if (!mx_strcmp(mx_js_to_str(j_result, "Answer"), "Profile info!"))
        //     n = send(sockbd.sockfd, "Profile info!", mx_strlen("Profile info!"),  0);
        // else if (!mx_strcmp(mx_js_to_str(j_result, "Answer"), "Profile data is changed!"))
        //     n = send(sockbd.sockfd, "Profile data is changed!", mx_strlen("Profile data is changed!"),  0);
        json_object_put(j_result);
        if (n <= 0) {
            mx_user_deactivate(sockbd.bd, sockbd.sockfd);
            break;
        }
    }
    mx_strdel(&login);
    // pthread_mutex_unlock(&(sockbd.mutex));
    return 0;
}
