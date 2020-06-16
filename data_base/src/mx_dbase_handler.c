#include "dbase.h"

json_object *mx_data_base_creation(json_object *jobj) {
    json_object *result = json_object_new_object();
    struct json_object *parsed;
    struct json_object *type;
    const char *all_data = NULL;

    // all_data = json_object_to_json_string(jobj);
    // parsed = json_tokener_parse(all_data);
    json_object_object_get_ex(parsed, "Type", &type);
    // const char *type = json_object_get_string(json_object_object_get(jobj, "Type"));
    if (!mx_strcmp("\"Logging\"", json_object_to_json_string(type))) {
        result = mx_if_logging(parsed);
    }
    if (!mx_strcmp("\"Registr\"", json_object_to_json_string(type))) {
        result = mx_if_registr(parsed);
    }
    
}
