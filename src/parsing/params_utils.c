/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:42:05 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/11/20 11:42:56 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_params	*params_holder(void)
{
	static t_params	*ret;

	if (ret == NULL)
		ret = malloc(sizeof(t_params));
	return (ret);
}

void	params_init(t_params **params)
{
	int	index;

	index = 0;
	(*params)->map = NULL;
	while (index < ALL_TEXTURES)
		(*params)->textures[index++] = NULL;
	index = 0;
	while (index < 3)
	{
		(*params)->ceiling_color[index] = -1;
		(*params)->floor_color[index] = -1;
		index++;
	}
	(*params)->player_posX = -1;
	(*params)->player_posY = -1;
}

void	free_params(t_params **params)
{
	int	index;

	index = 0;
	while (index < ALL_TEXTURES)
		free ((*params)->textures[index++]);
	index = 0;
	if ((*params)->map)
	{
		while ((*params)->map[index])
		{
			free ((*params)->map[index]);
			index++;
		}
		free((*params)->map);
	}
	free (*params);
}
