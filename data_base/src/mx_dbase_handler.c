#include "dbase.h"

json_object *mx_dbase_handler(json_object *jobj, sqlite3 *db) {
    t_datab *datab = mx_create_datab_node();
    json_object *j_result = json_object_new_object();
    // json_object *j_result2 = json_object_new_object();

    if (!mx_strcmp("Logging", mx_json_to_str(jobj, "Type"))) {
        j_result = mx_if_logging(jobj, db, datab);
        // json_object *j_test_Login = json_object_new_string("AAA");
        // json_object *j_test_Chat_name = json_object_new_string("Chisto potrindetb");
        // json_object *j_test_Security_key = json_object_new_string("cdef9e974ae775ea9b1472cedb108607127607e538b5c1ff8f9e46123");
        // json_object_object_add(jobj,"Login", j_test_Login);
        // json_object_object_add(jobj,"Chat_name", j_test_Chat_name);
        // json_object_object_add(jobj,"Security_key", j_test_Security_key);
        // j_result2 = mx_if_chat(jobj, db, datab);
        // printf("BUFFER: %s\n", json_object_get_string(j_result2));
    }
    else if (!mx_strcmp("Registr", mx_json_to_str(jobj, "Type")))
        j_result = mx_if_registr(jobj, db, datab);
    else if (!mx_strcmp("Add_contact", mx_json_to_str(jobj, "Type")))
        j_result = mx_if_contact(jobj, db, datab);
    else if (!mx_strcmp("Get_profile", mx_json_to_str(jobj, "Type")))
        j_result = mx_if_get_profile(jobj, db, datab);
    else if (!mx_strcmp("Change_profile", mx_json_to_str(jobj, "Type")))
        j_result = mx_if_change_profile(jobj, db, datab);
    else if (!mx_strcmp("Change_passwd", mx_json_to_str(jobj, "Type")))
        j_result = mx_if_change_passwd(jobj, db, datab);
    else if (!mx_strcmp("Chat_create", mx_json_to_str(jobj, "Type")))
        j_result = mx_if_chat_create(jobj, db, datab);
    else if (!mx_strcmp("Chat", mx_json_to_str(jobj, "Type")))
        j_result = mx_if_chat(jobj, db, datab);
    mx_dealloc_datab(&datab);
    return j_result;
}
