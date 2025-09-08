NAME = libft.a
MODE ?= release

BIN_DIR = .bin-$(MODE)
INCLUDES = -Iincludes

CC = cc
CFLAGS = -Wall -Werror -Wextra -Iincludes -MD $(INCLUDES)

ifeq ($(MODE), debug)
	CFLAGS += -g3
endif

VPATH = srcs:srcs/is:srcs/mem:srcs/str:srcs/to:srcs/lst:srcs/math:srcs/algo:srcs/printf:srcs/gnl

SRCS_ALGO =	ft_sort_int_tab.c	\
			ft_swap.c			\

SRCS_GNL =	get_next_line.c		\
			ft_getline.c		\

SRCS_IS =	ft_isalnum.c		\
			ft_isalpha.c		\
			ft_isascii.c		\
			ft_isblank.c		\
			ft_iscntrl.c		\
			ft_isdigit.c		\
			ft_isgraph.c		\
			ft_islower.c		\
			ft_isprime.c		\
			ft_isprint.c		\
			ft_ispunct.c		\
			ft_isspace.c		\
			ft_isupper.c		\
			ft_isxdigit.c		\

SRCS_LST =	ft_lstadd_back.c	\
			ft_lstadd_front.c	\
			ft_lstclear.c		\
			ft_lstdelone.c		\
			ft_lstiter.c		\
			ft_lstlast.c		\
			ft_lstmap.c			\
			ft_lstnew.c			\
			ft_lstremove_if.c	\
			ft_lstreverse.c		\
			ft_lstsize.c		\
			ft_lstsort.c		\
			ft_lstmerge.c		\

SRCS_MATH =	ft_abs.c			\
			ft_clamp.c			\
			ft_factorial.c		\
			ft_max.c			\
			ft_min.c			\
			ft_pow.c			\
			ft_round.c			\
			ft_sqrt.c			\
			ft_trigo.c			\
			ft_vec3_op_d.c		\
			ft_vec3_op_vec3.c	\

SRCS_MEM =	ft_bzero.c			\
			ft_calloc.c			\
			ft_memchr.c			\
			ft_memcmp.c			\
			ft_memcpy.c			\
			ft_memmove.c		\
			ft_memset.c			\
			ft_nothing.c		\
			ft_realloc.c		\

SRCS_PRINTF =	ft_printf.c			\
				ft_printf_utils.c	\

SRCS_STR =	ft_split.c			\
			ft_strchr.c			\
			ft_strcmp.c			\
			ft_strcpy.c			\
			ft_strdup.c			\
			ft_striteri.c		\
			ft_strjoin.c		\
			ft_strlcat.c		\
			ft_strlcpy.c		\
			ft_strlen.c			\
			ft_strmapi.c		\
			ft_strncmp.c		\
			ft_strndup.c		\
			ft_strnstr.c		\
			ft_strrchr.c		\
			ft_strtrim.c		\
			ft_substr.c			\

SRCS_TO =	ft_atod.c			\
			ft_atoi_base.c		\
			ft_atoi.c			\
			ft_atol.c			\
			ft_atoll.c			\
			ft_itoa.c			\
			ft_strtod.c			\
			ft_strtoi.c			\
			ft_strtol.c			\
			ft_tolower.c		\
			ft_toupper.c		\

SRCS =	$(SRCS_ALGO)	\
		$(SRCS_GNL)		\
		$(SRCS_IS)		\
		$(SRCS_LST)		\
		$(SRCS_MATH)	\
		$(SRCS_MEM)		\
		$(SRCS_PRINTF)	\
		$(SRCS_STR)		\
		$(SRCS_TO)		\

OBJS = $(addprefix $(BIN_DIR)/, $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

all: $(BIN_DIR) $(NAME)

debug:
	$(MAKE) MODE=debug

$(BIN_DIR):
		mkdir -p $(BIN_DIR)

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)

$(BIN_DIR)/%.o: %.c Makefile | $(BIN_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -rf .bin-release .bin-debug

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)

.SILENT:
MAKEFLAGS=--no-print-directory
