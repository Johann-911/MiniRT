NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
LIBFT = /Libft/libft.a
LDFLAGS = /Libft/libft
LIBS = -ltf

SRC_FILES = ft_printf.c \
			ft_conversions.c 

OBJS = $(SRC_FILES:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)


%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
