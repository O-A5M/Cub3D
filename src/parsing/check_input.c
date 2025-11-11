/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:47:48 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/11/11 07:07:45 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	check_xpm_exist(t_map *map)
{
	int	fd;

	fd = open(map->textures->no, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	fd = open(map->textures->ea, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	fd = open(map->textures->so, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	fd = open(map->textures->we, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	return (0);
}

int	is_player_valid(t_map **map)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = -1;
	while ((*map)->map->array[i])
	{
		j = 0;
		while ((*map)->map->array[i][j])
		{
			if ((*map)->map->array[i][j] == 'S'
				|| (*map)->map->array[i][j] == 'W'
				|| (*map)->map->array[i][j] == 'N'
				|| (*map)->map->array[i][j] == 'E')
			{
				if (flag == -1)
				{
					(*map)->player_pos[0] = i;
					(*map)->player_pos[1] = j;
					flag = 0;
				}
				else if (flag != -1)
					return (-1);
			}
			j++;
		}
		i++;
	}
	if (flag == -1)
		return (-1);
	return (0);
}

int	is_map_closed(char **map, int row, int col);

int	is_map_valide(t_map *map)
{
	if (is_player_valid(&map) == -1)
		return (-1);
	if (is_map_closed(map->map->array, map->player_pos[0], map->player_pos[1]) == -1)
		return (-1);
	return (0);
}

int	check_input_struct(t_map *map)
{
	// if (check_xpm_exist(map) == -1)
	// {
	// 	printf("Error in the textures files.\n");
	// 	return (-1);
	// }
	if (is_map_valide(map))
	{
		printf("Invalide map!\n");
		return (-1);
	}
	return (0);
}
