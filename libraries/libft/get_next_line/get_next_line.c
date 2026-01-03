/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 11:25:04 by oakhmouc          #+#    #+#             */
/*   Updated: 2026/01/02 12:59:54 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft.h"

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
			*ret = ft_strdup_("");
		tmp = *ret;
		*ret = ft_strjoin_(tmp, buff);
		free(tmp);
		if (ft_strchr_(*ret, '\n'))
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

char	*ft_substr_(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen_(s))
	{
		ret = ft_strdup_("");
		return (ret);
	}
	if (len > ft_strlen_(s + start))
		len = ft_strlen_(s + start);
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
	*left_l = ft_substr_(ret, count + 1, ft_strlen_(ret) - count);
	return (count);
}

char	*get_next_line(int fd)
{
	static char	*left_l;
	char		*buff;
	char		*ret;
	char		*tmp;

	buff = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buff);
		buff = NULL;
		free(left_l);
		left_l = NULL;
		return (NULL);
	}
	ret = ft_strdup_(left_l);
	if (!ft_strchr_(ret, '\n'))
		fill_line(fd, buff, &ret);
	free(buff);
	buff = NULL;
	if (!ret)
		return (NULL);
	free_the_slave(ret, &left_l);
	tmp = ft_substr_(ret, 0, the_line(ret, &left_l) + 1);
	return (free(ret), tmp);
}
