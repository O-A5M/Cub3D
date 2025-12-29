/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:09:48 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/12/10 18:26:47 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	step_ray(t_params *params, double *ray_dist_y,
			double *ray_dist_x, char *ray_dist_axis)
{
	if (*ray_dist_y < *ray_dist_x)
	{
		*ray_dist_axis = 'y';
		params->ray->cell_y += params->ray->dir_y;
		*ray_dist_y += params->ray->distance_per_y;
	}
	else if (*ray_dist_y > *ray_dist_x)
	{
		*ray_dist_axis = 'x';
		params->ray->cell_x += params->ray->dir_x;
		*ray_dist_x += params->ray->distance_per_x;
	}
	else
	{
		//special case will need FURTHER INSPECTION later!!!
		*ray_dist_axis = 'b';
		params->ray->cell_y += params->ray->dir_y;
		params->ray->cell_x += params->ray->dir_x;
		*ray_dist_y += params->ray->distance_per_y;
		*ray_dist_x += params->ray->distance_per_x;
	}
	return ;
}

int	check_cell(t_params *params, char ray_dist_axis)
{
	char	**map;
	int		y;
	int		x;
	int		dir_y;
	int		dir_x;

	map = params->map;
	y = params->ray->cell_y;
	x = params->ray->cell_x;
	dir_y = params->ray->dir_y;
	dir_x = params->ray->dir_x;
	printf("cell y: %d  ;  cell x: %d\n", y, x);
	if (map[y][x] != '0')
		return (1);
	if (ray_dist_axis == 'b')
	{
		if ((map[y - dir_y][x] != '0') || (map[y][x - dir_x] != '0'))
			return (1);
	}
	return (0);
}

double	find_ray_length(t_params *params, double angle)
{
	double	ray_dist_y;
	double	ray_dist_x;
	char	ray_dist_axis;

	params->ray->cell_y = params->player->cell_y;
	params->ray->cell_x = params->player->cell_x;
	direction_corrector(params, angle);
	ray_dist_y = params->ray->distance_per_y;
	ray_dist_x = params->ray->distance_per_x;
	while (37)
	{
		step_ray(params, &ray_dist_y, &ray_dist_x, &ray_dist_axis);
		if (check_cell(params, ray_dist_axis))
		{
			if (ray_dist_axis == 'y')
				return (ray_dist_y - (1.5 * params->ray->distance_per_y));
			else
				return (ray_dist_x - (1.5 * params->ray->distance_per_x));
		}
	}
	return (0);
}

/* The Function that does the whole ray casting thing */
int	ray_caster(t_params *params)
{
	int			ray_num;
	double		angle;
	double		correction_angle;

	ray_num = 0;
	angle = params->player->starting_angle + (FOV / 2);
	correction_angle = (FOV / 2);
	while (ray_num < NUM_OF_RAYS)
	{
		printf("ray n %d\n\n", ray_num);
		params->ray->distance_per_y
			= fabs(CELL_HEIGHT / fabs(sin(deg_to_rad(angle))));
		params->ray->distance_per_x
			= fabs(CELL_WIDTH / fabs(cos(deg_to_rad(angle))));
		params->ray->ray_length
			= find_ray_length(params, deg_to_rad(angle));
		draw_wall(params, ray_num, deg_to_rad(fabs(correction_angle)));
		angle -= ((double)FOV / NUM_OF_RAYS);
		correction_angle -= ((double)FOV / NUM_OF_RAYS);
		ray_num += 1;
	}
	mlx_put_image_to_window(params->mlx->mlx_ptr, params->mlx->win_ptr,
		params->img->img_ptr, 0, 0);
	return (0);
}
