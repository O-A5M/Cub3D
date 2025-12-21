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

#include "include.h"

/* A function added by oakhmouc that merger the rgb values */
int	merge_colors(int *rgb)
{
	return (rgb[RED] << 16 | rgb[GREEN] << 8 | rgb[BLUE]);
}

/* a function that colors the ceiling and the floor inside the window */
void	draw_ceiling_and_floor(t_params *params)
{
	char			*dst;
	unsigned int	color;
	int				y;
	int				x;

	color = merge_colors(params->ceiling_color);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y == (WIN_HEIGHT / 2))
			color = merge_colors(params->floor_color);
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
	double	wall_height;
	int		y;
	int		x;
	int		y_limit;

	// need to have a better equation for better represntation,
	// 	and also make sure we don't go out of boundaries,
	//	nor have issues when changing the map / window dimensions.
	wall_height = (50 * WIN_HEIGHT)
			/ (params->ray->ray_length * cos(correction_angle));
	y = (int)((WIN_HEIGHT / (double)2) - (wall_height / 2));
	y_limit = WIN_HEIGHT - y;
	x = ray_num;
	while (y < y_limit)
	{
		dst = params->img->img_add + (y * params->img->line_length)
			+ (x * (params->img->bpp / 8));
		*(unsigned int *)dst = 0x0000FF;
		y += 1;
	}
	return ;
}
