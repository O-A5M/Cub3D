/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 12:45:54 by oakhmouc          #+#    #+#             */
/*   Updated: 2026/01/02 12:45:54 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	minimap_filler(t_imgdata *img, int line, int cell, int color)
{
	char	*dst;
	int		line_counter;
	int		cell_counter;

	line_counter = 0;
	while (line_counter < CELL_SIZE * 10)
	{
		cell_counter = 0;
		while (cell_counter < CELL_SIZE * 10)
		{
			dst = img->img_add
				+ ((8 * line + line_counter) * img->line_length)
				+ ((8 * cell + cell_counter) * (img->bpp / 8));
			*(unsigned int *)dst = color;
			cell_counter += 1;
		}
		line_counter += 1;
	}
}

void	set_map_color(int pixel_x, int pixel_y, int map_x, int map_y)
{
	char		tile;
	t_params	*params;

	params = params_holder();
	tile = params->map[map_y][map_x];
	if (tile == '0' || tile == 'E' || tile == 'W'
		|| tile == 'N' || tile == 'S')
		minimap_filler(params->img, pixel_x, pixel_y, 0x4a8eff);
	else if (tile == '1')
		minimap_filler(params->img, pixel_x, pixel_y, 0x2e3136);
	else
		minimap_filler(params->img, pixel_x, pixel_y, 0x13161c);
}

int	draw_2d_map(t_params *params)
{
	int	pixel_y;
	int	pixel_x;
	int	map_y;
	int	map_x;

	pixel_y = -1;
	while (++pixel_y < 16)
	{
		map_y = params->player->cell_y + (pixel_y - 8);
		pixel_x = -1;
		while (++pixel_x < 16)
		{
			map_x = params->player->cell_x + (pixel_x - 8);
			if (map_y >= 0 && map_y < params->map_height_2d
				&& map_x >= 0 && map_x < params->map_width_2d
				&& params->map[map_y][map_x] != '\0')
				set_map_color(pixel_x, pixel_y, map_x, map_y);
			else
				minimap_filler(params->img, pixel_x, pixel_y, 0x000000);
		}
	}
	minimap_filler(params->img, 8, 8, 0xFF0000);
	return (0);
}

int	create_minimap(t_params *params)
{
	draw_2d_map(params);
	return (0);
}
