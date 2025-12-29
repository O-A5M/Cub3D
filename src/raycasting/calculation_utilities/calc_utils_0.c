/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:23:52 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/12/10 18:30:53 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	set_pixel_coords(t_params *params)
{
	if (params->player->cell_x < 0 || params->player->cell_y < 0
		|| params->player->direction == 0)
		return (1);
	params->player->pixel_y = (params->player->cell_y + 0.5)
		* (WIN_HEIGHT / params->map_height_2d);
	params->player->pixel_x = (params->player->cell_x + 0.5)
		* (WIN_WIDTH / params->map_width_2d);
	return (0);
}

int	calc_map_width_and_height(t_params *params)
{
	int	i;
	int	j;
	int	height;
	int	width;

	if (!params->map || !params->map[0])
		return (1);
	height = 0;
	width = 0;
	j = 0;
	/* I think I am counting the spaces on the edge too, attention */
	while (params->map[j])
	{
		height += 1;
		i = 0;
		while (params->map[j][i])
		{
			if (i > width)
				width = i;
			i += 1;
		}
		j += 1;
	}
	params->map_width_2d = width;
	params->map_height_2d = height;
	return (0);
}

int	set_starting_angle(t_params *params)
{
	if (params->player->direction == 'E')
		params->player->starting_angle = 0;
	else if (params->player->direction == 'N')
		params->player->starting_angle = 90;
	else if (params->player->direction == 'W')
		params->player->starting_angle = 180;
	else if (params->player->direction == 'S')
		params->player->starting_angle = 270;
	else
		return (1);
	return (0);
}

void	direction_corrector(t_params *params, double angle)
{
	params->ray->dir_y = 1;
	params->ray->dir_x = 1;
	if (angle >= 0 && angle < (M_PI / 2))
		params->ray->dir_y = -1;
	else if (angle >= M_PI && angle < (M_PI * 3 / 2))
		params->ray->dir_x = -1;
	else if (angle >= (M_PI / 2) && angle < M_PI)
	{
		params->ray->dir_y = -1;
		params->ray->dir_x = -1;
	}
}

double	deg_to_rad(double angle)
{
	double	ang;

	ang = angle;
	if (ang < 0)
		while (ang < 0)
			ang += 360;
	if (ang > 360)
		ang = fmod(ang, 360);
	ang *= (M_PI / 180);
	return (ang);
}

double	rad_to_deg(double angle)
{
	double	ang;

	ang = angle;
	ang *= (180 / M_PI);
	if (ang < 0)
		while (ang < 0)
			ang += 360;
	if (ang > 360)
		ang = fmod(ang, 360);
	return (ang);
}
