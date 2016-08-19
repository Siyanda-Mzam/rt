
SRC = logging_base.c
make -C ../libft re

gcc -o test logging_base.c test.c -L ../libft -lft -I ../ -I ../matrix -I ../vector -I ../libft

