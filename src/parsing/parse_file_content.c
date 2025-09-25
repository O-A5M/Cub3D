#include "include.h"
#include "libft.h"

int	parse_wall(char **content, int *index, t_map **map)
{
	int	count;

	count = 0;
	while (count < 4)
	{
		if (ft_strnstr(content[*index + count], "NO",2))
			(*map)->textures->no = ft_strdup(content[*index + count]);
		if (ft_strnstr(content[*index + count], "SO",2))
			(*map)->textures->so = ft_strdup(content[*index + count]);
		if (ft_strnstr(content[*index + count], "EA",2))
			(*map)->textures->ea = ft_strdup(content[*index + count]);
		if (ft_strnstr(content[*index + count], "WE",2))
			(*map)->textures->we = ft_strdup(content[*index + count]);
		count++;
	}
	if (!(*map)->textures->ea || !(*map)->textures->no
		|| !(*map)->textures->we || !(*map)->textures->so)
	{
		free_map(map);
		return (-1);
	}
	index += count;
	return (0);
}

int	parse_color(char **content, int *index, t_map **map); // TODO
int	parse_map(char **content, int *index, t_map **map); // TODO

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
			parse_wall(content, &index, &ret);
		else if (content[index][0] == 'F' || content[index][0] == 'C')
			parse_color(content, &index, &ret); // TODO
		else
			parse_map(content, &index, &ret); // TODO
	}
	return (ret);
}
