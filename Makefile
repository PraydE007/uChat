CL_NAME	=	uchat
SV_NAME = 	uchat_server

CFLG	=	-std=c11 $(addprefix -W, all extra error pedantic) -g
INCD = inc
CL_SRCD	=	client/src
SV_SRCD =	server/src
DB_SRCD =	data_base/src
CL_INCD	=	client/inc
SV_INCD =	server/inc
DB_INCD =	data_base/inc
CL_OBJD	=	client/obj
SV_OBJD =	server/obj
DB_OBJD =	data_base/obj
CL_GTK_FLAGS = `pkg-config --cflags --libs gtk+-3.0`
CL_GTK_SORT_FLAGS = `pkg-config --cflags gtk+-3.0`
SQL_FLAGS = -lsqlite3
SANITAIZER_FLAGS =  -fsanitize=address
CL_THREADS_LINKER = -pthread -lpthread

LMXD	=	libmx
LMXA:=	$(LMXD)/libmx.a


DB_MXD	=	data_base
DB_MXA:=	$(DB_MXD)/uchat_db
DB_MXI:=	$(DB_MXD)/$(INCD)

CL_INC		=	client.h
SV_INC		=	server.h

CL_INCS	=	$(addprefix $(CL_INCD)/, $(CL_INC))
SV_INCS =	$(addprefix $(SV_INCD)/, $(SV_INC))

CL_SRC		=	main.c \
				mx_init_auth_screen.c \
				mx_interface.c \
				mx_close_window.c \
				mx_open_window.c \
				mx_get_widget.c \
				mx_load_theme.c \
				mx_light_theme.c \
				mx_dark_theme.c \
				mx_logged_in.c \
				mx_logged_in_chat.c \
				mx_open_signup.c \
				mx_close_signup.c \
				mx_hash_to_string.c \
				mx_registration.c \
				mx_send_message.c \
				mx_gw.c \
				mx_client_recv.c \
				mx_open_profile.c \
				mx_close_profile.c \
				mx_load_img.c \
				mx_push_chat.c \
				mx_find_user.c \
				mx_push_message.c \
				mx_change_theme.c \
				mx_check_number.c \
				mx_check_pass.c \
				mx_check_login.c \
				mx_check_mail.c \
				mx_rep_img.c \
				mx_show_dialog.c \
				mx_change_profile.c \
				mx_success_logging.c \
				mx_anti_resize.c \
				mx_p_own.c \
				mx_p_owned.c \
				mx_clear_container.c \
				mx_open_chat.c \
				mx_change_pass.c \
				mx_success_registr.c \
				mx_success_profile.c \
				mx_success_change_profile.c \
				mx_success_change_passwd.c \
				mx_render_contacts.c \
				mx_success_add_contact.c \
				mx_success_message.c \
				mx_open_group.c \
				mx_close_group.c \
				mx_send_image.c \
				mx_success_history.c \
				mx_upload_file.c \
				mx_open_file_chooser.c \
				mx_render_chats.c \
				mx_add_user_to_group.c \

SV_SRC		=	main.c \
				mx_doprocessing.c \
				mx_demonize.c \
				mx_create_log.c \


CL_SRCS	=	$(addprefix $(CL_SRCD)/, $(CL_SRC))
SV_SRCS =	$(addprefix $(SV_SRCD)/, $(SV_SRC))
CL_OBJS	=	$(addprefix $(CL_OBJD)/, $(CL_SRC:%.c=%.o))
SV_OBJS	=	$(addprefix $(SV_OBJD)/, $(SV_SRC:%.c=%.o))

all: install

$(FILE:a/%=%)

install: install_client install_server

install_db:

install_client: $(LMXA) $(CL_NAME)

$(CL_NAME): $(CL_OBJS)
	@clang $(CFLG) $(CL_OBJS) $(CL_GTK_FLAGS) -L$(LMXD) -L/usr/local/opt/openssl/lib/ -lssl -lcrypto -lmx -rdynamic -o $@ libjson-c.a
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(CL_OBJD)/%.o: $(CL_SRCD)/%.c $(CL_INCS)
	@clang $(CFLG) -c $< $(CL_GTK_SORT_FLAGS) -I/usr/local/opt/openssl/include/ -o $@ -I$(CL_INCD) -I$(LMXI)
	@printf "\r\33[2K$(CL_NAME) \033[33;1mcompile \033[0m$(<:$(CL_SRCD)/%.c=%) "


$(CL_OBJS): | $(CL_OBJD)

$(CL_OBJD):
	@mkdir -p $@

install_server: $(LMXA) $(DB_MXA) $(SV_NAME)

$(SV_NAME): $(SV_OBJS)
	@clang $(CFLG) $(SV_OBJS) -L$(LMXD) -fsanitize=address -L/usr/local/opt/openssl/lib/ -lssl -lcrypto -lmx -o $@ libjson-c.a $(DB_MXA) -lsqlite3
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(SV_OBJD)/%.o: $(SV_SRCD)/%.c $(SV_INCS)
	@clang $(CFLG) -c $< -I/usr/local/opt/openssl/include/ -o $@ -I$(SV_INCD) -I$(LMXI) -I$(DB_MXI)
	@printf "\r\33[2K$(SV_NAME) \033[33;1mcompile \033[0m$(<:$(SV_SRCD)/%.c=%) "

$(SV_OBJS): | $(SV_OBJD)

$(SV_OBJD):
	@mkdir -p $@

$(LMXA):
	@make -sC $(LMXD)

$(DB_MXA):
	@make -sC $(DB_MXD)
clean:
	@make -sC $(LMXD) $@
	@make -sC $(DB_MXD) $@
	@rm -rf $(CL_OBJD)
	@rm -rf $(SV_OBJD)
	@rm -rf $(DB_MXD)/$(DB_MXA)
	@printf "$(CL_OBJD)\t   \033[31;1mdeleted\033[0m\n"
	@printf "$(SV_OBJD)\t   \033[31;1mdeleted\033[0m\n"


uninstall: clean
	@make -sC $(LMXD) $@
	@make -sC $(DB_MXD) $@
	@rm -rf $(CL_NAME)
	@rm -rf $(SV_NAME)
	@printf "$(CL_NAME) \033[31;1muninstalled\033[0m\n"
	@printf "$(SV_NAME) \033[31;1muninstalled\033[0m\n"

uninstall_server:
	@make -sC $(DB_MXD) uninstall
	@rm -rf $(SV_NAME)
	@printf "$(SV_NAME) \033[31;1muninstalled\033[0m\n"

reinstall: uninstall install

reinstall_server : uninstall_server install_server
