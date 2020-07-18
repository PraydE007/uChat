#include "client.h"

void mx_init_images(t_s_glade **gui) {
    mx_rep_img((*gui)->i_avatar, MX_AVATAR_MIS, 225, 225);
    mx_rep_img((*gui)->i_b_profile, MX_BUTTON_PROFILE, 32, 32);
    mx_rep_img((*gui)->i_b_logout, MX_BUTTON_LOGOUT, 32, 32);
    mx_rep_img((*gui)->i_b_find, MX_BUTTON_FIND, 25, 25);
    mx_rep_img((*gui)->i_b_group, MX_BUTTON_GROUP, 25, 25);
    mx_rep_img((*gui)->i_b_settings, MX_BUTTON_SETTINGS, 25, 25);
    // mx_rep_img((*gui)->i_b_emoji, MX_BUTTON_EMOJI, 25, 25);
    mx_rep_img((*gui)->i_b_send, MX_BUTTON_SEND, 25, 25);
    mx_rep_img((*gui)->i_group, MX_G_A_MIS, 225, 225);
    mx_rep_img((*gui)->i_f_image, MX_BUTTON_FIND, 25, 25);
    mx_rep_img((*gui)->i_p_f_image, MX_BUTTON_FIND, 25, 25);
    // mx_rep_img((*gui)->i_i_reset, MX_BUTTON_RESET, 25, 25);
    mx_rep_img((*gui)->i_b_f_user, MX_BUTTON_FIND, 25, 25);
    mx_rep_img((*gui)->i_b_user, MX_BUTTON_BAN, 25, 25);
    mx_rep_img((*gui)->i_b_u_file, MX_BUTTON_FILE, 25, 25);
    mx_rep_img((*gui)->i_b_u_profile, MX_BUTTON_PROFILE, 25, 25);
    mx_rep_img((*gui)->i_b_r_chat, MX_BUTTON_BAN, 25, 25);
    mx_rep_img((*gui)->i_b_edit, MX_BUTTON_EDIT, 25, 25);
    mx_rep_img((*gui)->i_b_e_apply, MX_BUTTON_APPLY, 25, 25);
}
