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
		*ray_dist_axis = 'b';
		params->ray->cell_y += params->ray->dir_y;
		params->ray->cell_x += params->ray->dir_x;
		*ray_dist_y += params->ray->distance_per_y;
		*ray_dist_x += params->ray->distance_per_x;
	}
	return ;
}

double	find_ray_length(t_params *params, double angle)
{
	double	ray_dist_y;
	double	ray_dist_x;
	char	ray_dist_axis;

	direction_corrector(params, angle);
	params->ray->cell_y = params->player->cell_y;
	params->ray->cell_x = params->player->cell_x;
	ray_dist_y = params->ray->distance_per_y;
	ray_dist_x = params->ray->distance_per_x;
	while (params->ray->cell_y >= 0 && params->ray->cell_x >= 0
		&& params->map[params->ray->cell_y]
		&& params->map[params->ray->cell_y][params->ray->cell_x])
	{
		step_ray(params, &ray_dist_y, &ray_dist_x, &ray_dist_axis);
		if (params->map[params->ray->cell_y][params->ray->cell_x] == '1')
		{
			if (ray_dist_axis == 'y')
				// I think i shouldn't have divided by sin() here.
				return (ray_dist_y  - (3.0 / 2 * params->ray->distance_per_y));
			else
				// same for cos() here.
				return (ray_dist_x  - (3.0 / 2 * params->ray->distance_per_x));
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
	angle = params->player->starting_angle - (FOV / 2);
	correction_angle = (FOV / 2);
	while (ray_num < NUM_OF_RAYS)
	{
		params->ray->distance_per_y
			= fabs(CELL_HEIGHT / sin(deg_to_rad(angle)));
		params->ray->distance_per_x
			= fabs(CELL_WIDTH / cos(deg_to_rad(angle)));
		params->ray->ray_length
			= find_ray_length(params, deg_to_rad(angle));
		draw_wall(params, ray_num, deg_to_rad(fabs(correction_angle)));
		angle += ((double)FOV / NUM_OF_RAYS);
		correction_angle -= ((double)FOV / NUM_OF_RAYS);
		ray_num += 1;
	}
	mlx_put_image_to_window(params->mlx->mlx_ptr, params->mlx->win_ptr,
		params->img->img_ptr, 0, 0);
	return (0);
}
