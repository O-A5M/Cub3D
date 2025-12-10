/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayclude.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:38:20 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/12/10 18:43:49 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCLUDE_H
# define RAYCLUDE_H

/* the header inclusions */
# include "include.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "mlx.h"
# include <X11/keysym.h>

/* the MACROs */
# define WIN_HEIGHT 1000
# define WIN_WIDTH 1000
# define FOV 60
# define NUM_OF_RAYS 200
# define MAP_HEIGHT 10
# define MAP_WIDTH 10
# define GRID_HEIGHT (WIN_HEIGHT / MAP_HEIGHT)
# define GRID_WIDTH (WIN_WIDTH / MAP_WIDTH)

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
	double			x;
	double			y;
	int				grid_y;
	int				grid_x;
	char			direction;
	double			starting_angle;
}				t_playerdata;

typedef struct s_coord
{
	double	y;
	double	x;
}				t_coord;

typedef struct s_raydata
{
	double	ray_length;
	int		grid_y;
	int		grid_x;
	int		y_dir;
	int		x_dir;
	double	nearest_blocky;
	double	nearest_blockx;

}				t_raydata;

/* a structure that holds the important data to comfortably use it around */
typedef struct s_data
{
	t_mlxdata		*mlx;
	t_imgdata		*img;
	t_playerdata	*player;
	t_raydata		*ray;
	unsigned int	ceiling_color;
	unsigned int	floor_color;
}				t_data;

/* Function Prototypes*/
int		ft_write(const char *s);
void	block_to_pixel_coords(t_params *params, int j, int i);
void	direction_corrector(t_params *params, double angle);
double	deg_to_rad(double angle);
double	rad_to_deg(double angle);
int		render(t_params *params);
void	draw_ceiling_and_floor(t_params *params);
void	draw_wall(t_params *params, int ray_num, double corr_angle);
int		initiate_mlx(t_params *params, t_mlxdata *mlx, t_imgdata *img);
int		initiate_player_and_ray(t_params *params, t_playerdata *player,
			t_raydata *ray);
int		render(t_params *params);

#endif /* RAYCLUDE_H */
