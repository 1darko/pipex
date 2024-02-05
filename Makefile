# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Name
NAME = pipex

# Dir
SRC_DIR = .
OBJ_DIR = $(SRC_DIR)

# Source files
SRC_FILES = pipex.c err_display.c ft_calloc.c ft_split.c ft_strdup.c \
            ft_strlen.c get_path.c free_array.c ft_putstr_fd.c ft_strcmp.c \
            get_env.c path_check.c

# Object files
OBJ_FILES = $(SRC_FILES:.c=.o)

# Paths
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))


# Rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "⬜🟥🟥🟥🟥⬜⬜⬜"
	@echo "🟥🟥🟥🟥🟥🟥🟥🟥"
	@echo "🟫🟫🟫🟧🟫🟧⬜⬜"
	@echo "🟧🟫🟧🟧🟫🟧🟧🟧"
	@echo "🟧🟫🟫🟧🟧🟫🟧🟧"
	@echo "⬜🟧🟧🟧🟫🟫🟫⬜ YOUR PIPE(X) IS READY"
	@echo "⬜⬜🟧🟧🟧🟧⬜⬜"
	@echo "⬜🟫🟥🟫🟫🟥🟫⬜"
	@echo "🟫🟫🟥🟫🟫🟥🟫🟫"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


