#include "dbase.h"

static json_object *third_conditions(json_object *jobj, json_object **j_result,
                                    sqlite3 *db, t_datab *datab) {
    if (!mx_strcmp("Delete_user_from_chat", mx_js_to_str(jobj, "Type")))
        *j_result = mx_if_delete_contact_from_chat(jobj, db, datab);
    else if (!mx_strcmp("Chat", mx_js_to_str(jobj, "Type")))
        *j_result = mx_if_chat(jobj, db, datab);
    else if (!mx_strcmp("Send_message", mx_js_to_str(jobj, "Type"))
            || !mx_strcmp("File", mx_js_to_str(jobj, "Type")))
        *j_result = mx_if_send_message(jobj, db, datab);
    else
        mx_add_str_to_js(*j_result, "Answer", MX_CHEAT_MESSAGE);
    mx_dealloc_datab(&datab);
    return *j_result;
}

static json_object *second_conditions(json_object *jobj, json_object **j_result,
                                    sqlite3 *db, t_datab *datab) {
    if (!mx_strcmp("Change_chat", mx_js_to_str(jobj, "Type")))
        *j_result = mx_if_change_chat(jobj, db, datab);
    else if (!mx_strcmp("Change_profile", mx_js_to_str(jobj, "Type")))
        *j_result = mx_if_change_profile(jobj, db, datab);
    else if (!mx_strcmp("Change_passwd", mx_js_to_str(jobj, "Type")))
        *j_result = mx_if_change_passwd(jobj, db, datab);
    else if (!mx_strcmp("Create_chat", mx_js_to_str(jobj, "Type")))
        *j_result = mx_if_create_chat(jobj, db, datab);
    else if (!mx_strcmp("Delete_chat", mx_js_to_str(jobj, "Type")))
        *j_result = mx_if_delete_chat(jobj, db, datab);
    else if (!mx_strcmp("Delete_contact", mx_js_to_str(jobj, "Type")))
        *j_result = mx_if_delete_contact(jobj, db, datab);
    else
        *j_result = third_conditions(jobj, j_result, db, datab);
    return *j_result;
}

json_object *mx_dbase_handler(json_object *jobj, sqlite3 *db) {
    t_datab *datab = mx_create_datab_node();
    json_object *j_result = json_object_new_object();

    if (!mx_strcmp("Logging", mx_js_to_str(jobj, "Type")))
        j_result = mx_if_logging(jobj, db, datab);
    else if (!mx_strcmp("Registr", mx_js_to_str(jobj, "Type")))
        j_result = mx_if_registr(jobj, db, datab);
    else if (!mx_strcmp("Add_contact", mx_js_to_str(jobj, "Type")))
        j_result = mx_if_contact(jobj, db, datab);
    else if (!mx_strcmp("Add_user_to_chat", mx_js_to_str(jobj, "Type")))
        j_result = mx_if_add_user_to_chat(jobj, db, datab);
    else if (!mx_strcmp("Get_chat_profile", mx_js_to_str(jobj, "Type")))
        j_result = mx_if_get_chat_profile(jobj, db, datab);
    else if (!mx_strcmp("Get_profile", mx_js_to_str(jobj, "Type")))
        j_result = mx_if_get_profile(jobj, db, datab);
    else if (!mx_strcmp("Get_contact_profile", mx_js_to_str(jobj, "Type")))
        j_result = mx_if_get_contact_profile(jobj, db, datab);
    else
        j_result = second_conditions(jobj, &j_result, db, datab);
    return j_result;
}
