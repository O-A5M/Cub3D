/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 04:56:04 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/12/23 06:40:08 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include "rayclude.h"

int	load_textures(void)
{
	int			index;
	t_params	*param;

	index = -1;
	param = params_holder();
	while(++index < 4)
	{
		param->tex_info[index].addr = mlx_xpm_file_to_image(
			param->mlx->win_ptr,
			param->textures[index],
			&param->tex_info->width,
			&param->tex_info->height);
		if (!param->tex_info[index].addr)
			return (perror("cub3D"), -1);
	}
	return (0);
}
