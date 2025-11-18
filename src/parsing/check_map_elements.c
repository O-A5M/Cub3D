#include "include.h"

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
	return (0);
}
