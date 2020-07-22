#include "dbase.h"

void mx_add_arr_to_js(struct json_object *j_result,
                      struct json_object *j_answer) {
    json_object_array_add(j_result, j_answer);
}
