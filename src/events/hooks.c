/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 12:46:11 by oakhmouc          #+#    #+#             */
/*   Updated: 2026/01/02 12:46:12 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	hooks(t_params *params)
{
	mlx_hook(params->mlx->win_ptr, 2, 1L << 0, key_press, params);
	mlx_hook(params->mlx->win_ptr, 3, 1L << 1, key_release, params);
	mlx_hook(params->mlx->win_ptr, 17, 0, exit_and_clear, params->mlx->mlx_ptr);
	mlx_loop_hook(params->mlx->mlx_ptr, move_loop, params);
}
