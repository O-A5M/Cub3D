#include "include.h"

static int	split_color(char *type, char *colors)
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
