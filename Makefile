
#______command and their flags______#
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -w -L$(HOME)/readline/lib -fsanitize=address
INCLUDES = -I$(RDLDIR)/include/readline -Iincludes -Ilibft/includes
RDLLIB = -L$(RDLDIR)/lib -lreadline

#______directories______#
OBJ_DIR = obj
SRC_DIR = src
RDLDIR=$(HOME)/readline


#______mandatory and bonus files______#
FILES = main.c handle_signal.c tokenizing.c ft_ownsplit.c check_errors.c tools.c syntax_error.c\
		expanding.c here_doc.c here_doc_norm.c list_of_cmds.c list_of_cmds_norm.c create_env.c garbage_collector.c builtins.c exec.c syntax_error_norm.c\
		expanding_norm.c expanding_norm_two.c open_files.c ft_ownsplit.c ft_ownsplit_norm.c ft_ownsplit_count.c\
		ft_ownsplit_tools.c path_init.c
#______patterns and substitutions______#
SOURCES = $(FILES:%.c=$(SRC_DIR)/%.c)
OBJECTS = $(SOURCES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

#______static library name______#
NAME = minishell
LIB = libft

#______________Rules______________#

$(NAME): $(OBJECTS) $(LIB)/libft.a
	$(CC) $(CFLAGS) $^ $(INCLUDES) $(RDLLIB) -o $@

# impicit rule for mandatory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $< $(INCLUDES) $(RDLLIB) -c -o $@

$(LIB)/%.a:
	$(MAKE) all -C $(LIB)

re: fclean all

all: $(NAME)

#______cleaning______#
clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIB) fclean
fclean: clean
	$(RM) $(NAME)
