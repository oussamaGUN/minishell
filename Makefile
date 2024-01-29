SRC = main.c

LIBFT = libft/libft.a

main:
	cc $(SRC) -lreadline  libft/libft.a 
