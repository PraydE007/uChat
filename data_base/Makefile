NAME = uchat_db.a

CFLG = -std=c11 $(addprefix -W, all extra error pedantic) -g

SRCD = src
INCD = inc
OBJD = obj

INC = dbase.h
INCS = $(addprefix $(INCD)/, $(INC))

FILES = mx_callback.c \
		mx_cb_chat_id_finder.c \
		mx_create_datab_node.c \
		mx_data_base_creation.c \
		mx_dbase_handler.c \
		mx_dealloc_datab.c \
		mx_if_change_passwd.c \
		mx_if_change_profile.c \
		mx_if_chat.c \
		mx_if_chat_create.c \
		mx_if_contact.c \
		mx_if_logging.c \
		mx_if_get_profile.c \
		mx_if_registr.c \
		mx_is_active.c \
		mx_js_add_str.c \
		mx_js_arr_add.c \
		mx_json_to_datab.c \
		mx_json_to_int.c \
		mx_json_to_str.c \
		mx_strjoin_free_js_value.c \
		mx_table_activity.c \
		mx_table_creation.c \
		mx_table_chats.c \
		mx_table_contacts.c \
		mx_table_messages.c \
		mx_table_setting.c \
		mx_table_users.c \
		mx_table_users_chats.c \
		mx_trigger_for_activity.c \
		mx_trigger_for_messages_delete.c \
		mx_trigger_for_users.c \
		mx_user_activate.c \
		mx_user_deactivate.c \


SRCS = $(addprefix $(SRCD)/, $(FILES))
OBJS = $(addprefix $(OBJD)/, $(FILES:%.c=%.o))

all: install

install: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $@ $^
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@clang $(CFLG) -c $< -o $@ -I$(INCD)
	@printf "\r\33[2K$(NAME) \033[33;1mcompile \033[0m$(<:$(SRCD)/%.c=%) "

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

clean:
	@rm -rf $(OBJD)
	@printf "$(OBJD)\t   \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@rm -rf $(NAME)
	@printf "$(NAME) \033[31;1muninstalled\033[0m\n"

reinstall: uninstall install
