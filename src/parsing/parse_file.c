/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:41:42 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/10/21 00:11:28 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include <stddef.h>

void	free_array(char **arr)
{
	int	index;

	index = 0;
	while (arr[index])
	{
		free(arr[index]);
		index++;
	}
	free(arr[index]);
	free(arr);
}

int	check_file_name(char *file_name)
{
	int		len;
	char	*tmp;

	if (!file_name)
		return (1);
	len = ft_strlen(file_name);
	if (len < 5)
		return (1);
	tmp = ft_substr(file_name, len - 4, 4);
	if (ft_strncmp(".cub", tmp, 5) != 0)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int	open_file(char *file_name)
{
	if (check_file_name(file_name))
		return (1);
	return (open(file_name, O_RDONLY));
}

int	parse_file(char	*file_name)
{
	int		fd;
	size_t	len;
	char	**file_content;
	t_map	*map;

	map = NULL;
	fd = open_file(file_name);
	if (fd == -1)
		return (1);
	len = file_len(fd);
	close(fd);
	fd = open_file(file_name);
	if (fd == -1)
		return (1);
	file_content = read_file(fd, len);
	map = parse_content(file_content, len);
	if (!map)
		return (free_array(file_content), close(fd), 1);
	for (size_t i = 0; i < map->map->count - 2; i++)
		printf("%s", map->map->array[i]);
	printf("%s", map->textures->ea);
	printf("%s", map->textures->so);
	printf("%s", map->textures->no);
	printf("%s", map->textures->we);
	for (int i = 0; i < 3; i++)
	{
		printf("%d\n", map->ceilling[i]);
		printf("%d\n", map->floore[i]);
	}
	free_map(map);
	free_array(file_content);
	close(fd);
	return (0);
}
