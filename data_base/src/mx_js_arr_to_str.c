#include "dbase.h"

const char *mx_js_arr_to_str(json_object *jobj, int index) {
    const char *value = NULL;

    value = json_object_get_string(json_object_array_get_idx(jobj, index));
    return value;
}
