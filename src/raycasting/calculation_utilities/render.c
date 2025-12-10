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

void	next_grid_finder(t_data *data, double *close_y,
			double *close_x, char *last_met)
{
	if (*close_y < *close_x)
	{
		*last_met = 'y';
		data->ray->grid_y += data->ray->y_dir;
		*close_y += data->ray->nearest_blocky;
	}
	else if (*close_y > *close_x)
	{
		*last_met = 'x';
		data->ray->grid_x += data->ray->x_dir;
		*close_x += data->ray->nearest_blockx;
	}
	else
	{
		*last_met = 'b';
		data->ray->grid_y += data->ray->y_dir;
		data->ray->grid_x += data->ray->x_dir;
		*close_y += data->ray->nearest_blocky;
		*close_x += data->ray->nearest_blockx;
	}
	return ;
}

double	find_wall(t_data *data, double angle)
{
	double	close_y;
	double	close_x;
	char	last_met;

	direction_corrector(data, angle);
	data->ray->grid_y = data->player->grid_y;
	data->ray->grid_x = data->player->grid_x;
	close_y = data->ray->nearest_blocky;
	close_x = data->ray->nearest_blockx;
	while (data->ray->grid_y >= 0 && data->ray->grid_y <= 9
			&& data->ray->grid_x >= 0 && data->ray->grid_x <= 9)
	{
		next_grid_finder(data, &close_y, &close_x, &last_met);
		if (map[data->ray->grid_y][data->ray->grid_x] == '1')
		{
			if (last_met == 'y')
				return ((close_y  - (3.0 / 2 * data->ray->nearest_blocky))
					/ fabs(sin(angle)));
			else
				return ((close_x  - (3.0 / 2 * data->ray->nearest_blockx))
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

	params->ray->ray_length = 0;
	ray_num = 0;
	angle = rad_to_deg(params->player->starting_angle) - (FOV / 2);
	correction_angle = (FOV / 2);
	while (ray_num < NUM_OF_RAYS)
	{
		params->ray->nearest_blocky
			= fabs(GRID_HEIGHT / (sin(deg_to_rad(angle))));
		params->ray->nearest_blockx
			= fabs(GRID_WIDTH / (cos(deg_to_rad(angle))));
		params->ray->ray_length = find_wall(params, deg_to_rad(angle), map);
		draw_wall(params, ray_num, correction_angle);
		angle += 0.3000000000;
		correction_angle -= 0.3;
		ray_num += 1;
	}
}

/* the function that starts everything rendering wise */
int	render(t_params *params)
{
	draw_ceiling_and_floor(params);
	ray_caster(data, map);
	return (0);
}
