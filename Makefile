# The compiler and flags

CC	  = cc
######################## removed the flags for testing, don't forget to put them back ###########################
FLAGS = -Wall -Wextra -Werror -g3 -g -O3 -Iincludes -Ilibraries/libft -Ilibraries/minilibx-linux -Isrc/raycasting

# external libraries

LIBFT_D = libraries/libft
LIBFT_N = $(LIBFT_D)/libft.a
LIBFT   = ft

# Source and object files

SRC    = main/main.c src/parsing/lines_utils.c src/parsing/parse_args.c\
		 src/parsing/params_utils.c src/parsing/read_file.c\
		 src/parsing/separate_elements.c src/parsing/other_utils.c\
		 src/parsing/separate_elements_map.c src/parsing/separate_elements_colors.c\
		 src/parsing/separate_elements_textures.c src/parsing/check_map_elements.c\
		 src/raycasting/basic_utilities/basic_utils_0.c src/raycasting/calculation_utilities/calc_utils_0.c\
		 src/raycasting/calculation_utilities/render.c src/raycasting/calculation_utilities/calc_utils_1.c\
		 src/raycasting/drawing_utilities/draw_utils_0.c #src/raycasting/extra_stuff/map_2d_code.c\
		 src/raycasting/extra_stuff/fun.c

OBJDIR = obj
OBJS   = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

# Name

NAME = cub3D

# Rules

all: $(LIBFT_N) $(NAME)

$(LIBFT_N):
	make -C $(LIBFT_D)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -L./$(LIBFT_D) -l$(LIBFT) -lm -o $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_D)
	echo ${NAME}
	rm $(OBJDIR) -fr

fclean: clean
	make fclean -C $(LIBFT_D)
	rm $(NAME) -fr

re: fclean all

do: fclean all
	make clean -C $(LIBFT_D)
	rm $(OBJDIR) -fr
	clear

.SECONDARY: $(OBJS)
.PHONY: clean
