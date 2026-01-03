/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 12:46:06 by oakhmouc          #+#    #+#             */
/*   Updated: 2026/01/03 09:08:32 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	exit_and_clear(void)
{
	t_params	*params;

	params = params_holder();
	free_params(&params);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_params *params)
{
	if (keycode == XK_Right)
	{
		params->player->starting_angle
			= fmod((params->player->starting_angle + 360 - 10), 360);
	}
	else if (keycode == XK_Left)
	{
		params->player->starting_angle
			= fmod((params->player->starting_angle + 360 + 10), 360);
	}
	else if (keycode == XK_a || keycode == XK_A)
		params->player_move = 'a';
	else if (keycode == XK_d || keycode == XK_D)
		params->player_move = 'd';
	else if (keycode == XK_w || keycode == XK_W)
		params->player_move = 'w';
	else if (keycode == XK_s || keycode == XK_S)
		params->player_move = 's';
	else if (keycode == XK_Escape)
		exit_and_clear();
	return (0);
}

int	key_release(int keycode, t_params *params)
{
	(void)keycode;
	params->player_move = 0;
	return (0);
}

int	move_loop(t_params *params)
{
	if (params->player_move == 'a')
		move_player(params, 'a');
	else if (params->player_move == 'd')
		move_player(params, 'd');
	else if (params->player_move == 'w')
		move_player(params, 'w');
	else if (params->player_move == 's')
		move_player(params, 's');
	draw_ceiling_and_floor(params);
	ray_caster(params);
	create_minimap(params);
	mlx_put_image_to_window(params->mlx->mlx_ptr, params->mlx->win_ptr,
		params->img->img_ptr, 0, 0);
	return (0);
}
