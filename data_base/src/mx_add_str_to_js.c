#include "dbase.h"

void mx_add_str_to_js(struct json_object *j_result, char *key, char *value) {
    json_object *j_answer = json_object_new_string(value);
printf("11\n");
    json_object_object_add(j_result, key, j_answer);
printf("22\n");
}
