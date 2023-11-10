NAME	:= fractol

CFLAGS	:= -Wextra -Wall -Werror

LIBMLX	:= ./lib/MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include

LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCDIR := ./src/

SRCS	:=  $(SRCDIR)fractol.c \
			$(SRCDIR)hooks.c \
			$(SRCDIR)utils.c \
			$(SRCDIR)algorithms.c \
			$(SRCDIR)strtodo.c

OBJS	:= ${SRCS:.c=.o}

CC		:= gcc

all: libmlx $(NAME)

libft:
	@make -C ./lib/libft

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS) libft
	@$(CC) $(OBJS) $(LIBS) ./lib/libft/libftprintf.a $(HEADERS) -o $(NAME)

clean:
	@make -C ./lib/libft clean
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@make -C ./lib/libft fclean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
