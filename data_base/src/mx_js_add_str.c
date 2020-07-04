#include "dbase.h"

void mx_js_add_str(struct json_object *j_result, char *key, char *value) {
    json_object *j_answer = json_object_new_string(value);
    json_object_object_add(j_result, key, j_answer);
}
