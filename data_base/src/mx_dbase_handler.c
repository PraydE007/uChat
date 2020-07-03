#include "dbase.h"

json_object *mx_dbase_handler(json_object *jobj, sqlite3 *db) {
    t_datab *datab = mx_create_datab_node();
    json_object *j_result = json_object_new_object();

    if (!mx_strcmp("Logging", mx_json_to_str(jobj, "Type")))
        j_result = mx_if_logging(jobj, db, datab);
    else if (!mx_strcmp("Registr", mx_json_to_str(jobj, "Type")))
        j_result = mx_if_registr(jobj, db, datab);
    else if (!mx_strcmp("Add_contact", mx_json_to_str(jobj, "Type")))
        j_result = mx_if_contact(jobj, db, datab);
    else if (!mx_strcmp("Get_Profile", mx_json_to_str(jobj, "Type")))
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
