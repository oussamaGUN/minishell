CC = cc

#CFLAGS = -Wall -Wextra -Werror

SRC = main.c normal_cmd.c handle_signal.c check_builtins.c builtin.c ft_echo.c ft_export.c tokenizing/first_step.c tokenizing/ft_ownsplit.c \
	parsing/quotes_handle.c tools/tools.c parsing/syntax_error.c

LIBFT = libft/libft.a

LIBS = -lreadline -lhistory

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
