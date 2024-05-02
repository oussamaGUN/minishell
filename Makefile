# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melfersi <melfersi@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/02 09:21:26 by melfersi          #+#    #+#              #
#    Updated: 2024/05/02 09:21:31 by melfersi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#______command and their flags______#
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror

#______directories______#
OBJ_DIR = obj
SRC_DIR = src
INCLUDES = -Iincludes
ifeq ($(shell uname), Linux)
	INC = -L/usr/local/lib -I/usr/local/include -lreadline
endif
ifeq ($(shell uname), Darwin)
	INC = -lreadline -I$(HOME)/readline/include/readline -L$(HOME)/readline/lib
	INCP = -I$(HOME)/readline/include/readline
endif
LIB_INCLUDES = -Ilibft/includes


#______colors______#
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
BLUE = \033[0;34m
CYAN = \033[0;36m
BOLD = \033[1m
NC = \033[0m

#______mandatory and bonus files______#
FILES = main.c tokenizing.c ft_ownsplit.c check_errors.c signals.c syntax_error.c\
		expanding.c here_doc.c here_doc_norm.c list_of_cmds.c list_of_cmds_norm.c\
		create_env.c garbage_collector.c builtins.c exec.c syntax_error_norm.c\
		expanding_norm.c expanding_norm_two.c open_files.c ft_ownsplit.c\
		ft_ownsplit_norm.c ft_ownsplit_count.c ft_ownsplit_tools.c path_init.c\
		builtins_utils1.c builtins_utils2.c builtins_utils3.c exec_utils.c\
		signals_processes.c
#______patterns and substitutions______#
SOURCES = $(FILES:%.c=$(SRC_DIR)/%.c)
OBJECTS = $(SOURCES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

#______static library name______#
NAME = minishell
LIB = libft

#______________Rules______________#

$(NAME): $(OBJECTS) $(LIB)/libft.a
	@$(CC) $(CFLAGS) $^ $(INCLUDES) $(LIB_INCLUDES) $(INC) -o $@ -fsanitize=address
	@echo "${GREEN}${BOLD}minishell is ready ✅${NC}"

# impicit rule for mandatory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< $(INCLUDES) $(LIB_INCLUDES)  $(INC) -o $@ 2> /dev/null || $(CC) $(CFLAGS) -c $< $(INCLUDES) $(LIB_INCLUDES) $(INCP) -o $@
	@echo "${GREEN}compiling ...⏳ ${RED}{${CYAN}$<${RED}}${NC}"

$(LIB)/%.a:
	@echo "${YELLOW}${BOLD}compiling libft ...⏳${NC}"
	@$(MAKE) all -C $(LIB)

re: fclean all

all: $(NAME)

#______cleaning______#
clean:
	@echo "${RED}${BOLD}cleaning ...🧹${NC}"
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIB) fclean
	@echo "${GREEN}${BOLD}cleaned ✅${NC}"
fclean: clean
	@echo "${RED}${BOLD}fleaning ...🧹${NC}"
	@$(RM) $(NAME)
	@echo "${GREEN}${BOLD}fcleaned ✅${NC}"
