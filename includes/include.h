#ifndef INCLUDE_H
#define INCLUDE_H
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


//-------------------------------------------------------//
# define WIN_HEIGHT 1000
# define WIN_WIDTH 1000
# define FOV 60
# define NUM_OF_RAYS 200
# define MAP_HEIGHT 10
# define MAP_WIDTH 10
# define CELL_HEIGHT (WIN_HEIGHT / MAP_HEIGHT)
# define CELL_WIDTH (WIN_WIDTH / MAP_WIDTH)
//-------------------------------------------------------//


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

typedef struct s_coord t_coord;

typedef struct s_raydata t_raydata;
//-------------------------------------------------------//


typedef struct	s_textures
{
	void	*addr;
	int		height;
	int		width;
}				t_textures;


typedef struct	s_params
{
	char			**map;
	char			*textures[ALL_TEXTURES];
	int				floor_color[3];
	int				ceiling_color[3];
	t_mlxdata		*mlx;
	t_imgdata		*img;
	t_playerdata	*player;
	t_raydata		*ray;
}				t_params;

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
int			check_map_elements(void);
int			is_map_surrounded(void);
t_textures    *load_tex(void);


//-------------------------------------------------------//
/* Function Prototypes*/
int		ft_write(const char *s);
// void	block_to_pixel_coords(t_params *params, int j, int i);
void	direction_corrector(t_params *params, double angle);
double	deg_to_rad(double angle);
double	rad_to_deg(double angle);
void	draw_ceiling_and_floor(t_params *params);
int		ray_caster(t_params *params);
void	draw_wall(t_params *params, int ray_num, double correction_angle);
int		initiate_mlx(t_params *params, t_mlxdata *mlx, t_imgdata *img);
int		setup_player_and_ray(t_params *params);
int		ray_caster(t_params *params);
//-------------------------------------------------------//


#endif
