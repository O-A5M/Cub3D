/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:41:25 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/11/28 22:51:55 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static char	**copy_and_replace(void);

int	check_map_elements(void)
{
	int			i;
	int			j;
	t_params	*param;

	i = -1;
	param = params_holder();
	while (param->map[++i])
	{
		j = -1;
		while (param->map[i][++j])
		{
			if (param->player_posX == -1 && param->player_posY == -1
				&& (param->map[i][j] == 'S' || param->map[i][j] == 'N'
				|| param->map[i][j] == 'E' || param->map[i][j] == 'W'))
			{
				param->player_posY = i;
				param->player_posX = j;
				continue ;
			}
			if (param->map[i][j] != '0' && param->map[i][j] != '1'
			&& param->map[i][j] != ' ' && param->map[i][j] != '\n')
				return (-1);
		}
	}
	return (0);
}

static int	check_is_map_open(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0' && (i == 0 || j == 0
			|| !map[i + 1] || !map[i][j + 1]
			|| map[i][j + 1] == ' ' || map[i][j - 1] == ' '
			|| map[i + 1][j] == ' ' || map[i - 1][j] == ' '))
				return (-1);
		}
	}
	return (0);
}

int	is_map_surrounded(void)
{
	char	**map;

	map = copy_and_replace();
	if (check_is_map_open(map) == -1)
		return (free_array(&map), -1);
	return (free_array(&map), 0);
}

static char	*replace_space(char *str, int longest)
{
	char	*ret;
	int		index;

	index = -1;
	ret = malloc(sizeof(char) * longest);
	if (!ret)
		return (NULL);
	while (str[++index] != '\n')
		ret[index] = str[index];
	while (index < longest - 1)
		ret[index++] = ' ';
	ret[index] = '\0';
	return (ret);
}

static char	**copy_and_replace(void)
{
	t_params	*param;
	int			index;
	int			longest;
	char		**ret;

	index = -1;
	longest = 0;
	param = params_holder();
	while (param->map[++index])
	{
		if ((size_t)longest < ft_strlen(param->map[index]))
			longest = ft_strlen(param->map[index]);
	}
	ret = malloc((index + 1) * sizeof(char *));
	if (!ret)
		return (perror("cub3D"), NULL);
	index = -1;
	while (param->map[++index])
		ret[index] = replace_space(param->map[index], longest);
	ret[index] = NULL;
	return (ret);
}
