/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:42:00 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/11/20 11:42:34 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	free_array(char ***arr)
{
	int	index;

	index = -1;
	if (!arr)
		return ;
	if (!(*arr))
		return ;
	while ((*arr)[++index])
		free((*arr)[index]);
	free(*arr);
	(*arr) = NULL;
}
