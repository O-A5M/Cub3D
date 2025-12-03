#ifndef INCLUDE_H
# define INCLUDE_H
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "mlx.h"
#include "libft.h"

#define ALL_TEXTURES 6
#define NORTH_TEX 0
#define SOUTH_TEX 1
#define EAST_TEX 2
#define WEST_TEX 3
#define DOOR_TEX 4
#define SPRITE_TEX 5

#define RED 0
#define GREEN 1
#define BLUE 2

typedef struct	s_lines
{
	char			*line;
	struct s_lines	*next;
}				t_lines;

typedef struct	s_params
{
	char	**map;
	char	*textures[ALL_TEXTURES];
	char	player_direction;
	int		floor_color[3];
	int		ceiling_color[3];
	int		player_posX;
	int		player_posY;
}				t_params;

t_lines		*new_line(char *str);
void		add_line(t_lines **head, t_lines *line);
t_lines		*last_line(t_lines *head);
size_t		lines_count(t_lines *head);
void		free_lines(t_lines **head);
t_params	*params_holder(void);
void		params_init(t_params **params);
void		free_params(t_params **params);
int			parse_args(char *filename);
t_lines		*extract_file_content(int fd);
int			parse_content(t_lines *file_content);
int			separate_elements(t_lines *file_content);
void		free_array(char	***arr);
int			add_tex(t_lines *file_content);
int			add_color(t_lines *file_content);
int			add_map(t_lines *file_content);
int			check_map_elements(void);
int			is_map_surrounded(void);

#endif
