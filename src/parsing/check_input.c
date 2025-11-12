/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:47:48 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/11/12 11:57:10 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include <stddef.h>

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

void	add_spaces(char **str, int longest)
{
	char	tmp[longest + 1];
	int		index;

	index = 0;
	while ((*str)[index])
	{
		tmp[index] = (*str)[index];
		index++;
	}
	while (index < longest)
	{
		tmp[index] = '7';
		index++;
	}
	tmp[index] = '\0';
	free((*str));
	(*str) = ft_strdup(tmp);
}

int	complete_the_map(char **map, int count)
{
	int		len;
	size_t	longest;

	len = 0;
	longest = 0;
	while (len < count - 3)
	{
		if (longest < ft_strlen(map[len]))
			longest = ft_strlen(map[len]);
		len++;
	}
	len = 0;
	while (len < count - 3)
	{
		if (ft_strlen(map[len]) < longest)
			add_spaces(&map[len], longest);
		len++;
	}
	return (longest);
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

int	is_map_closed(char **map, int row, int col, int	count)
{
	// int	longest;

	(void)row;
	(void)col;
	complete_the_map(map, count);
	return (0);
}

int	is_map_valide(t_map *map)
{
	if (is_player_valid(&map) == -1)
		return (-1);
	if (is_map_closed(map->map->array, map->player_pos[0], map->player_pos[1], map->map->count) == -1)
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
