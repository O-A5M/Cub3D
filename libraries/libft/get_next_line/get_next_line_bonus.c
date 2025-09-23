/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 11:25:04 by oakhmouc          #+#    #+#             */
/*   Updated: 2024/12/03 20:10:36 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	fill_line(int fd, char	*buff, char **ret)
{
	int		how_much;
	char	*tmp;

	how_much = 1;
	while (how_much > 0)
	{
		how_much = read(fd, buff, BUFFER_SIZE);
		if (how_much == -1)
		{
			free(*ret);
			*ret = NULL;
			break ;
		}
		else if (how_much == 0)
			break ;
		buff[how_much] = '\0';
		if (!*ret)
			*ret = ft_strdup("");
		tmp = *ret;
		*ret = ft_strjoin(tmp, buff);
		free(tmp);
		if (ft_strchr(*ret, '\n'))
			break ;
	}
}

void	free_the_slave(char *ret, char **left_l)
{
	int	i;

	i = 0;
	while (ret[i] && ret[i] != '\n')
		i++;
	if (ret[i] == '\0')
	{
		free(*left_l);
		*left_l = NULL;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		ret = ft_strdup("");
		return (ret);
	}
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	ret = malloc(sizeof(char) * len + 1);
	if (!ret)
		return (NULL);
	while (start + i < start + len && s[start + i])
	{
		ret[i] = s[start + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

size_t	the_line(char *ret, char **left_l)
{
	size_t	count;

	count = 0;
	while (ret[count] != '\0' && ret[count] != '\n')
		count++;
	if (ret[count] == '\0')
		return (count);
	free(*left_l);
	*left_l = ft_substr(ret, count + 1, ft_strlen(ret) - count);
	return (count);
}

char	*get_next_line(int fd)
{
	static char	*left_l[1024];
	char		*buff;
	char		*ret;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buff);
		buff = NULL;
		free(left_l[fd]);
		left_l[fd] = NULL;
		return (NULL);
	}
	ret = ft_strdup(left_l[fd]);
	if (!ft_strchr(ret, '\n'))
		fill_line(fd, buff, &ret);
	free(buff);
	buff = NULL;
	if (!ret)
		return (NULL);
	free_the_slave(ret, &left_l[fd]);
	ret[the_line(ret, &left_l[fd]) + 1] = '\0';
	return (ret);
}
