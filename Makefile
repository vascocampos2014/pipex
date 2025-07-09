CC      = gcc
CFLAGS  = -Wall -Wextra -Werror

NAME    = pipex

SRC_BONUS = srcs/exec.c srcs/parsing.c srcs/handle.c srcs/pipex.c
OBJ_BONUS = $(SRC_BONUS:srcs_bonus/%.c=$(OBJ_DIR)/%.o)
OBJ_DIR = obj

LIBFT_DIR = libft
LIBFT_A   = $(LIBFT_DIR)/libft.a

INCLUDES = -I./$(LIBFT_DIR)/include

all: $(OBJ_DIR) $(OBJ_BONUS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT_A) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: srcs_bonus/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_A):
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all