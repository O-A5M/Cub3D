/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_elements_textures.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:42:32 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/12/28 14:39:12 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include <stddef.h>

static int	split_tex(char *type, char *path)
{
	t_params	*param;
	size_t		size;

	size = ft_strlen(path) - 1;
	param = params_holder();
	if (type[0] == 'N' && type[1] == 'O')
		param->textures[NORTH_TEX] = ft_substr(path, 0, size);
	else if (type[0] == 'S' && type[1] == 'O')
		param->textures[SOUTH_TEX] = ft_substr(path, 0, size);
	else if (type[0] == 'W' && type[1] == 'E')
		param->textures[WEST_TEX] = ft_substr(path, 0, size);
	else if (type[0] == 'E' && type[1] == 'A')
		param->textures[EAST_TEX] = ft_substr(path, 0, size);
	return (0);
}

static int	manage_tex(char ***tmp, t_lines *file_content)
{
	(*tmp) = ft_split(file_content->line, ' ');
	if (!(*tmp) || !(*tmp)[0] || !(*tmp)[1] || (*tmp)[2])
		return (perror("cub3D"), -1);
	if (ft_strlen((*tmp)[0]) != 2)
		return (-1);
	if (split_tex((*tmp)[0], (*tmp)[1]) == -1)
		return (-1);
	return (0);
}

int	add_tex(t_lines *file_content)
{
	char	**tmp;

	if (!file_content)
		return (-1);
	while (file_content
		&& ((file_content->line[0] == 'N' && file_content->line[1] == 'O')
			|| (file_content->line[0] == 'S' && file_content->line[1] == 'O')
			|| (file_content->line[0] == 'W' && file_content->line[1] == 'E')
			|| (file_content->line[0] == 'E' && file_content->line[1] == 'A')
			|| file_content->line[0] == '\n'))
	{
		if (file_content->line[0] != '\n')
		{
			if (manage_tex(&tmp, file_content) == -1)
				return (free_array(&tmp), -1);
			free_array(&tmp);
		}
		file_content = file_content->next;
	}
	if (params_holder()->floor_color[0] == -1)
		return (free_array(&tmp), add_color(file_content));
	return (free_array(&tmp), add_map(file_content));
}
