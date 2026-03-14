# --- Names and Paths ---
NAME        = minishell
LIBFT       = libft/libft.a
INC         = include/
SRC_DIR     = src/
OBJ_DIR     = obj/

# --- Compilation Flags ---
CC          = cc
CFLAGS      = -Wall -Werror -Wextra -I$(INC)
# Add Readline flags (Standard for 42 Macs/Linux)
LDFLAGS     = -lreadline

# --- Source Files ---
# We use find or manual listing to stay organized
SRC_FILES   = main.c \
              exec/executor.c exec/pipe_utils.c exec/redirections.c \
              parser/lexer.c parser/parser_utils.c \
              builtins/cd.c builtins/pwd.c builtins/env.c \
              signals/signals.c

SRCS        = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS        = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

# --- Colors for terminal output ---
GREEN       = \033[0;32m
RESET       = \033[0m

# --- Rules ---

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Minishell compiled successfully!$(RESET)"

# Compiles Libft
$(LIBFT):
	@make -C libft

# Compiles .c files into .o files in a separate obj/ folder
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C libft
	@rm -rf $(OBJ_DIR)
	@echo "Object files removed."

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "Executable removed."

re: fclean all

.PHONY: all clean fclean re