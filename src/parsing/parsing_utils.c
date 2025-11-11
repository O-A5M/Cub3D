/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:08:52 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/11/11 01:27:16 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include "libft.h"

void	free_textures(t_textures **tex)
{
	free((*tex)->so);
	free((*tex)->no);
	free((*tex)->ea);
	free((*tex)->we);
	free((*tex));
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	da_free(map->map);
	if (map->textures)
		free_textures(&map->textures);
	free(map);
}

void	init_map(t_map **map)
{
	da_init(&(*map)->map, 1);
	ft_memset((*map)->floore, -1, sizeof((*map)->floore));
	ft_memset((*map)->ceilling, -1, sizeof((*map)->ceilling));
	ft_memset((*map)->player_pos, -1, sizeof((*map)->player_pos));
	(*map)->textures = malloc(sizeof(t_textures));
	(*map)->textures->ea = NULL;
	(*map)->textures->no = NULL;
	(*map)->textures->so = NULL;
	(*map)->textures->we = NULL;
}
