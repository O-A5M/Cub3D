/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:42:24 by aelmsafe          #+#    #+#             */
/*   Updated: 2026/01/02 10:54:13 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include "mlx.h"
#include "rayclude.h"

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
		|| set_starting_angle(params) || set_pixel_coords(params)
		|| load_textures() == -1)
		return (free_params(&params), 1);
	draw_ceiling_and_floor(params);
	ray_caster(params);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, img.img_ptr, 0, 0);
	hooks(params);
	mlx_loop(params->mlx->mlx_ptr);
	return (free_params(&params), 0);
}
