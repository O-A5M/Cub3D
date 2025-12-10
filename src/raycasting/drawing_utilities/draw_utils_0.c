/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:51:32 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/12/10 18:14:51 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <math.h>
#include "../rayclude.h"

/* a function that colors the ceiling and the floor inside the window */
void	draw_ceiling_and_floor(t_params *params)
{
	char			*dst;
	unsigned int	color;
	int				y;
	int				x;

	color = params->ceiling_color;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y == (WIN_HEIGHT / 2))
			color = params->floor_color;
		x = 0;
		while (x < WIN_WIDTH)
		{
			dst = params->img->img_add + (y * params->img->line_length)
				+ (x * (params->img->bpp / 8));
			*(unsigned int *)dst = color;
			x += 1;
		}
		y += 1;
	}
	return ;
}

/* a function that draws a vertical line representing a casted ray*/
void	draw_wall(t_params *params, int ray_num, double corr_angle)
{
	char	*dst;
	int		counter;
	double	wall_height;
	t_coord	coords;

	params->ray->ray_length *= cos(corr_angle * (M_PI / 180));
	wall_height = WIN_HEIGHT * (100 / (params->ray->ray_length
				* cos(corr_angle * (M_PI / 180))));
	coords.y = (WIN_HEIGHT / 2) - (wall_height / 2);
	coords.x = ray_num * (WIN_WIDTH / 200);
	while (wall_height > 0)
	{
		counter = 1;
		while (counter < 4)
		{
			dst = params->img->img_add + ((int)coords.y * params->img->line_length)
				+ (((int)coords.x + counter) * (params->img->bpp / 8));
			*(unsigned int *)dst = 0xFF0000FF;
			counter += 1;
		}
		coords.y += 1;
		wall_height -= 1;
	}
	return ;
}
