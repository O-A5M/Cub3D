#include "include.h"

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
