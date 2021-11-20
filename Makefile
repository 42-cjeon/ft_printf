CC = clang
CFLAGS = 

NAME = libftprintf.a
SRCS = arg_to_stringf1.c arg_to_stringf2.c arg_to_stringf3.c \
	format_parser.c format_parser_helper.c ft_printf.c \
	get_arg1.c get_arg2.c utils.c itoa.c
OBJS_ROOT = objs
#OBJS = $(addprefix $(OBJS_ROOT)/, $(SRCS:.c=.o))
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

test : all main.c
	$(CC) -L. -lftprintf main.c -o main && ./main

.PHONY : all clean fclean re test