/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:51:32 by aelmsafe          #+#    #+#             */
/*   Updated: 2026/01/02 08:18:34 by oakhmouc         ###   ########.fr       */
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
	double	wall_real_height;
	double	wall_height;
	int		y;
	int		y_limit;

	wall_height = (CELL_SIZE
			/ (params->ray->ray_length * fabs(cos(correction_angle))))
		* ((WIN_WIDTH / 2) / tan(deg_to_rad(FOV / 2)));
	wall_real_height = wall_height;
	if (wall_height > WIN_HEIGHT)
		wall_height = WIN_HEIGHT;
	y = (WIN_HEIGHT / 2.0) - (wall_height / 2.0);
	y_limit = WIN_HEIGHT - y;
	while (y < y_limit)
	{
		dst = params->img->img_add + (y * params->img->line_length)
			+ (ray_num * (params->img->bpp / 8));
		*(unsigned int *)dst
			= *(unsigned int *)texture_pixel(wall_real_height, y);
		y += 1;
	}
	return ;
}
