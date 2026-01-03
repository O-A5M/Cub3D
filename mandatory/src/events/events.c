/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 12:46:06 by oakhmouc          #+#    #+#             */
/*   Updated: 2026/01/02 12:46:06 by oakhmouc         ###   ########.fr       */
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

void	move_player(t_params *params, char direction)
{
	double	move_angle;
	double	new_y;
	double	new_x;

	if (direction == 'a')
		move_angle = params->player->starting_angle + 90;
	else if (direction == 'd')
		move_angle = params->player->starting_angle + 270;
	else if (direction == 'w')
		move_angle = params->player->starting_angle;
	else
		move_angle = params->player->starting_angle + 180;
	new_y = params->player->pos_y - 0.04 * sin(deg_to_rad(move_angle));
	new_x = params->player->pos_x + 0.04 * cos(deg_to_rad(move_angle));
	if (params->map[(int)new_y][(int)new_x] != '1'
		&& params->map[(int)new_y][(int)new_x] != ' ')
	{
		params->player->pos_y = new_y;
		params->player->pos_x = new_x;
		params->player->cell_y = (int)params->player->pos_y;
		params->player->cell_x = (int)params->player->pos_x;
	}
	return ;
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
	mlx_put_image_to_window(params->mlx->mlx_ptr, params->mlx->win_ptr,
		params->img->img_ptr, 0, 0);
	return (0);
}
