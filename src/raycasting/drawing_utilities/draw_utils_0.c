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
// #include "../rayclude.h"
#include "include.h"

/* a function that colors the ceiling and the floor inside the window */
void	draw_ceiling_and_floor(t_params *params)
{
	char			*dst;
	unsigned int	color;
	int				y;
	int				x;

	color = (unsigned int)merge_colors(params->ceiling_color);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y == (WIN_HEIGHT / 2))
			color = (unsigned int)merge_colors(params->floor_color);
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
void	draw_wall(t_params *params, int ray_num, double correction_angle)
{
	char	*dst;
	int		counter;
	double	wall_height;
	t_coord	coords;

	wall_height = WIN_HEIGHT * (100 / (params->ray->ray_length
				* cos(correction_angle)));
	// what if this is negative???
	coords.y = (WIN_HEIGHT / (double)2) - (wall_height / 2);
	coords.x = (WIN_WIDTH / (double)200) * ray_num;
	while ((int)wall_height > 0)
	{
		counter = 1;
		// need to use MACROS or variables, don't forget the hardcoded values here
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
