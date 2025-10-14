/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:07:40 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/10/14 11:23:08 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	da_init(t_dynamic_array da, size_t count)
{
	da.count = count;
	da.size = sizeof(char *);
	da.array = malloc(da.size * da.count);
	if (!da.array)
		return (1);
	ft_memset(da.array, 0, da.count * da.size);
	return (0);
}

int	da_append(t_dynamic_array da, char *s)
{
	t_dynamic_array	tmp;
	int				index;

	index = 0;
	tmp.array = NULL;
	if (da.count == 2 && !da.array[0])
		da.array[0] = ft_strdup(s);
	else
	{
		da_init(tmp, da.count);
		while (da.array[index++])
			tmp.array[index] = ft_strdup(da.array[index]);
		da_free(da);
		da_init(da, tmp.count + 1);
		index = 0;
		while (tmp.array[index++])
			da.array[index] = ft_strdup(tmp.array[index]);
		da.array[index] = ft_strdup(s);
		da_free(tmp);
	}
	return (0);
}

void	da_free(t_dynamic_array da)
{
	int	index;

	index = 0;
	if (da.array)
	{
		while (da.array[index++])
			free(da.array[index]);
		free(da.array[index]);
		free(da.array);
	}
}
