#include "include.h"

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
