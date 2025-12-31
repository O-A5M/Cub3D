/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 03:09:34 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/12/31 05:45:42 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	get_wall_dir(t_params *params)
{
	if (params->ray->ray_axis == 'x')
	{
		if (params->ray->dir_x > 0)
			return (EAST_TEX);
		else
			return (WEST_TEX);
	}
	if (params->ray->ray_axis == 'y')
	{
		if (params->ray->dir_y > 0)
			return (SOUTH_TEX);
		else
			return (NORTH_TEX);
	}
	return (0);
}

int	calculation_x(t_params *params, int dir)
{
	double	hit_offset;
	int		x_tex;

	x_tex = 0;
	hit_offset = 0.0;
	if (params->ray->ray_axis == 'y')
		hit_offset = fmod(params->ray->hit_x, CELL_SIZE) / CELL_SIZE;
	if (params->ray->ray_axis == 'x')
		hit_offset = fmod(params->ray->hit_y, CELL_SIZE) / CELL_SIZE;
	if (hit_offset < 0)
		hit_offset += 1.0;
	x_tex = (int)(hit_offset * params->tex_info[dir].width);
	return (x_tex);
}

char	*texture_pixel(double wall_height, int y)
{
	t_params	*params;
	int			y_tex;
	int			x_tex;
	int			dir;

	params = params_holder();
	dir = get_wall_dir(params);
	y_tex = ((y - ((WIN_HEIGHT / 2.0) - (wall_height / 2.0))) *
		params->tex_info[dir].height / wall_height);
	x_tex = calculation_x(params, dir);
	if (y_tex < 0)
		y_tex = 0;
	if (y_tex >= params->tex_info[dir].height)
		y_tex = params->tex_info[dir].height - 1;
	return (params->tex_info[dir].addr + (y_tex * params->tex_info[dir].line_len)
			+ (x_tex * (params->tex_info[dir].bpp / 8)));
}
