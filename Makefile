NAME = fractol

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJ)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
