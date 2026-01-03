/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 12:46:00 by oakhmouc          #+#    #+#             */
/*   Updated: 2026/01/02 12:46:00 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	mouse_move(int x, int y, t_params *params)
{
	static int	old_x;
	double		dx;

	(void)y;
	dx = old_x - x;
	old_x = x;
	if (dx != 0 && x % 3 == 0)
	{
		params->player->starting_angle
			= fmod(params->player->starting_angle + dx
				* 0.5 + 360.0, 360.0);
	}
	return (0);
}

void	hooks(t_params *params)
{
	mlx_hook(params->mlx->win_ptr, 2, 1L << 0, key_press, params);
	mlx_hook(params->mlx->win_ptr, 3, 1L << 1, key_release, params);
	mlx_hook(params->mlx->win_ptr, 17, 0, exit_and_clear, params->mlx->mlx_ptr);
	mlx_hook(params->mlx->win_ptr, 6, 1L << 6, mouse_move, params);
	mlx_loop_hook(params->mlx->mlx_ptr, move_loop, params);
}
