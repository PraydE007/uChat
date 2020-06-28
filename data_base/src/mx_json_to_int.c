#include "dbase.h"

int mx_json_to_int(json_object *jobj, char *key) {
    int value = 0;

    value = json_object_get_int(json_object_object_get(jobj, key));
    return value;
}
