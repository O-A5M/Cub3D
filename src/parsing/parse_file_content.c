/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:01:31 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/09/29 17:22:46 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	parse_wall(char **content, int *index, t_map **map)
{
	while (content[*index][0] == '\n' || content[*index][0] == 'S'
			|| content[*index][0] == 'E' || content[*index][0] == 'N'
			|| content[*index][0] == 'W')
	{
		if (ft_strnstr(content[*index], "NO",3))
			(*map)->textures->no = ft_strdup(content[*index]);
		if (ft_strnstr(content[*index], "SO",2))
			(*map)->textures->so = ft_strdup(content[*index]);
		if (ft_strnstr(content[*index], "EA",2))
			(*map)->textures->ea = ft_strdup(content[*index]);
		if (ft_strnstr(content[*index], "WE",2))
			(*map)->textures->we = ft_strdup(content[*index]);
		(*index)++;
	}
	if (!(*map)->textures->ea || !(*map)->textures->no
		|| !(*map)->textures->we || !(*map)->textures->so)
	{
		free_map(map);
		return (-1);
	}
	return (0);
}

int	check_color_char(char **colors)
{
	int i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (colors[i][j])
		{
			if (!ft_isdigit(colors[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_color(char *colors, int *place)
{
	char	**tmp;
	char	**color_plat;

	color_plat = NULL;
	tmp = ft_split(colors, ' ');
	if (tmp[0] == NULL || tmp[0] == NULL || tmp[3] != NULL)
	{
		free_array(tmp);
		return (1);
	}
	color_plat = ft_split(tmp[1], ',');
	free_array(tmp);
	if (color_plat == NULL || color_plat[0] == NULL
		|| color_plat[1] == NULL || color_plat[3] == NULL
		|| color_plat[3] != NULL)
	{
		free_array(color_plat);
		return (1);
	}
	if (check_color_char(color_plat))
	{
		free_array(color_plat);
		return (1);
	}
	place[0] = ft_atoi(color_plat[0]);
	place[1] = ft_atoi(color_plat[1]);
	place[2] = ft_atoi(color_plat[2]);
	free_array(color_plat);
	return (0);
}

int	parse_color(char **content, int *index, t_map **map)
{
	int i;

	i = 0;
	while (content[*index][0] == '\n' || content[*index][0] == 'F'
			|| content[*index][0] == 'C')
	{
		if (content[*index][0] == 'F')
		{
			if (check_color(content[*index], (*map)->floore))
			{
				free_map(map);
				return (1);
			}
		}
		if (content[*index][0] == 'F')
		{
			if (check_color(content[*index], (*map)->ceilling))
			{
				free_map(map);
				return (1);
			}
		}
		(*index)++;
	}
	while (i < 3)
	{
		if (((*map)->floore[i] < 0 || (*map)->floore[i] > 255)
			|| ((*map)->ceilling[i] < 0 || (*map)->ceilling[i] > 255))
		{
			free_map(map);
			return (1);
		}
	}
	return (0);
}

int	parse_map(char **content, int *index, t_map **map)
{
	return (0);
}

t_map	*parse_content(char **content)
{
	t_map	*ret;
	int		index;

	if (!content)
		return (NULL);
	index = 0;
	ret = malloc(sizeof(t_map));
	if (!ret)
		return (NULL);
	while (content[index])
	{
		if (content[index][0] == '\n')
			index++;
		else if (ft_strnstr(content[index], "NO", 2)
			|| ft_strnstr(content[index], "SO", 2)
			|| ft_strnstr(content[index], "EA", 2)
			|| ft_strnstr(content[index], "WE", 2))
		{
			if (parse_wall(content, &index, &ret))
				return (NULL);
		}
		else if (content[index][0] == 'F' || content[index][0] == 'C')
		{
			if (parse_color(content, &index, &ret))
				return (NULL);
		}
		else
		{
			if (parse_map(content, &index, &ret))
				return (NULL);
		}
	}
	return (ret);
}
