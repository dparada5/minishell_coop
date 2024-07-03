# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dparada <dparada@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/31 11:04:19 by dparada           #+#    #+#              #
#    Updated: 2024/07/02 19:18:50 by dparada          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 		= clang
NAME 	= minishell
USER 	= dparada
CFLAGS 	= -Wall -Wextra -Werror -g
LIBFT = lib/LIBFT
SRC_DIR = src/
OBJ_DIR = obj/
MINISHELL_H = ./inc/$(NAME).h
LIB = -lreadline

MAGENTA = \033[35;1m
YELLOW  = \033[33;1m
GREEN   = \033[32;1m
WHITE   = \033[37;1m
RESET   = \033[0m
GRAY 	= \033[0;90m
BLUE    = \033[34;1m
CYAN    = \033[37;1m
BOLD	= \033[1m
RED		= \033[31;1m

SRC_FILES = executer/built_ins/cd \
			executer/built_ins/echo \
			executer/built_ins/env \
			executer/built_ins/exit \
			executer/built_ins/export \
			executer/built_ins/pwd \
			executer/built_ins/unset \
			executer/utils/env_utils \
			executer/utils/exec_utils \
			executer/utils/general_utils \
			executer/utils/tokens_utils \
			executer/executor \
			parser/commands/cmds_create \
			parser/commands/cmds_utils \
			parser/commands/create_cmd_matrix \
			parser/tokens/create_token \
			parser/utils/env \
			parser/tokens/expand_types \
			parser/tokens/expand \
			parser/utils/free \
			parser/init \
			parser/utils/prints \
			parser/commands/redirecc \
			parser/utils/states \
			parser/tokens/token_utils \
			parser/tokens/tokens \
			parser/utils/utils \
			parser/utils/signals \
			parser/main
			

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o,$(SRC_FILES)))

OBJF = .cache_exists

all: $(NAME)

$(NAME): compiling $(OBJ)
		@echo
		@make all -C $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJ) $(LIB) -L$(LIBFT) -lft -o $(NAME)
		@echo "$(MAGENTA)Minishell compiled!$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(MINISHELL_H)| $(OBJF)
		@mkdir -p $(dir $@)
		@echo "$(BLUE)Compiling: $(RESET)$(notdir $<)"
		@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(BONUS_DIR)%.c | $(OBJF)
		@echo "$(WHITE)Compiling: $(RESET)$(notdir $<)"
		@$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
		@mkdir -p $(OBJ_DIR)

compiling:
		@echo "$(RED)Compiling Minishell: $(RESET)"

clean:
		@rm -rf $(OBJ_DIR)
		@make clean -C $(LIBFT)
		@echo "$(RED)Cleaning Minishell's objects. $(RESET)"
		@echo

fclean:
		@rm -rf $(OBJ_DIR)
		@rm -rf $(NAME)
		@make fclean -C $(LIBFT)
		@echo "$(RED)Cleaning Minishell's executables.$(RESET)"

re: fclean all

.PHONY: all clean fclean re compiling 
