# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yolabi <yolabi@42.us.org>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/06 01:44:44 by yolabi            #+#    #+#              #
#    Updated: 2017/07/02 23:23:34 by yolabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a
CC		=	gcc
CFLAGS	=	-c -Wall -Wextra -Werror
SRCDIR	=	srcs/
INCS	=	-I./includes/
 LIST	=	env_utils find_width_and_precision ft_printf itoa_and_uitoa_base	\
 			libft_utils parse_conversion parse_flags print_d					\
 			print_formatted_numbers print_formatted_strings print_nums 			\
 			print_octal_hex_and_pointer print_percent_and_chars	set_flags_1 	\
 			set_flags_2
SRCS	=	$(addsuffix .c,$(addprefix $(SRCDIR),$(LIST)))
OBJS	=	$(addsuffix .o,$(LIST))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): 
	$(CC) $(CFLAGS) $(SRCS) $(INCS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
