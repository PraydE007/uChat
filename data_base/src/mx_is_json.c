#include "dbase.h"

bool mx_is_json(json_object *jobj, char *buffer) {
    bool result = false;
printf("1\n");
    jobj = json_tokener_parse(buffer);
    if (jobj) {
        if (mx_js_to_str(jobj, "Type") && mx_js_to_str(jobj, "Login"))
            result = true;

    }
printf("2\n");
    return result;
}
