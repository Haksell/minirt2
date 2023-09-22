NAME := miniRT

PATH_SRCS := srcs
PATH_OBJS := objs

PATH_LIBFT := libft
LIBFT := $(PATH_LIBFT)/libft.a
LIBFT_REPO := git@github.com:Haksell/libft.git

PATH_MLX := mlx
MLX := $(PATH_MLX)/libmlx.a
MLX_REPO := git@github.com:42Paris/minilibx-linux.git

RESET := \033[0m
RED := \033[1m\033[31m
GREEN := \033[1m\033[32m
BLUE := \033[1m\033[34m
PINK := \033[1m\033[35m

GARBAGE := .vscode
YEET := 1>/dev/null 2>/dev/null

CC := cc -Wall -Wextra -Werror -O3 -g3
INCLUDES := -I. -I./$(PATH_LIBFT) -I./$(PATH_MLX)
LIBRARIES := -L$(PATH_LIBFT) -lft -lX11 -lXext -L$(PATH_MLX) -lmlx -lm

HEADER := minirt.h

SRCS += srcs/main.c
SRCS += srcs/utils/complain.c

FILENAMES := $(basename $(SRCS))
FOLDERS := $(sort $(dir $(SRCS)))
OBJS := $(FILENAMES:$(PATH_SRCS)%=$(PATH_OBJS)%.o)

all: $(NAME)

$(PATH_OBJS):
	@mkdir -p $(FOLDERS:$(PATH_SRCS)%=$(PATH_OBJS)%)

$(OBJS): $(PATH_OBJS)/%.o: $(PATH_SRCS)/%.c $(HEADER) | $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)
	@$(CC) -c $< -o $@ $(INCLUDES)
	@echo "$(BLUE)✓ $@$(RESET)"

$(NAME): $(LIBFT) $(MLX)
	@$(MAKE) $(OBJS)
	@$(CC) $(OBJS) $(LIBRARIES) -o $@
	@echo "$(PINK)$@ is compiled.$(RESET)"

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

norm:
	@./scripts/niih $(PATH_LIBFT) $(HEADER) $(PATH_SRCS)

.PHONY: all clean fclean re run rerun norm
