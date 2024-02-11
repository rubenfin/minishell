CC = cc
CFLAGS = -g

LDFLAGS =
ifeq ($(shell uname -s),Linux)
    CFLAGS +=-fsanitize=leak
endif
ifdef FSAN
    CFLAGS +=-fsanitize=address
endif
ifdef BUG
    CFLAGS +=-g
endif

SRC_DIR = src
BUILTINS_DIR = builtins
EXECUTING_DIR = executing
PARSING_DIR = parsing
UTILS_DIR = utils

SRC :=  $(wildcard $(SRC_DIR)/*.c) \
        $(wildcard $(SRC_DIR)/$(BUILTINS_DIR)/*.c) \
		$(wildcard $(SRC_DIR)/$(EXECUTING_DIR)/*.c) \
		$(wildcard $(SRC_DIR)/$(PARSING_DIR)/*.c) \
        $(wildcard $(SRC_DIR)/$(UTILS_DIR)/*.c)

OBJS_DIR = objs
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

NAME = minishell

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -rf $(OBJ)
	@echo "$(YELLOW)Removed all objects!$(DEFAULT)"

fclean: clean
	rm -rf $(NAME)
	rm -rf $(OBJS_DIR)
	@echo "$(RED)Removed executables!$(DEFAULT)"

re: fclean all

$(NAME): $(OBJS_DIR) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LINKERFLAGS) src/libft.a
	@echo "$(GREEN)Compiled mandatory!$(DEFAULT)"

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

fsan:
	$(MAKE) FSAN=1 BUG=1
.PHONY: fsan

resan:  fclean fsan
.PHONY: resan

debug:
	$(MAKE) BUG=1
.PHONY: debug

rebug:  fclean debug
.PHONY: rebug

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m