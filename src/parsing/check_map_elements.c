#include "include.h"

int	is_map_surrounded(t_params *param);

int	check_map_elements(void)
{
	int			i;
	int			j;
	t_params	*param;

	i = -1;
	param = params_holder();
	while (param->map[++i])
	{
		j = -1;
		while (param->map[i][++j])
		{
			if (param->player_posX == -1 && param->player_posY == -1
			&& (param->map[i][j] == 'S' || param->map[i][j] == 'N'
			|| param->map[i][j] == 'E' || param->map[i][j] == 'W'))
			{
				param->player_posY = i;
				param->player_posX = j;
				continue ;
			}
			if (param->map[i][j] != '0' && param->map[i][j] != '1'
			&& param->map[i][j] != ' ' && param->map[i][j] != '\n')
				return (-1);
		}
	}
	if (is_map_surrounded(param) == -1)
		return (-1);
	return (0);
}

int	flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0 || !map[y] || !map[y][x]
		|| map[y][x] == ' ')
		return (-1);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	map[y][x] = 'V';
	if (flood_fill(map, x, y - 1) == -1)
		return (-1);
	if (flood_fill(map, x - 1, y) == -1)
		return (-1);
	if (flood_fill(map, x, y + 1) == -1)
		return (-1);
	if (flood_fill(map, x + 1, y) == -1)
		return (-1);
	return (0);
}

char	**copy_map(void)
{
	int		i;
	int		len;
	char	**ret;

	i = -1;
	len = -1;
	while (params_holder()->map[++len])
		;
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (perror("cub3D"), NULL);
	while (params_holder()->map[++i])
		ret[i] = ft_strdup(params_holder()->map[i]);
	ret[i] = NULL;
	return (ret);
}

int	is_map_surrounded(t_params *param)
{
	char	**map;

	map = copy_map();
	if (flood_fill(map, param->player_posX, param->player_posY) == -1)
		return (free_array(&map), -1);
	return (free_array(&map), 0);
}
