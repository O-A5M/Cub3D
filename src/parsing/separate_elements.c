#include "include.h"

int	split_color(char *type, char *colors)
{
	char		**tmp;
	t_params	*param;
	int			index;

	index = 0;
	param = params_holder();
	tmp = ft_split(colors, ',');
	if (!tmp)
		return (perror("cub3D"), -1);
	if (!tmp[0] || !tmp[1] || !tmp[2] || tmp[3])
		return (free_array(&tmp), -1);
	if (type[0] == 'F')
	{
		while (index < 3)
		{
			param->floor_color[index] = ft_atoi(tmp[index]);
			index++;
		}
	}
	if (type[0] == 'C')
	{
		while (index < 3)
		{
			param->ceiling_color[index] = ft_atoi(tmp[index]);
			index++;
		}
	}
	return (free_array(&tmp), 0);
}

int	add_color(t_lines *file_content)
{
	char		**tmp;

	while (file_content->line[0] == 'F' || file_content->line[0] == 'C'
			|| file_content->line[0] == '\n')
	{
		if (file_content->line[0] == 'F' || file_content->line[0] == 'C')
		{
			tmp = ft_split(file_content->line, ' ');
			if (!tmp)
				return (perror("cub3D"), -1);
			if (!tmp[0] || !tmp[1] || tmp[2])
				return (free_array(&tmp), -1);
			if (ft_strlen(tmp[0]) != 1)
				return (free_array(&tmp), -1);
			if (split_color(tmp[0], tmp[1]) == -1)
				return (free_array(&tmp), -1);
		}
		file_content = file_content->next;
	}
	if (!params_holder()->textures[NORTH_TEX])
		return (free_array(&tmp), add_tex(file_content));
	return (free_array(&tmp), add_map(file_content));
}

int	split_tex(char *type, char *path)
{
	t_params	*param;

	param = params_holder();
	if (type[0] == 'N' && type[1] == 'O')
		param->textures[NORTH_TEX] = ft_strdup(path);
	else if (type[0] == 'S' && type[1] == 'O')
		param->textures[SOUTH_TEX] = ft_strdup(path);
	else if (type[0] == 'W' && type[1] == 'E')
		param->textures[WEST_TEX] = ft_strdup(path);
	else if (type[0] == 'E' && type[1] == 'A')
		param->textures[EAST_TEX] = ft_strdup(path);
	return (0);
}

int	add_tex(t_lines *file_content)
{
	char	**tmp;

	while ((file_content->line[0] == 'N' && file_content->line[1] == 'O')
		|| (file_content->line[0] == 'S' && file_content->line[1] == 'O')
		|| (file_content->line[0] == 'W' && file_content->line[1] == 'E')
		|| (file_content->line[0] == 'E' && file_content->line[1] == 'A')
		|| file_content->line[0] == '\n')
	{
		if (file_content->line[0] != '\n')
		{
			tmp = ft_split(file_content->line, ' ');
			if (!tmp || !tmp[0] || !tmp[1] || tmp[2])
				return (free_array(&tmp), perror("cub3D"), -1);
			if (ft_strlen(tmp[0]) != 2)
				return (free_array(&tmp), -1);
			if (split_tex(tmp[0], tmp[1]) == -1)
				return (free_array(&tmp), -1);
		}
		file_content = file_content->next;
	}
	if (params_holder()->floor_color[0] == -1)
		return (free_array(&tmp), add_color(file_content));
	return (free_array(&tmp), add_map(file_content));
}

int	split_map(t_lines *file_content, size_t len)
{
	t_params	*param;
	size_t		index;

	index = 0;
	param = params_holder();
	param->map = malloc(sizeof(char *) * (len + 1));
	if (!param->map)
		return (perror("cub3D"), -1);
	while (index < len)
	{
		param->map[index] = ft_strdup(file_content->line);
		index++;
		file_content = file_content->next;
	}
	param->map[index] = NULL;
	return (0);
}

int	add_map(t_lines *file_content_i)
{
	size_t	len;
	t_lines	*file_content;

	len = 0;
	file_content = file_content_i;
	while (file_content->line[0] == '0' || file_content->line[0] == '1'
			|| file_content->line[0] == ' ' || file_content->line[0] == '\n')
	{
		if (file_content->line[0] != '\n')
			len++;
		else
		{
			while (file_content && file_content->line)
			{
				if (file_content->line[0] != '\n')
					return (-1);
				file_content = file_content->next;
			}
		}
		file_content = file_content->next;
		if (!file_content)
			break ;
	}
	return (split_map(file_content_i, len));
}

static int	separate_tex_color(t_lines *file_content)
{
	if ((file_content->line[0] == 'N' && file_content->line[1] == 'O')
		|| (file_content->line[0] == 'S' && file_content->line[1] == 'O')
		|| (file_content->line[0] == 'W' && file_content->line[1] == 'E')
		|| (file_content->line[0] == 'E' && file_content->line[1] == 'A'))
	{
		if (add_tex(file_content) == -1)
			return (-1);
	}
	else if (file_content->line[0] == 'C' || file_content->line[0] == 'F')
	{
		if (add_color(file_content) == -1)
			return (-1);
	}
	return (0);
}

int	separate_elements(t_lines *file_content)
{
	t_lines	*tmp;

	tmp = file_content;
	while (tmp && tmp->line[0] == '\n')
		tmp = tmp->next;
	if (separate_tex_color(tmp) == -1)
		return (free_lines(&file_content), -1);
	return (free_lines(&file_content), 0);
}
