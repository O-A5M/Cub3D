
# The compiler and flags

CC	  = cc
######################## removed the flags for testing, don't forget to put them back ###########################
FLAGS  = -Wall -Wextra -Werror -g3 -g -O3 -Iincludes -Ilibraries/libft -Isrc/raycasting
XFLAGS = -lmlx -lm -lXext -lX11

# external libraries

LIBFT_D = libraries/libft
LIBFT_N = $(LIBFT_D)/libft.a
LIBFT   = ft

# Source and object files

SRC = mandatory/main/main.c \
      mandatory/src/parsing/lines_utils.c \
      mandatory/src/parsing/parse_args.c \
      mandatory/src/parsing/params_utils.c \
      mandatory/src/parsing/read_file.c \
      mandatory/src/parsing/separate_elements.c \
      mandatory/src/parsing/other_utils.c \
      mandatory/src/parsing/separate_elements_map.c \
      mandatory/src/parsing/separate_elements_colors.c \
      mandatory/src/parsing/separate_elements_textures.c \
      mandatory/src/parsing/check_map_elements.c \
      mandatory/src/raycasting/initialization_utilities/init_utils_0.c \
      mandatory/src/raycasting/basic_utilities/basic_utils_0.c \
      mandatory/src/raycasting/calculation_utilities/calc_utils_0.c \
      mandatory/src/raycasting/calculation_utilities/render.c \
      mandatory/src/raycasting/drawing_utilities/draw_utils_0.c \
      mandatory/src/textures/load_textures.c \
      mandatory/src/raycasting/drawing_utilities/draw_textures.c \
      mandatory/src/raycasting/calculation_utilities/calc_utils_1.c \
      mandatory/src/events/events.c \
      mandatory/src/events/hooks.c 

BONUS_SRC = bonus/main/main.c \
            bonus/src/parsing/lines_utils.c \
            bonus/src/parsing/parse_args.c \
            bonus/src/parsing/params_utils.c \
            bonus/src/parsing/read_file.c \
            bonus/src/parsing/separate_elements.c \
            bonus/src/parsing/other_utils.c \
            bonus/src/parsing/separate_elements_map.c \
            bonus/src/parsing/separate_elements_colors.c \
            bonus/src/parsing/separate_elements_textures.c \
            bonus/src/parsing/check_map_elements.c \
            bonus/src/raycasting/initialization_utilities/init_utils_0.c \
            bonus/src/raycasting/basic_utilities/basic_utils_0.c \
            bonus/src/raycasting/calculation_utilities/calc_utils_0.c \
            bonus/src/raycasting/calculation_utilities/render.c \
            bonus/src/raycasting/drawing_utilities/draw_utils_0.c \
            bonus/src/textures/load_textures.c \
            bonus/src/raycasting/drawing_utilities/draw_textures.c \
            bonus/src/raycasting/calculation_utilities/calc_utils_1.c \
            bonus/src/events/events.c \
            bonus/src/bonus/collision_bonus.c \
            bonus/src/bonus/mouse_bonus.c \
            bonus/src/bonus/minimap_bonus.c

OBJDIR      = obj
OBJS        = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))
BONUS_OBJS  = $(patsubst %.c,$(OBJDIR)/%.o,$(BONUS_SRC))

# Names

NAME        = cub3D
NAME_BONUS  = cub3D_bonus

# Rules

all: $(LIBFT_N) $(NAME)

bonus: $(LIBFT_N) $(NAME_BONUS)

$(LIBFT_N):
	make -C $(LIBFT_D)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -L./$(LIBFT_D) -l$(LIBFT) -lm -o $(NAME) $(XFLAGS)

$(NAME_BONUS): $(BONUS_OBJS)
	$(CC) $(BONUS_OBJS) -L./$(LIBFT_D) -l$(LIBFT) -lm -o $(NAME_BONUS) $(XFLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_D)
	rm -rf $(OBJDIR)

fclean: clean
	make fclean -C $(LIBFT_D)
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

do: fclean all
	make clean -C $(LIBFT_D)
	rm -rf $(OBJDIR)
	clear

.SECONDARY: $(OBJS) $(BONUS_OBJS)
.PHONY: all bonus clean fclean re

