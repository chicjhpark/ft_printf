NAME	= libftprintf.a

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

SRCS	= ft_printf.c \
			ft_printf_utils.c \
			ft_printf_calc.c \
			ft_printf_calc2.c \
			ft_printf_spec.c \

OBJS	= $(SRCS:.c=.o)

%.o 	: %.c
			$(CC) $(CFLAGS) -c $<

$(NAME)	: $(OBJS)
			ar rc $(NAME) $(OBJS)

.PHONY	: all clean fclean re bonus

all		: $(NAME)

clean	:
			rm -f $(OBJS)

fclean	: clean
			rm -f $(NAME)

re		: fclean all
