CC = cc

# CFLAGS = -Wall -Wextra -Werror

SRC = main.c  handle_signal.c tokenizing/first_step.c tokenizing/ft_ownsplit.c \
	parsing/quotes_handle.c tools/tools.c parsing/syntax_error.c expanding/del_quotes.c  \
	files/here_doc.c parsing/tree.c execution/execution.c builtins/builtins.c env/create_env.c

LIBFT = libft/libft.a

LIBS = -lreadline

OBJ = $(SRC:.c=.o)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
