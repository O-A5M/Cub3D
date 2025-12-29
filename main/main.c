/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:42:24 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/12/28 14:40:06 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*A function added by oakhmouc used to clear image before drawing again */
/*to avoid redrawing on top of another image */
void	clear_screen(t_params *params)
{
	int		x;
	int		y;
	char	*dst;

	x = -1;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			dst = params->img->img_add + (y * params->img->line_length)
				+ (x * (params->img->bpp / 8));
			*(unsigned int *)dst = 0X000000;
		}
	}
	mlx_put_image_to_window(params->mlx->mlx_ptr,
		params->mlx->win_ptr, params->img->img_ptr, 0, 0);
}

void	move_player(t_params *params, char direction)
{
	if (direction == 'a')
	{
		// params->player->pixel_y = ;
		// params->player->pixel_x = ;
	}
	else if (direction == 'd')
	{

	}
	else if (direction == 'w')
	{

	}
	else if (direction == 's')
	{

	}
	else
	{
		;
	}
	draw_ceiling_and_floor(params);
	ray_caster(params);
}

int	key_hook(int keycode, t_params *params)
{
	if (keycode == XK_Right)
	{
		params->player->starting_angle
			= fmod((params->player->starting_angle + 360 - 45), 360);
		printf("new angle: %f\n", params->player->starting_angle);
		draw_ceiling_and_floor(params);
		ray_caster(params);
		create_minimap(params);
		mlx_put_image_to_window(params->mlx->mlx_ptr, params->mlx->win_ptr,
			params->img->img_ptr, 0, 0);
	}
	else if (keycode == XK_Left)
	{
		params->player->starting_angle
			= fmod((params->player->starting_angle + 360 + 45), 360);
		printf("new angle: %f\n", params->player->starting_angle);
		draw_ceiling_and_floor(params);
		ray_caster(params);
		create_minimap(params);
		mlx_put_image_to_window(params->mlx->mlx_ptr, params->mlx->win_ptr,
			params->img->img_ptr, 0, 0);
	}
	// else if (keycode == XK_a || keycode == XK_A)
	// {
	// 	move_player(params, 'a');
	// }
	// else if (keycode == XK_d || keycode == XK_D)
	// {
	// 	move_player(params, 'd');
	// }
	// else if (keycode == XK_w || keycode == XK_W)
	// {
	// 	move_player(params, 'w');
	// }
	// else if (keycode == XK_s || keycode == XK_S)
	// {
	// 	move_player(params, 's');
	// }
	else
		return (1);
	return (0);
}

void	print_coords(t_params *params)
{
	printf("Map Height: %d | Map Width: %d\n", (int)params->map_height_2d, (int)params->map_width_2d);
	printf("Player position:\n");
	printf("pixel y: %d | pixel x: %d\n", (int)params->player->pixel_y, (int)params->player->pixel_x);
	printf("cell y: %d | cell x: %d\n", (int)params->player->cell_y, (int)params->player->cell_x);
	printf("Map:\n");
}

void	print_map(t_params *params)
{
	int	i;
	int	j;

	j = 0;
	while (params->map[j])
	{
		i = 0;
		while (params->map[j][i])
		{
			printf("%c, ", params->map[j][i]);
			i += 1;
		}
		printf("\n");
		j += 1;
	}
}

void	minimap_filler(t_imgdata *img, int line, int cell, int color)
{
	char	*dst;
	int		line_counter;
	int		cell_counter;

	line_counter = 0;
	while (line_counter < 4)
	{
		cell_counter = 0;
		while (cell_counter < 4)
		{
			dst = img->img_add
				+ ((4 * line + line_counter) * img->line_length)
				+ ((4 * cell + cell_counter) * (img->bpp / 8));
			*(unsigned int *)dst = color;
			cell_counter += 1;
		}
		line_counter += 1;
	}
}

int	draw_2d_map(t_params *params)
{
	int		line;
	int		cell;

	line = 0;
	while (params->map[line])
	{
		cell = 0;
		while (params->map[line][cell])
		{
			if (params->map[line][cell] == '0')
				minimap_filler(params->img, line, cell, 0x004a8eff);
			else if (params->map[line][cell] == '1')
				minimap_filler(params->img, line, cell, 0x002e3136);
			else if (params->map[line][cell] == 'E' || params->map[line][cell] == 'W'
				|| params->map[line][cell] == 'S' || params->map[line][cell] == 'N')
				minimap_filler(params->img, line, cell, 0x00FF0000);
			else
				minimap_filler(params->img, line, cell, 0x0013161c);
			cell += 1;
		}
		line += 1;
	}
	return (0);
}

int	create_minimap(t_params *params)
{
	draw_2d_map(params);
	// mlx_put_image_to_window(params->mlx->mlx_ptr, params->mlx->win_ptr,
	// 	params->img->img_ptr, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_params		*params;
	t_mlxdata		mlx;
	t_imgdata		img;
	t_playerdata	player;
	t_raydata		ray;

	params = params_holder();
	params_init(&params, &ray, &player);
	if ((ac != 2) || (ac == 2 && parse_args(av[1]) == -1))
		return (free_params(&params), 1);
	if (initiate_mlx(params, &mlx, &img) || calc_map_width_and_height(params)
		|| set_starting_angle(params) || set_pixel_coords(params))
		return (free_params(&params), 1);
	// print_coords(params);
	// print_map(params);
	if (load_textures() == -1)
		printf("Error\n");
	draw_ceiling_and_floor(params);
	ray_caster(params);
	create_minimap(params);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, img.img_ptr, 0, 0);
	mlx_key_hook(params->mlx->win_ptr, key_hook, params);
	mlx_loop(params->mlx->mlx_ptr);
	return (free_params(&params), 0);
}
