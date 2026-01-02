/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 04:56:04 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/12/28 15:25:07 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include "mlx.h"
#include "rayclude.h"

int	load_textures(void)
{
	int			index;
	t_params	*param;

	index = -1;
	param = params_holder();
	while (++index < 4)
	{
		param->tex_info[index].img = mlx_xpm_file_to_image(
				param->mlx->mlx_ptr,
				param->textures[index],
				&param->tex_info[index].width,
				&param->tex_info[index].height);
		if (!param->tex_info[index].img)
			return (perror("cub3D"), -1);
		param->tex_info[index].addr = mlx_get_data_addr
			(param->tex_info[index].img,
				&param->tex_info[index].bpp,
				&param->tex_info[index].line_len,
				&param->tex_info[index].endian);
		if (!param->tex_info[index].addr)
			return (perror("cub3D 2"), -1);
	}
	return (0);
}
