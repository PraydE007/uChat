NAME = uchat_db.a

CFLG = -std=c11 $(addprefix -W, all extra error pedantic) -g

SRCD = src
INCD = inc
OBJD = obj

INC = dbase.h
INCS = $(addprefix $(INCD)/, $(INC))

FILES = mx_create_datab_node.c \
		mx_data_base_creation.c \
		mx_dbase_handler.c \
		mx_if_logging.c \
		mx_if_registr.c \
		mx_strjoin_free_js_value.c \
		mx_js_add.c \
		mx_json_to_str.c \
		mx_table_chats.c \
		mx_table_contacts.c \
		mx_table_messages.c \
		mx_table_users.c \
		mx_table_users_chats.c \
		mx_users_insert.c \


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
