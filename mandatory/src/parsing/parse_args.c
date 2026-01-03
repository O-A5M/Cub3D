/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:42:09 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/11/20 11:48:07 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static int	check_filename(char *filename)
{
	int		len;
	char	*tmp;

	len = 0;
	tmp = NULL;
	if (!filename || filename[0] == 0)
		return (-1);
	len = ft_strlen(filename);
	if (len <= 4)
		return (-1);
	tmp = ft_substr(filename, len - 4, 4);
	if (ft_strncmp(tmp, ".cub", 5))
		return (free (tmp), -1);
	return (free(tmp), 0);
}

int	parse_args(char *filename)
{
	int		fd;
	t_lines	*file_content;

	file_content = NULL;
	fd = -1;
	if (check_filename(filename) == -1)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("cub3D"), -1);
	file_content = extract_file_content(fd);
	if (!file_content)
		return (perror("cub3D"), free_lines(&file_content), -1);
	if (parse_content(file_content) == -1)
		return (free_lines(&file_content), -1);
	return (free_lines(&file_content), 0);
}
