/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:07:40 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/10/16 18:29:18 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include <stddef.h>

int	da_init(t_dynamic_array **da, size_t count)
{
	size_t	index;

	index = 0;
	(*da) = malloc(sizeof(t_dynamic_array));
	if (!*da)
		return (1);
	(*da)->count = count;
	(*da)->size = sizeof(char *);
	(*da)->array = malloc((*da)->size * (*da)->count);
	if (!(*da)->array)
		return (1);
	while (index < (*da)->count)
		(*da)->array[index++] = NULL;
	return (0);
}

int	da_append(t_dynamic_array **da, char *s)
{
	t_dynamic_array	*tmp;
	size_t			index;

	index = 0;
	da_init(&tmp, (*da)->count);
	while ((*da)->count > 1 && (*da)->array[index])
	{
		tmp->array[index] = ft_strdup((*da)->array[index]);
		index++;
	}
	da_free(*da);
	da_init(da, tmp->count + 1);
	index = 0;
	while ((*da)->count > 2 && index < tmp->count - 1)
	{
		(*da)->array[index] = ft_strdup(tmp->array[index]);
		index++;
	}
	(*da)->array[index] = ft_strdup(s);
	da_free(tmp);
	return (0);
}

void	da_free(t_dynamic_array *da)
{
	size_t	index;

	index = 0;
	if (da->array)
	{
		while (index < da->count)
			free(da->array[index++]);
		free(da->array);
	}
	free(da);
}
