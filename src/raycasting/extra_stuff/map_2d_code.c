/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 17:05:34 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/11/27 11:36:21 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rayclude.h"

/* a func that colors a given cell in the map, with a given a color */
void	color_cell(t_data *data, int cell_x, int cell_y)
{
	char	*dst;
	int		px;
	int		py;

	py = cell_y * CELL_HEIGHT;
	while (py < (cell_y + 1) * CELL_HEIGHT)
	{
		px = cell_x * CELL_WIDTH;
		while (px < (cell_x + 1) * CELL_WIDTH)
		{
			dst = data->img->img_add + (py * data->img->line_length)
				+ (px * (data->img->bpp / 8));
			*(unsigned int *)dst = 0x00FF00F0;
			px++;
		}
		py++;
	}
	return ;
}

/* a func that draws a line, given its starting point, direction, and color */
void	draw_a_line(t_data *data)
{
	int		counter;
	int		line_length;

	line_length = 8;
	counter = 0;
	while (counter++ <= line_length
		&& data->player->pixel_x > 0 && data->player->pixel_x < WIN_WIDTH
		&& data->player->pixel_y > 0 && data->player->pixel_y < WIN_HEIGHT)
	{
		*(unsigned int *)dst = 0x00F0F0CC;
		(void)((data->player->direction == 'N')
			&& (dst -= (data->img->line_length)));
		(void)((data->player->direction == 'S')
			&& (dst += (data->img->line_length)));
		(void)((data->player->direction == 'E')
			&& (dst += (data->img->bpp / 8)));
		(void)((data->player->direction == 'W')
			&& (dst -= (data->img->bpp / 8)));
	}
	if (counter <= 8)
		write(1, "Direction Arrow is Out of Bounds!\n", 34);
	return ;
}

/* a func that draws a player's direction vector given its starting point,
its direction (N, S, E, W), and the color */
void	draw_direction_vector(t_data *data)
{
	char	*dst;

	if (direction == 'N')
		py = py - 3;
	else if (direction == 'S')
		py = py + 3;
	else if (direction == 'E')
		px = px + 3;
	else if (direction == 'W')
		px = px - 3;
	dst = img->img_add + px * (img->bpp / 8) + py * img->line_length;
	draw_a_line(data, dst);
}

/* a func that draws a small square representing the player,
given its cell's coordinates on the map, its color and its direction */
void	draw_player(t_data *data, int cell_x, int cell_y)
{
	char	*dst;
	int		x;
	int		y;
	int		counter_x;
	int		counter_y;

	data->player->pixel_y = (cell_y * CELL_HEIGHT) + (CELL_HEIGHT / 2) - 2;
	y = data->player->pixel_y;
	counter_y = 0;
	while (counter_y < 5)
	{
		data->player->pixel_x = (cell_x * CELL_WIDTH) + (CELL_WIDTH / 2) - 2;
		x = data->player->pixel_x;
		counter_x = 0;
		while (counter_x < 5)
		{
			dst = data->img->img_add + data->player->pixel_y * data->img->line_length
				+ data->player->pixel_x * (data->img->bpp / 8);
			*(unsigned int *)dst = 0x00FF0000;
			x++;
			counter_x++;
		}
		y++;
		counter_y++;
	}
	draw_direction_vector(data);
	return ;
}
