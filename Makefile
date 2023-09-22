NAME := miniRT

PATH_SRCS := srcs
PATH_OBJS := objs

PATH_LIBFT := libft
PATH_MLX := mlx

LIBFT := $(PATH_LIBFT)/libft.a
MLX := $(PATH_MLX)/libmlx.a

LIBFT_REPO := git@github.com:Haksell/libft.git
MLX_REPO := git@github.com:42Paris/minilibx-linux.git

RESET := \033[0m
RED := \033[1m\033[31m
GREEN := \033[1m\033[32m

GARBAGE := .vscode
YEET := 1>/dev/null 2>/dev/null

INCLUDES := -I./$(PATH_LIBFT)/includes -I./$(PATH_MLX)
HEADERS := minirt.h

CC := cc -Wall -Wextra -Werror -O3 -g3
LIBRARIES := -L$(PATH_LIBFT) -lft -lX11 -lXext -L$(PATH_MLX) -lmlx -lm

HEADER := minirt.h

vpath %.c $(PATH_SRCS)
SRCS += main

SRCS := $(addsuffix .c, $(SRCS))
OBJS := $(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS))

all: $(NAME)

$(OBJS): $(PATH_OBJS)/%.o: %.c $(HEADERS)
	@mkdir -p $(PATH_OBJS)
	$(CC) -c $< -o $@ $(INCLUDES)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(OBJS) $(LIBRARIES) -o $@

$(PATH_LIBFT):
	@echo "$(GREEN)==> Cloning libft$(RESET)"
	@git clone $(LIBFT_REPO) $@ $(YEET)
	@rm -rf $(PATH_LIBFT)/.git*

$(LIBFT): | $(PATH_LIBFT)
	@echo "$(GREEN)==> Compiling libft$(RESET)"
	@$(MAKE) -s -C $(PATH_LIBFT) $(YEET)

$(PATH_MLX):
	@echo "$(GREEN)==> Cloning mlx$(RESET)"
	@git clone $(MLX_REPO) $@ $(YEET)
	@rm -rf $(PATH_MLX)/.git*

$(MLX): | $(PATH_MLX)
	@echo "$(GREEN)==> Compiling mlx$(RESET)"
	@$(MAKE) -s -C $(PATH_MLX) $(YEET)

clean:
	@rm -rf $(PATH_LIBFT) $(PATH_MLX)
	@echo "$(RED)Libraries removed.$(RESET)"
	@rm -rf $(PATH_OBJS) $(GARBAGE)
	@echo "$(RED)Objects removed.$(RESET)"

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)

run: $(NAME)
	@./$(NAME)

rerun: fclean
	@$(MAKE) -s run

.PHONY: all clean fclean re run rerun
