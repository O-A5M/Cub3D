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

int	main(int ac, char **av)
{
	t_params		*params;
	t_mlxdata		mlx;
	t_imgdata		img;
	t_playerdata	player;
	t_raydata		ray;

	if (!load_tex())
		printf("haha got you\n");
	params = params_holder();
	params_init(&params, &ray, &player);
	if ((ac != 2) || (ac == 2 && parse_args(av[1]) == -1))
		return (free_params(&params), 1);
	if (initiate_mlx(params, &mlx, &img)
		|| setup_player_and_ray(params))
		return (free_params(&params), 1);
	draw_ceiling_and_floor(params);
	ray_caster(params);
	return (free_params(&params), 0);
}
