/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:42:24 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/12/10 18:28:31 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	main(int ac, char **av)
{
	t_params		*param;
	t_mlxdata		mlx;
	t_imgdata		img;
	t_playerdata	player;
	t_raydata		ray;

	param = params_holder();
	params_init(&param);
	// much shorter than before, in case we need some space.
	if ((ac != 2) || (ac == 2 && parse_args(av[1]) == -1))
		return (free_params(&param), 1);
	if (initiate_mlx(params, &mlx, &img) || initiate_player_and_ray(params, &player, &ray))
		return (free_params(&param), 1);
	render(params);
	return (free_params(&param), 0);
}
