#ifndef INCLUDE_H
# define INCLUDE_H

/* the header inclusions */
# include <stddef.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "mlx.h"
# include "libft.h"
# include <X11/keysym.h>
# include "rayclude.h"

#define ALL_TEXTURES 4
#define NORTH_TEX 0
#define SOUTH_TEX 1
#define EAST_TEX 2
#define WEST_TEX 3
#define PLAYER_RADIUS 0.15

#define RED 0
#define GREEN 1
#define BLUE 2

typedef struct	s_lines
{
	char			*line;
	struct s_lines	*next;
}				t_lines;


//-------------------------------------------------------//
/* a structure for window creation info */
typedef struct s_mlxdata t_mlxdata;

/* a structure for image info */
typedef struct s_imgdata t_imgdata;

/* a structure for player info */
typedef struct s_playerdata t_playerdata;

/* a structure for coordiations type */
typedef struct s_coord t_coord;

/* a structure for ray info */
typedef struct s_raydata t_raydata;

/* a structure to hold the textures infos */
typedef struct s_tex_info
{
	void	*img;
	char	*addr;
	int		height;
	int		width;
	int		bpp;
	int		line_len;
	int		endian;
}				t_tex_info;

/* a structure that holds everything altogether plus some more infos */
typedef struct	s_params
{
	char			**map;
	char			*textures[ALL_TEXTURES];
	int				floor_color[3];
	int				ceiling_color[3];
	int				map_height_2d;
	int				map_width_2d;
	t_mlxdata		*mlx;
	t_imgdata		*img;
	t_playerdata	*player;
	t_raydata		*ray;
	t_tex_info		tex_info[4];
	int				player_move;
}				t_params;

/* Function Prototypes*/
t_lines		*new_line(char *str);
void		add_line(t_lines **head, t_lines *line);
t_lines		*last_line(t_lines *head);
size_t		lines_count(t_lines *head);
void		free_lines(t_lines **head);
t_params	*params_holder(void);
void		params_init(t_params **params, t_raydata *ray, t_playerdata *player);
void		free_params(t_params **params);
int			parse_args(char *filename);
t_lines		*extract_file_content(int fd);
int			parse_content(t_lines *file_content);
int			separate_elements(t_lines *file_content);
void		free_array(char	***arr);
int			add_tex(t_lines *file_content);
int			add_color(t_lines *file_content);
int			add_map(t_lines *file_content);
int			check_map_elements(t_params *params);
int			is_map_surrounded(void);
int			load_textures(void);
char		*texture_pixel(double wall_height, int y);

#endif
