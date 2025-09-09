NAME := ft_ls
LIBFT_AUTHORIZED := $(shell if [ -d libft ]; then echo 1; else echo 0; fi)
MODE ?= mandatory
BONUS := $(if $(filter bonus,$(MODE)),1,0)

MACRO_DEF = -D LIBFT_AUTHORIZED=$(LIBFT_AUTHORIZED) -D EXEC_NAME=\"$(NAME)\" -D BONUS=$(BONUS)
INCLUDES = -Iincludes

ifeq ($(LIBFT_AUTHORIZED), 1)
	INCLUDES += -Ilibft/includes
	LIBFT_LIB = libft/libft.a
endif

CC = cc
CFLAGS = -Wall -Werror -Wextra -MD $(MACRO_DEF) $(INCLUDES)

ifeq ($(MODE), debug)
	CFLAGS = -Wall -Wextra -MD $(MACRO_DEF) $(INCLUDES) -g3
endif

VPATH := srcs

SRCS =	main.c			\
		utils.c			\
		parse.c			\
		parse_options.c	\
		run.c			\
		sort.c			\

ifeq ($(BONUS), 1)
	NAME = ft_ls_bonus
	SRCS +=	parse_color_bonus.c
endif

BIN_DIR = .bin-$(MODE)
OBJS = $(addprefix $(BIN_DIR)/, $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

RESET	= \033[0m
GRAY	= \033[90m
RED 	= \033[31m
GREEN 	= \033[32m
YELLOW 	= \033[33m
BLUE 	= \033[34m

all: $(NAME)
	printf "$(RESET)"

bonus:
	$(MAKE) MODE=bonus

debug:
	$(MAKE) MODE=debug

debugb:
	$(MAKE) MODE=debug BONUS=1

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

ifeq ($(LIBFT_AUTHORIZED), 1)
$(LIBFT_LIB):
	$(MAKE) -C libft
endif

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $@

$(BIN_DIR)/%.o: %.c Makefile | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	printf "$(GRAY)compiling: $(BLUE)%-40s $(GRAY)[%d/%d]\n" "$<" "$$(ls $(BIN_DIR) | grep -c '\.o')" "$(words $(SRCS))"

clean:
ifeq ($(LIBFT_AUTHORIZED), 1)
	$(MAKE) -C libft clean
endif
	rm -rf .bin-*

fclean:
ifeq ($(LIBFT_AUTHORIZED), 1)
	$(MAKE) -C libft fclean
endif
	rm -rf .bin-*
	rm -f ft_ls ft_ls_bonus

re: fclean all

.PHONY: all clean fclean re debug libft

-include $(DEPS)

.SILENT:
MAKEFLAGS := --no-print-directory
