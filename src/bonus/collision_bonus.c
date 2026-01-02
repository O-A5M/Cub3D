#include "include.h"

int	is_wall(t_params *p, double y, double x)
{
	return (p->map[(int)y][(int)x] == '1');
}

void	move_player(t_params *params, char direction)
{
	double	move_angle;
	double	new_y;
	double	new_x;

	if (direction == 'a')
		move_angle = params->player->starting_angle + 90;
	else if (direction == 'd')
		move_angle = params->player->starting_angle + 270;
	else if (direction == 'w')
		move_angle = params->player->starting_angle;
	else
		move_angle = params->player->starting_angle + 180;
	new_y = params->player->pos_y - 0.1 * sin(deg_to_rad(move_angle));
	new_x = params->player->pos_x + 0.1 * cos(deg_to_rad(move_angle));
	if (!is_wall(params, new_y + PLAYER_RADIUS, params->player->pos_x)
		&& !is_wall(params, new_y - PLAYER_RADIUS, params->player->pos_x))
		params->player->pos_y = new_y;
	if (!is_wall(params, params->player->pos_y, new_x + PLAYER_RADIUS)
		&& !is_wall(params, params->player->pos_y, new_x - PLAYER_RADIUS))
		params->player->pos_x = new_x;
	params->player->cell_y = (int)params->player->pos_y;
	params->player->cell_x = (int)params->player->pos_x;
}
