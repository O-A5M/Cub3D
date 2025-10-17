/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:01:31 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/10/17 15:04:40 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include "libft.h"

int	check_color_plat(char **content, int *index, t_map **map, char type)
{
	int		i;
	int		j;
	char	**tmp;
	int		tmp_color;

	i = 0;
	j = 0;
	tmp_color = -1;
	tmp = split_colors(content[*index]);
	if (!tmp)
		return (1);
	while (tmp[i] && i < 3)
	{
		j = 0;
		while (tmp[i][j])
		{
			if (!ft_isdigit(tmp[i][j]) && tmp[i][j] != '\n')
				return (free_array(tmp), 1);
			j++;
		}
		tmp_color = ft_atoi(tmp[i]);
		if (insert_color(tmp_color, map, type, i))
			return (free_array(tmp), 1);
		i++;
	}
	return (free_array(tmp), 0);
}

int	parse_color(char **content, int *index, t_map **map)
{
	int	flag;

	flag = 0;
	while (flag < 2 && *index >= 0)
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
			if (!check_color_plat(content, index, map, 'C'))
				flag++;
			else
				return (1);
		}
		(*index)--;
	}
	if (flag != 2)
		return (printf("Error in the Ceilling or floor colors\n"), 1);
	return (0);
}

int	parse_wall_tex(char **content, int *index, t_map **map)
{
	int		flag;

	flag = 0;
	while (flag < 4 && *index >= 0)
	{
		insert_tex_name(content[*index], &flag, map);
		(*index)--;
	}
	if (!(*map)->textures->no || !(*map)->textures->so
		|| !(*map)->textures->ea || !(*map)->textures->we)
	{
		printf("empty textures\n");
		return (1);
	}
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
		(*index)--;
	}
	return (0);
}

int	check_map_pos(char **content, int index)
{
	int	i;

	i = index - 2;
	while (i >= 0)
	{
		while (content[i] && content[i][0] == '\n')
			i--;
		if (content[i][0] != ' ' && content[i][0] != '0'
			&& content[i][0] != '1')
			return (1);
		else
			return (0);
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
	if (check_map_pos(content, (int)len))
		return (free_map(map), NULL);
	if (parse_map(content, &index, &map))
		return (free_map(map), NULL);
	if (parse_wall_color(content, &index, &map))
		return (free_map(map), NULL);
	return (map);
}
