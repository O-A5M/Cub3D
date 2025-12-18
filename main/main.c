/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:42:24 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/12/11 15:48:18 by aelmsafe         ###   ########.fr       */
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

int	key_hook(int keycode, t_params *params)
{
	if (keycode == XK_Right)
	{
		draw_ceiling_and_floor(params);
		params->player->starting_angle
			= fmod((params->player->starting_angle + 360 + 10), 360);
		ray_caster(params);
	}
	else if (keycode == XK_Left)
	{
		draw_ceiling_and_floor(params);
		params->player->starting_angle
			= fmod((params->player->starting_angle + 360 - 10), 360);
		ray_caster(params);
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
	if (initiate_mlx(params, &mlx, &img)
		|| setup_player_and_ray(params))
		return (free_params(&params), 1);
	draw_ceiling_and_floor(params);
	ray_caster(params);
	mlx_key_hook(params->mlx->win_ptr, key_hook, params);
	mlx_loop(params->mlx->mlx_ptr);
	return (free_params(&params), 0);
}
