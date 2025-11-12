#include "include.h"

// int	parse_content(t_lines *file_content);

t_lines	*extract_file_content(int fd)
{
	t_lines	*ret;
	char	*tmp;

	ret = NULL;
	tmp = get_next_line(fd);
	while (!tmp)
	{
		add_line(&ret, new_line(tmp));
		free (tmp);
		tmp = get_next_line(fd);
	}
	return (ret);
}
