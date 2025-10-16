/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:09:15 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/10/16 16:10:25 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include <stddef.h>

size_t	file_len(int fd)
{
	size_t	ret;
	char	*tmp;

	ret = 0;
	tmp = get_next_line(fd);
	while (tmp)
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
	char	*tmp;
	int		index;

	index = 0;
	tmp = NULL;
	if (len == 0)
		return (NULL);
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	while (len - index > 0)
	{
		tmp = get_next_line(fd);
		ret[index] = ft_strdup(tmp);
		index++;
		free (tmp);
	}
	ret[index] = NULL;
	return (ret);
}
