#include "client.h"

static t_verbs init_struct_verbs(){
    t_verbs verbs;

    verbs.bad_verbs = mx_file_to_str("client/res/bad_verbs.txt");
    verbs.bad_words = mx_file_to_str("client/res/bad_words.txt");
    verbs.good_verbs = mx_file_to_str("client/res/good_verbs.txt");
    verbs.good_words = mx_file_to_str("client/res/good_words.txt");
    return verbs;
}

static t_splitetd_verbs init_split_verbs(t_verbs verbs) {
    t_splitetd_verbs splitetd_verbs;

    splitetd_verbs.bad_verbs = mx_strsplit(verbs.bad_verbs, ',');
    splitetd_verbs.bad_words = mx_strsplit(verbs.bad_words, ',');
    splitetd_verbs.good_verbs = mx_strsplit(verbs.good_verbs, ',');
    splitetd_verbs.good_words = mx_strsplit(verbs.good_words, ',');

    return splitetd_verbs;
}

char *mx_init_filter(char *message) {
    t_verbs verbs = init_struct_verbs();
    t_splitetd_verbs splitetd_verbs = init_split_verbs(verbs);
    int count = 0;

    while(splitetd_verbs.bad_verbs[count]) {
        if(strstr(message, splitetd_verbs.bad_verbs[count]))
            message = mx_replace_substr(message,
                splitetd_verbs.bad_verbs[count],
                splitetd_verbs.good_verbs[count]);
        count++;
    }
    count = 0;
    while(splitetd_verbs.bad_words[count]) {
        if(strstr(message, splitetd_verbs.bad_words[count]))
            message = mx_replace_substr(message,
                splitetd_verbs.bad_words[count],
                splitetd_verbs.good_words[count]);
        count++;
    }
    return message;
}
