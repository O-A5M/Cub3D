/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:01:31 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/10/14 16:59:10 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	parse_map(char **content, int *index, t_map **map)
{
	int	i;

	while (content[*index] && content[*index][0] == '\n')
		(*index)--;
	while (content[*index] && content[*index][0] != '\n'
			&& content[*index][0] != 'F' && content[*index][0] != 'C'
			&& content[*index][0] != 'N' && content[*index][0] != 'S'
			&& content[*index][0] != 'E' && content[*index][0] != 'W')
	{
		i = 0;
		while (content[*index][i++])
		{
			if (content[*index][i] != '1' && content[*index][i] != '0'
				&& content[*index][i] != 'N' && content[*index][i] != 'S'
				&& content[*index][i] != 'E' && content[*index][i] != 'W'
				&& content[*index][i] != ' ')
				return (1);
		}
		da_append(&(*map)->map, content[*index]);
		(*index)--;
	}
	return (0);
}

int	check_color_plat(char **content, int *index, t_map **map, char type)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	tmp = NULL;
	while (content[*index][i])
	{
		while (content[*index][i] && !ft_isdigit(content[*index][i]))
			i++;
		if (content[*index][i] && ft_isdigit(content[*index][i]))
		{
			tmp = ft_split(content[*index] + i, ',');
			if (!tmp)
				return (1);
		}
	}
	i = 0;
	while (tmp[i] && i < 3)
	{
		if (tmp[i] == NULL)
		{
			free_array(tmp);
			return (1);
		}
		j = 0;
		while (tmp[i][j])
		{
			if (!ft_isdigit(tmp[i][j]))
			{
				free_array(tmp);
				return (1);
			}
			j++;
		}
		if (type == 'F')
		{
			(*map)->floore[i] = ft_atoi(tmp[i]);
			if ((*map)->floore[i] > 255 || (*map)->floore[i] < 0)
			{
				free_array(tmp);
				return (1);
			}
		}
		if (type == 'C')
		{
			(*map)->ceilling[i] = ft_atoi(tmp[i]);
			if ((*map)->ceilling[i] > 255 || (*map)->ceilling[i] < 0)
			{
				free_array(tmp);
				return (1);
			}
		}
		i++;
	}
	free_array(tmp);
	return (0);
}

int	parse_color(char **content, int *index, t_map **map)
{
	int	flag;

	flag = 0;
	while (flag != 2)
	{
		if (content[*index][0] == 'F')
		{
			if (!check_color_plat(content, index, map, 'F'))
	  			flag++;
			else
				return (1);
	  	}
		else if (content[*index][0] == 'C')
		{
			if (!check_color_plat(content, index, map, 'F'))
	  			flag++;
			else
				return (1);
		}
		(*index)--;
	}
	return (0);
}

int	parse_wall_tex(char **content, int *index, t_map **map)
{
	int		flag;
	char	*tmp;

	flag = 0;
	tmp = NULL;
	while (flag < 4)
	{
		if (content[*index] && content[*index][0] != '\n')
			tmp = ft_substr(content[*index], 3, sizeof(content[*index]) - 3);
		if (tmp && content[*index][0] == 'N' && content[*index][0] == 'O')
		{
			(*map)->textures->no = ft_strdup(tmp);
			flag++;
		}
		if (tmp && content[*index][0] == 'S' && content[*index][0] == 'O')
		{
			(*map)->textures->so = ft_strdup(tmp);
			flag++;
		}
		if (tmp && content[*index][0] == 'E' && content[*index][0] == 'A')
		{
			(*map)->textures->ea = ft_strdup(tmp);
			flag++;
		}
		if (tmp && content[*index][0] == 'W' && content[*index][0] == 'E')
		{
			(*map)->textures->we = ft_strdup(tmp);
			flag++;
		}
		free(tmp);
		tmp = NULL;
		(*index)--;
	}
	if (!(*map)->textures->no || !(*map)->textures->so
		|| !(*map)->textures->ea || !(*map)->textures->we)
		return (1);
	return (0);
}

int	parse_wall_color(char **content, int *index, t_map **map)
{
	while (*index >= 0)
	{
		while (*index >= 0 && content[*index][0] == '\n')
			(*index)--;
		if (*index >= 0
			&& (content[*index][0] == 'F' || content[*index][0] == 'C'))
		{
			if (parse_color(content, index, map))
				return (1);
		}
		if (*index >= 0
			&& (content[*index][0] == 'S' || content[*index][0] == 'N'
			|| content[*index][0] == 'E' || content[*index][0] == 'W'))
		{
			if (parse_wall_tex(content, index, map))
				return (1);
		}
	}
	return (0);
}

t_map	*parse_content(char **content, size_t len)
{
	t_map	*map;
	int		index;

	index = len - 1;
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	init_map(&map);
	if (parse_map(content, &index, &map))
	{
		free_map(map);
		return (NULL);
	}
	if (parse_wall_color(content, &index, &map))
	{
		free_map(map);
		return (NULL);
	}
	return (map);
}
