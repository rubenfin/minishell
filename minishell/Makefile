# GNL = get_next_line.c get_next_line_utils.c
# SRCS_BONUS = check_input.c handle_input_bonus.c instructions_bonus.c instructions2_bonus.c instructions3_bonus.c push_swap_bonus_utils.c push_swap_bonus.c ft_split_bonus.c free_exit.c ft_atoi_bonus.c handle_instructions.c \
# $(GNL)
BUILTINS = builtins/cd.c builtins/echo.c builtins/env.c builtins/pwd.c  builtins/export.c  builtins/unset.c  
SRCS_MANDATORY = minishell.c my_own_env.c $(BUILTINS)

# OBJS_BONUS = $(SRCS_BONUS:%.c=$(OBJS_DIR)/%.o)
OBJS = $(SRCS_MANDATORY:%.c=$(OBJS_DIR)/%.o)
OBJS_DIR = objs

CC = cc -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -g 
RM = rm -rf

LIBS		:= ft
LIBS_TARGET	:= libft/libft.a

LINKERFLAGS	:= -lreadline $(addprefix -L ,$(dir $(LIBS_TARGET))) $(addprefix -l ,$(LIBS))

VPATH = . libft builtins

# INCLUDE_BONUS = -I./bonus -I./bonus/gnl
# INCLUDE = -I./mandatory

#BONUS = checker
NAME = minishell

all: $(NAME)
# bonus: $(BONUS)

$(OBJS_DIR)/%.o:	%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

# $(BONUS): $(OBJS_DIR) $(OBJS_BONUS) $(LIBS_TARGET)
#	@$(CC) $(OBJS_BONUS) $(LINKERFLAGS) -o $(BONUS) $(INCLUDE_BONUS)$@
#	@echo "$(GREEN)Compiled bonus!$(DEFAULT)"


$(NAME): $(OBJS) $(LIBS_TARGET)
	@$(CC) $(OBJS) $(LINKERFLAGS) -o $@
	@echo "$(GREEN)Compiled mandatory!$(DEFAULT)"

%.a:
	@$(MAKE) -C $(@D) all

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@$(RM) $(OBJS_DIR)
	@$(MAKE) -C $(dir $(LIBS_TARGET)) clean
	@echo "$(YELLOW)Removed all objects!$(DEFAULT)"

fclean: clean
#	@$(RM) $(BONUS)
	@$(RM) $(NAME)
	@$(MAKE) -C $(dir $(LIBS_TARGET)) fclean
	@echo "$(RED)Removed executables!$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re bonus


#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m