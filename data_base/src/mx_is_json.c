#include "dbase.h"

bool mx_is_json(json_object **jobj, char *buffer) {
    bool result = false;

    *jobj = json_tokener_parse(buffer);
    if (*jobj) {
        if (mx_js_to_str(*jobj, "Type") && mx_js_to_str(*jobj, "Login"))
            result = true;
    }
    return result;
}
