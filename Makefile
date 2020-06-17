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
CL_GTK_FLAGS = `pkg-config --cflags  --libs gtk+-3.0`
CL_GTK_SORT_FLAGS = `pkg-config --cflags gtk+-3.0`
SQL_FLAGS = -lsqlite3

LMXD	=	libmx
LMXA:=	$(LMXD)/libmx.a


DB_MXD	=	data_base
DB_MXA:=	$(DB_MXD)/uchat_db.a
DB_MXI:=	$(DB_MXD)/$(INCD)

SSLXD:= openssl
SSLXA:= $(SSLXD)/lib
SSLXI:=	$(SSLXD)/include

CL_INC		=	client.h
SV_INC		=	server.h

CL_INCS	=	$(addprefix $(CL_INCD)/, $(CL_INC))
SV_INCS =	$(addprefix $(SV_INCD)/, $(SV_INC))

CL_SRC		=	main.c \
				mx_init_auth_screen.c \
				mx_interface.c \

SV_SRC		=	main.c \
				doprocessing.c \


CL_SRCS	=	$(addprefix $(CL_SRCD)/, $(CL_SRC))
SV_SRCS =	$(addprefix $(SV_SRCD)/, $(SV_SRC))
CL_OBJS	=	$(addprefix $(CL_OBJD)/, $(CL_SRC:%.c=%.o))
SV_OBJS	=	$(addprefix $(SV_OBJD)/, $(SV_SRC:%.c=%.o))

all: install

$(FILE:a/%=%)

install: install_client install_server

install_client: $(LMXA) $(CL_NAME)

$(CL_NAME): $(CL_OBJS)
	@clang $(CFLG) $(CL_OBJS) $(CL_GTK_FLAGS) -L$(LMXD) -L$(SSLXA) -lmx -o $@ libjson-c.a openssl/lib/libcrypto.a openssl/lib/libssl.a  -lcrypto
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(CL_OBJD)/%.o: $(CL_SRCD)/%.c $(CL_INCS)
	@clang $(CFLG) -c $< $(CL_GTK_SORT_FLAGS) -o $@ -I$(CL_INCD) -I$(LMXI) -I$(SSLXI)
	@printf "\r\33[2K$(CL_NAME) \033[33;1mcompile \033[0m$(<:$(CL_SRCD)/%.c=%) "


$(CL_OBJS): | $(CL_OBJD)

$(CL_OBJD):
	@mkdir -p $@

install_server: $(LMXA) $(DB_MXA) $(SV_NAME)

$(SV_NAME): $(SV_OBJS)
	@clang $(CFLG) $(SV_OBJS) -L$(LMXD) -lmx -o $@ libjson-c.a $(DB_MXA) -lsqlite3
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(SV_OBJD)/%.o: $(SV_SRCD)/%.c $(SV_INCS)
	@clang $(CFLG) -c $< -o $@ -I$(SV_INCD) -I$(LMXI) -I$(DB_MXI)
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

reinstall: uninstall install
