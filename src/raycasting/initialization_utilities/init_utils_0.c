/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:48:34 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/12/10 18:43:46 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../rayclude.h"
#include "include.h"

/* a func that sets up some necessary data at the beginning of the program */
int	initiate_mlx(t_params *params, t_mlxdata *mlx, t_imgdata *img)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (ft_putstr_fd("Issue Creating Connection!\n", 2), 1);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub0d");
	if (!mlx->win_ptr)
		return (ft_putstr_fd("Issue Creating Window!\n", 2), 1);
	img->img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!img->img_ptr)
		return (ft_putstr_fd("Issue Creating Image!\n", 2), 1);
	img->img_add = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_length, &img->endian);
	if (!img->img_add)
		return (ft_putstr_fd("Issue Retrieving Address!\n", 2), 1);
	params->mlx = mlx;
	params->img = img;
	return (0);
}

int	setup_player_and_ray(t_params *params)
{
	if (params->player->cell_x == -1 || params->player->cell_y == -1
		|| params->player->direction == 0)
		return (1);
	params->player->pixel_y = (int)(params->player->cell_y
			* ((double)WIN_HEIGHT / MAP_HEIGHT));
	params->player->pixel_x = (int)(params->player->cell_x
			* ((double)WIN_WIDTH / MAP_WIDTH));
	if (params->player->direction == 'E')
		params->player->starting_angle = 0;
	else if (params->player->direction == 'N')
		params->player->starting_angle = 90;
	else if (params->player->direction == 'W')
		params->player->starting_angle = 180;
	else
		params->player->starting_angle = 270;
	return (0);
}
