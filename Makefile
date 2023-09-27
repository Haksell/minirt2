NAME := miniRT
HEADER := minirt.h # TODO: headers
DEFAULT_SCENE := scenes/valid/image21.rt

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

CC := cc -Wall -Wextra -Werror -Ofast -mavx -g3
INCLUDES := -I./ -I./$(PATH_LIBFT) -I./$(PATH_MLX)
LIBRARIES := -L$(PATH_LIBFT) -lft -lX11 -lXext -L$(PATH_MLX) -lmlx -lm

FILENAMES += main
FILENAMES += display/get_color
FILENAMES += display/light_effects
FILENAMES += display/phong
FILENAMES += display/ray
FILENAMES += display/render_frame
FILENAMES += display/render_frame2
FILENAMES += display/scatter
FILENAMES += hit/hit_disk
FILENAMES += hit/hit_plane
FILENAMES += hit/hit_sphere
FILENAMES += hit/hit_tube
FILENAMES += hit/hit_world
FILENAMES += init/init_minilibx
FILENAMES += init/init_multithreading
FILENAMES += init/init_pixels
FILENAMES += parsing/ft_atof
FILENAMES += parsing/get_commas
FILENAMES += parsing/get_words
FILENAMES += parsing/parse_elements
FILENAMES += parsing/parse_material
FILENAMES += parsing/parse_objects
FILENAMES += parsing/parse_scene
FILENAMES += parsing/parse_vectors
FILENAMES += random/random_float
FILENAMES += random/random_uint
FILENAMES += random/random_vector
FILENAMES += structs/interval
FILENAMES += structs/vec3a
FILENAMES += structs/vec3b
FILENAMES += utils/arrays
FILENAMES += utils/clean
FILENAMES += utils/complain
FILENAMES += utils/math
FILENAMES += utils/print # TODO: remove

PATH_SRCS := srcs
PATH_OBJS := objs

SRCS := $(addprefix $(PATH_SRCS)/, $(addsuffix .c, $(FILENAMES)))
OBJS := $(addprefix $(PATH_OBJS)/, $(addsuffix .o, $(FILENAMES)))

define clone_repo
	@echo "$(GREEN)==> Cloning $(1)$(RESET)"
	@git clone $(2) $(1) $(YEET)
	@rm -rf $(1)/.git*
endef

define compile_target
	@echo "$(GREEN)==> Compiling $(1)$(RESET)"
	@$(MAKE) -s -C $(1) $(YEET)
endef

define remove_target
@if [ -e "$(1)" ]; then \
	rm -rf "$(1)"; \
	echo "$(RED)[X] $(1) removed.$(RESET)"; \
fi
endef

all: $(NAME)

$(PATH_OBJS):
	@mkdir -p $(sort $(dir $(OBJS)))

$(OBJS): $(PATH_OBJS)/%.o: $(PATH_SRCS)/%.c $(HEADER) $(LIBFT) $(MLX) | $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)
	@$(CC) -c $< -o $@ $(INCLUDES)
	@echo "$(BLUE)+++ $@$(RESET)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBRARIES) -o $@
	@echo "$(PINK)$@ is compiled.$(RESET)"

$(PATH_LIBFT):
	$(call clone_repo,$(PATH_LIBFT),$(LIBFT_REPO))

$(LIBFT): | $(PATH_LIBFT)
	$(call compile_target,$(PATH_LIBFT))

$(PATH_MLX):
	$(call clone_repo,$(PATH_MLX),$(MLX_REPO))

$(MLX): | $(PATH_MLX)
	$(call compile_target,$(PATH_MLX))

clean:
	@rm -rf $(GARBAGE)
	$(call remove_target,$(PATH_LIBFT))
	$(call remove_target,$(PATH_MLX))
	$(call remove_target,$(PATH_OBJS))

fclean: clean
	$(call remove_target,$(NAME))

re: fclean
	@$(MAKE) -s $(NAME)

run: $(NAME)
	@./$(NAME) $(or $(firstword $(filter-out $@, $(MAKECMDGOALS))), $(DEFAULT_SCENE))

rerun: fclean
	@$(MAKE) -s run

norm:
	@./scripts/niih $(PATH_LIBFT) $(HEADER) $(PATH_SRCS)

%:
	@true

.PHONY: all clean fclean re run rerun norm
