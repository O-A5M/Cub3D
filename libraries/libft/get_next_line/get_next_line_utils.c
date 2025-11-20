/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 11:25:36 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/09/24 13:44:29 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_(const char *s)
{
	size_t	n;

	n = 0;
	if (!s)
		return (0);
	while (s[n])
	{
		n++;
	}
	return (n);
}

char	*ft_strchr_(char *s, int c)
{
	unsigned int	i;
	char			cc;

	if (!s)
		return (NULL);
	cc = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *) &s[i]);
	return (NULL);
}

char	*ft_strdup_(const char *s)
{
	char	*ret;
	int		i;

	if (!s)
		return (NULL);
	i = ft_strlen_(s);
	ret = (char *)malloc(sizeof(char) * i + 1);
	if (!ret)
		return (NULL);
	while (i >= 0)
	{
		ret[i] = s[i];
		i--;
	}
	return (ret);
}

void	fill_it(char const *s1, char const *s2, char *dst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dst[i] = s2[j];
		j++;
		i++;
	}
	dst[i] = '\0';
}

char	*ft_strjoin_(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen_(s1) + ft_strlen_(s2);
	ret = malloc(sizeof(char) * i + 1);
	if (!ret)
		return (NULL);
	fill_it(s1, s2, ret);
	return (ret);
}
