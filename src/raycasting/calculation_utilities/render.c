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

#include "../rayclude.h"

void	next_cell_finder(t_data *data, double *close_y,
			double *close_x, char *last_met)
{
	if (*close_y < *close_x)
	{
		*last_met = 'y';
		data->ray->cell_y += data->ray->dir_y;
		*close_y += data->ray->distance_per_y;
	}
	else if (*close_y > *close_x)
	{
		*last_met = 'x';
		data->ray->cell_x += data->ray->dir_x;
		*close_x += data->ray->distance_per_x;
	}
	else
	{
		*last_met = 'b';
		data->ray->cell_y += data->ray->dir_y;
		data->ray->cell_x += data->ray->dir_x;
		*close_y += data->ray->distance_per_y;
		*close_x += data->ray->distance_per_x;
	}
	return ;
}

double	find_wall(t_params *params, double angle)
{
	double	close_y;
	double	close_x;
	char	last_met;

	direction_corrector(params, angle);
	data->ray->cell_y = data->player->cell_y;
	data->ray->cell_x = data->player->cell_x;
	close_y = data->ray->distance_per_y;
	close_x = data->ray->distance_per_x;
	while (params->map[data->ray->cell_y] && params->map[data->ray->cell_y][data->ray->cell_x])
	{
		next_cell_finder(data, &close_y, &close_x, &last_met);
		if (map[data->ray->cell_y][data->ray->cell_x] == '1')
		{
			if (last_met == 'y')
				return ((close_y  - (3.0 / 2 * data->ray->distance_per_y))
					/ fabs(sin(angle)));
			else
				return ((close_x  - (3.0 / 2 * data->ray->distance_per_x))
				/ fabs(cos(angle)));
		}
	}
	return (0);
}

/* a function that casts the rays */
void	ray_caster(t_params *params)
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
		params->ray->ray_length = find_wall(params, deg_to_rad(angle), map);
		draw_wall(params, ray_num, correction_angle);
		angle += ((double)FOV / NUM_OF_RAYS);
		correction_angle -= ((double)FOV / NUM_OF_RAYS);
		ray_num += 1;
	}
}
