SRC = main.c normal_cmd.c handle_signal.c check_builtins.c cd_builtin.c

LIBFT = libft/libft.a

main:
	cc $(SRC) $(LIBFT) -lreadline -lhistory 
