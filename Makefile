SRC = main.c functions.c 

LIBFT = libft/libft.a

main:
	cc $(SRC) $(LIBFT) -lreadline -lhistory 
