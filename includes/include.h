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

// structer to store the path of
// the texture files.

typedef struct	s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}				t_textures;

// structer to implement the dynamic array consept

typedef struct	s_dynamic_array
{
	size_t	size;
	size_t	count;
	char	**array;
}				t_dynamic_array;

// structer to store all the info
// in the .cub file.

typedef struct	s_map
{
	t_dynamic_array	*map;
	t_textures		*textures;
	int				floore[3];
	int				ceilling[3];
	int				player_pos[2];
}					t_map;

// Parsing functions

char	**read_file(int fd, size_t len);
size_t	file_len(int fd);
int		chech_file_name(char *file_name);
int		open_file(char *file_name);
int		parse_file(char *file_name);
void	free_array(char **arr);
void	free_textures(t_textures **tex);
void	free_map(t_map *map);
int		da_init(t_dynamic_array **da, size_t count);
int		da_append(t_dynamic_array **da, char *s);
void	da_free(t_dynamic_array *da);
t_map	*parse_content(char **content, size_t len);
void	init_map(t_map **map);
void	insert_tex_name(char *content, int *flag, t_map **map);
char	**split_colors(char *content);
int		insert_color(int color, t_map **map, char type, int index);
int		parse_map(char **content, int *index, t_map **map);
int		check_input_struct(t_map *map);

#endif
