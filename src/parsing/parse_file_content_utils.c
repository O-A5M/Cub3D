/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_content_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:47:23 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/10/17 13:35:46 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	check_invalid_character(char c)
{
	if (c != '1' && c != '0'
		&& c != 'N' && c != 'S'
		&& c != 'E' && c != 'W'
		&& c != ' ' && c != '\n')
	{
		printf("%d invalide character in map.\n", c);
		return (1);
	}
	return (0);
}

int	parse_map(char **content, int *index, t_map **map)
{
	int	i;

	i = 0;
	while (content[*index] && content[*index][0] == '\n')
		(*index)--;
	while (content[*index] && content[*index][0] != '\n'
			/*&& content[*index][0] != 'F' && content[*index][0] != 'C'
			&& content[*index][0] != 'N' && content[*index][0] != 'S'
			&& content[*index][0] != 'E' && content[*index][0] != 'W'*/
			&& content[*index][0] != '\0')
	{
		i = 0;
		while (content[*index][i] != '\0')
		{
			if (check_invalid_character(content[*index][i]))
				return (1);
			i++;
		}
		da_append(&(*map)->map, content[*index]);
		(*index)--;
	}
	return (0);
}

void	insert_tex_name(char *content, int *flag, t_map **map)
{
	char	*tmp;

	tmp = ft_substr(content, 3, ft_strlen(content) - 3);
	if (tmp && content[0] == 'N' && content[1] == 'O' && tmp[0] != '\n')
	{
		(*map)->textures->no = ft_strdup(tmp);
		flag++;
	}
	if (tmp && content[0] == 'S' && content[1] == 'O' && tmp[0] != '\n')
	{
		(*map)->textures->so = ft_strdup(tmp);
		flag++;
	}
	if (tmp && content[0] == 'E' && content[1] == 'A' && tmp[0] != '\n')
	{
		(*map)->textures->ea = ft_strdup(tmp);
		flag++;
	}
	if (tmp && content[0] == 'W' && content[1] == 'E' && tmp[0] != '\n')
	{
		(*map)->textures->we = ft_strdup(tmp);
		flag++;
	}
	free(tmp);
}

char	**split_colors(char *content)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	while (content[i])
	{
		while (content[i] && !ft_isdigit(content[i]))
			i++;
		if (content[i] && ft_isdigit(content[i]))
		{
			tmp = ft_split(content + i, ',');
			if (!tmp)
				return (NULL);
			else
				break ;
		}
	}
	return (tmp);
}

int	insert_color(int color, t_map **map, char type, int index)
{
	if (color < 0 || color > 255)
		return (1);
	if (type == 'F')
		(*map)->floore[index] = color;
	else
		(*map)->floore[index] = color;
	return (0);
}
