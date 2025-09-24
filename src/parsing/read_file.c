#include "include.h"
#include <stddef.h>

size_t	file_len(int fd)
{
	size_t	ret;
	char	*tmp;

	ret = 0;
	tmp = get_next_line(fd);
	while(tmp)
	{
		ret++;
		free(tmp);
		tmp = get_next_line(fd);
	}
	return (ret);
}

char	**read_file(int fd, size_t len)
{
	char	**ret;
	int		index;

	index = 0;
	if (len == 0)
		return (NULL);
	ret = malloc(sizeof(char*) * (len + 1));
	if (!ret)
		return (NULL);
	while (len - index > 0)
	{
		ret[index] = get_next_line(fd);
		index++;
	}
	ret[index] = NULL;
	return (ret);
}
