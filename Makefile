
NAME	= libftprintf.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= 	ft_printf.c
OBJS	= $(SRCS:%.c=%.o)

.PHONY:	all comp NAME dir clean fclean re

all: comp $(NAME) dir

comp:
	$(CC) $(CFLAGS) -c $(SRCS)

$(NAME):
	ar rc $(NAME) $(OBJS)

dir:
	ranlib libftprintf.a

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
