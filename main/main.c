/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:42:24 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/12/23 06:44:53 by oakhmouc         ###   ########.fr       */
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
		draw_ceiling_and_floor(params);
		params->player->starting_angle
			= fmod((params->player->starting_angle + 360 + 45), 360);
		ray_caster(params);
	}
	else if (keycode == XK_Left)
	{
		draw_ceiling_and_floor(params);
		params->player->starting_angle
			= fmod((params->player->starting_angle + 360 - 45), 360);
		ray_caster(params);
	}
	else if (keycode == XK_a || keycode == XK_A)
	{
		move_player(params, 'a');
	}
	else if (keycode == XK_d || keycode == XK_D)
	{
		move_player(params, 'd');
	}
	else if (keycode == XK_w || keycode == XK_W)
	{
		move_player(params, 'w');
	}
	else if (keycode == XK_s || keycode == XK_S)
	{
		move_player(params, 's');
	}
	else
		return (1);
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
	printf("Map Height: %d | Map Width: %d\n", params->map_height_2d, params->map_width_2d);
	printf("Player position:\n");
	printf("pixel y: %d | pixel x: %d\n", params->player->pixel_y, params->player->pixel_x);
	printf("cell y: %d | cell x: %d\n", params->player->cell_y, params->player->cell_x);
	// if (load_textures() == -1)
	// 	printf("No way\n");
	draw_ceiling_and_floor(params);
	ray_caster(params);
	mlx_key_hook(params->mlx->win_ptr, key_hook, params);
	mlx_loop(params->mlx->mlx_ptr);
	return (free_params(&params), 0);
}
