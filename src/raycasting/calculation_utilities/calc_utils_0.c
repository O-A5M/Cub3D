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

// #include "../rayclude.h"
#include "include.h"

// void	block_to_pixel_coords(t_params *params, int j, int i)
// {
// 	params->player->cell_y = j;
// 	params->player->cell_x = i;
// 	params->player->pixel_y = (j + 1 / (double)2) * (WIN_HEIGHT / (double)MAP_HEIGHT);
// 	params->player->pixel_x = (i + 1 / (double)2) * (WIN_WIDTH / MAP_WIDTH);
// 	if (params->player->direction == 'N')
// 		params->player->starting_angle = M_PI / 2;
// 	else if (params->player->direction == 'S')
// 		params->player->starting_angle = M_PI * 3 / 2;
// 	else if (params->player->direction == 'E')
// 		params->player->starting_angle = 0;
// 	else if (params->player->direction == 'W')
// 		params->player->starting_angle = M_PI;
// }

void	direction_corrector(t_params *params, double angle)
{
	params->ray->dir_y = -1;
	params->ray->dir_x = 1;
	if (angle >= 0 && angle < (M_PI / 2))
		params->ray->dir_y = 1;
	else if (angle >= M_PI && angle < (M_PI * 3 / 2))
		params->ray->dir_x = -1;
	else if (angle >= (M_PI / 2) && angle < M_PI)
	{
		params->ray->dir_y = 1;
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
