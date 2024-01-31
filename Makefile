SRC = main.c

LIBFT = libft/libft.a

main:
	cc $(SRC) libft/libft.a -lreadline -lhistory 
