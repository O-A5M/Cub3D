#include "include.h"
#include "libft.h"

int	element_type(char *line)
{
	static int	map_flag;

	if (line[0] == '\n' || line[0] == '\0')
		return (0);
	if (line[0] == 'N' && line[1] == 'O' && map_flag == 1)
		return (-1);
	if (line[0] == 'S' && line[1] == 'O' && map_flag == 1)
		return (-1);
	if (line[0] == 'E' && line[1] == 'A' && map_flag == 1)
		return (-1);
	if (line[0] == 'W' && line[1] == 'E' && map_flag == 1)
		return (-1);
	if ((line[0] == 'F' || line[0] == 'C') && map_flag == 1)
		return (-1);
	if (line[0] == '0' || line[0] == '1' || line[0] == ' ')
		map_flag = 1;
	return (0);
}

int	check_element_order(t_lines *file_content)
{
	t_lines	*tmp;

	tmp = file_content;
	while (tmp)
	{
		if (element_type(tmp->line) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

int	parse_content(t_lines *file_content)
{
	// t_lines	*tmp;

	// tmp = file_content;
	if (check_element_order(file_content) == -1)
		return (-1);
	return (0);
}

t_lines	*extract_file_content(int fd)
{
	t_lines	*ret;
	char	*tmp;

	ret = NULL;
	tmp = get_next_line(fd);
	while (tmp)
	{
		add_line(&ret, new_line(ft_strdup(tmp)));
		free (tmp);
		tmp = get_next_line(fd);
	}
	return (ret);
}
