CC = clang
CFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a
SRCS = arg_to_string_char.c arg_to_string_hex.c arg_to_string_int.c \
		format_parser_helper.c format_parser1.c format_parser2.c format_parser_main.c \
		print_helper.c convert_digits.c string_utils.c utils.c \
		get_arg1.c get_arg2.c ft_printf.c 
OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJS) : $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

all : $(NAME)

bonus : all

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re