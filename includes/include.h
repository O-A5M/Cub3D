#ifndef INCLUDE_H
# define INCLUDE_H
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

// structer to store all the info
// in the .cub file.

typedef struct	s_map
{
	char		**map;
	t_textures	*textures;
	int			floore[3];
	int			ceilling[3];
}				t_map;

// Parsing functions

char	**read_file(int fd, size_t len);
size_t	file_len(int fd);
int		chech_file_name(char *file_name);
int		open_file(char *file_name);
int		parse_file(char *file_name);
void	free_array(char **arr);
void	free_textures(t_textures **tex);
void	free_map(t_map **map);

#endif
