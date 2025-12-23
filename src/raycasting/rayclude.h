/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayclude.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:38:20 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/12/14 18:56:49 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCLUDE_H
# define RAYCLUDE_H

/* the MACROs */
# define WIN_HEIGHT  1000
# define WIN_WIDTH 	 1000
# define MAP_HEIGHT  10
# define MAP_WIDTH 	 10
# define FOV         60
# define NUM_OF_RAYS 1000 /* must be equal to WIN_WIDTH */
# define CELL_HEIGHT 1
# define CELL_WIDTH  1

typedef struct	s_params t_params;

/* an enum for player directions */
typedef enum directions
{
	UP,
	DOWN,
	RIGHT,
	LEFT
}				t_direction;

/* a structure for window creation info */
typedef struct s_mlxdata
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlxdata;

/* a structure for image info */
typedef struct s_imgdata
{
	void	*img_ptr;
	void	*img_add;
	int		bpp;
	int		line_length;
	int		endian;
}				t_imgdata;

/* a structure for player info */
typedef struct s_playerdata
{
	double	pixel_x;
	double	pixel_y;
	double	cell_y;
	double	cell_x;
	char	direction;
	double	starting_angle;
}				t_playerdata;

/* a structure for coordiations type */
typedef struct s_coord
{
	double	y;
	double	x;
}				t_coord;

/* a structure for ray info */
typedef struct s_raydata
{
	double	ray_length;
	double	cell_y;
	double	cell_x;
	double	dir_y;
	double	dir_x;
	double	distance_per_y;
	double	distance_per_x;

}				t_raydata;

/* Function Prototypes*/
int		ft_write(const char *s);
int		initiate_mlx(t_params *params, t_mlxdata *mlx, t_imgdata *img);
void	direction_corrector(t_params *params, double angle);
double	deg_to_rad(double angle);
double	rad_to_deg(double angle);
void	draw_ceiling_and_floor(t_params *params);
int		ray_caster(t_params *params);
void	draw_wall(t_params *params, int ray_num, double correction_angle);
int		calc_map_width_and_height(t_params *params);
int		set_pixel_coords(t_params *params);
int		set_starting_angle(t_params *params);
int		create_minimap(t_params *params);

#endif /* RAYCLUDE_H */
