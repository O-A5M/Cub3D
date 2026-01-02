/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:42:24 by aelmsafe          #+#    #+#             */
/*   Updated: 2026/01/02 09:27:13 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include "mlx.h"
#include "rayclude.h"

/*A function added by oakhmouc used to clear image before drawing again */
/*to avoid redrawing on top of another image */
void	clear_screen(t_params *params)
{
	int		x;
	int		y;
	char	*dst;

	x = -1;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			dst = params->img->img_add + (y * params->img->line_length)
				+ (x * (params->img->bpp / 8));
			*(unsigned int *)dst = 0X000000;
		}
	}
	mlx_put_image_to_window(params->mlx->mlx_ptr,
		params->mlx->win_ptr, params->img->img_ptr, 0, 0);
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
	if (params->map[(int)new_y][(int)new_x] != '1'
		&& params->map[(int)new_y][(int)new_x] != ' ')
	{
		params->player->pos_y = new_y;
		params->player->pos_x = new_x;
		params->player->cell_y = (int)params->player->pos_y;
		params->player->cell_x = (int)params->player->pos_x;
	}
	return ;
}

int	exit_and_clear()
{
	t_params	*params;

	params = params_holder();
	free_params(&params);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_params *params)
{
	if (keycode == XK_a || keycode == XK_A)
		params->player_move = 'a';
	else if (keycode == XK_d || keycode == XK_D)
		params->player_move = 'd';
	else if (keycode == XK_w || keycode == XK_W)
		params->player_move = 'w';
	else if (keycode == XK_s || keycode == XK_S)
		params->player_move = 's';
	return (0);
}

int	key_release(int keycode, t_params *params)
{
	(void)keycode;
	params->player_move = 0;
	return (0);
}

int	move_loop(t_params *params)
{
	if (params->player_move == 'a')
		move_player(params, 'a');
	else if (params->player_move == 'd')
		move_player(params, 'd');
	else if (params->player_move == 'w')
		move_player(params, 'w');
	else if (params->player_move == 's')
		move_player(params, 's');
	return (0);
}

int	key_hook(int keycode, t_params *params)
{
	if (keycode == XK_Right)
	{
		params->player->starting_angle
			= fmod((params->player->starting_angle + 360 - 10), 360);
	}
	else if (keycode == XK_Left)
	{
		params->player->starting_angle
			= fmod((params->player->starting_angle + 360 + 10), 360);
	}
	else if (keycode == XK_a || keycode == XK_A)
		move_player(params, 'a');
	else if (keycode == XK_d || keycode == XK_D)
		move_player(params, 'd');
	else if (keycode == XK_w || keycode == XK_W)
		move_player(params, 'w');
	else if (keycode == XK_s || keycode == XK_S)
		move_player(params, 's');
	else if (keycode == XK_Escape)
		exit_and_clear();
	else
		return (1);
	draw_ceiling_and_floor(params);
	ray_caster(params);
	create_minimap(params);
	mlx_put_image_to_window(params->mlx->mlx_ptr, params->mlx->win_ptr, params->img->img_ptr, 0, 0);
	return (0);
}

void	print_coords(t_params *params)
{
	printf("Map Height: %d | Map Width: %d\n", (int)params->map_height_2d, (int)params->map_width_2d);
	printf("Player position:\n");
	printf("pixel y: %d | pixel x: %d\n", (int)params->player->pixel_y, (int)params->player->pixel_x);
	printf("cell y: %d | cell x: %d\n", (int)params->player->cell_y, (int)params->player->cell_x);
	printf("Map:\n");
}

void	print_map(t_params *params)
{
	int	i;
	int	j;

	j = 0;
	printf("MAP HEIGHT: %d\n", params->map_height_2d);
	printf("MAP WIDTH: %d\n", params->map_width_2d);
	while (params->map[j])
	{
		i = 0;
		while (params->map[j][i])
		{
			printf("%c, ", params->map[j][i]);
			i += 1;
		}
		printf("\n");
		j += 1;
	}
}

void	minimap_filler(t_imgdata *img, int line, int cell, int color)
{
	char	*dst;
	int		line_counter;
	int		cell_counter;

	line_counter = 0;
	while (line_counter < CELL_SIZE * 10)
	{
		cell_counter = 0;
		while (cell_counter < CELL_SIZE * 10)
		{
			dst = img->img_add
				+ ((8 * line + line_counter) * img->line_length)
				+ ((8 * cell + cell_counter) * (img->bpp / 8));
			*(unsigned int *)dst = color;
			cell_counter += 1;
		}
		line_counter += 1;
	}
}

int draw_2d_map(t_params *params)
{
    int pixel_y;
    int pixel_x;
    int map_y;
    int map_x;
    char tile;

    pixel_y = -1;
    while (++pixel_y < 16)
    {
        map_y = params->player->cell_y + (pixel_y - 8);
        pixel_x = -1;
        while (++pixel_x < 16)
        {
            map_x = params->player->cell_x + (pixel_x - 8);

            if (map_y >= 0 && map_y < params->map_height_2d
                && map_x >= 0 && map_x < params->map_width_2d
                && params->map[map_y][map_x] != '\0')
            {
                tile = params->map[map_y][map_x];
                if (tile == '0' || tile == 'E' || tile == 'W'
                    || tile == 'N' || tile == 'S')
                    minimap_filler(params->img, pixel_x, pixel_y, 0x4a8eff);
                else if (tile == '1')
                    minimap_filler(params->img, pixel_x, pixel_y, 0x2e3136);
                else
                    minimap_filler(params->img, pixel_x, pixel_y, 0x13161c);
            }
            else
                minimap_filler(params->img, pixel_x, pixel_y, 0x000000);
        }
    }
    minimap_filler(params->img, 8, 8, 0xFF0000);
    return (0);
}

int	create_minimap(t_params *params)
{
	draw_2d_map(params);
	return (0);
}

int	mouse_move(int x, int y, t_params *params)
{
	static int	old_x;

	(void)y;
	if (x % 3 == 0)
	{
		if (old_x - x)
		{
			params->player->starting_angle
				= fmod((params->player->starting_angle + 360 - 2), 360);
		}
		if (old_x - x)
		{
			params->player->starting_angle
				= fmod((params->player->starting_angle + 360 + 2), 360);
		}
		old_x = x;
		draw_ceiling_and_floor(params);
		ray_caster(params);
		create_minimap(params);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_params		*params;
	t_mlxdata		mlx;
	t_imgdata		img;
	t_playerdata	player;
	t_raydata		ray;

	params = params_holder();
	params_init(&params, &ray, &player);
	if ((ac != 2) || (ac == 2 && parse_args(av[1]) == -1))
		return (free_params(&params), 1);
	if (initiate_mlx(params, &mlx, &img) || calc_map_width_and_height(params)
		|| set_starting_angle(params) || set_pixel_coords(params))
		return (free_params(&params), 1);
	print_map(params);
	if (load_textures() == -1)
	{
		free_params(&params);
		exit (1);
	}
	draw_ceiling_and_floor(params);
	ray_caster(params);
	create_minimap(params);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, img.img_ptr, 0, 0);
	mlx_hook(params->mlx->win_ptr, 2, 1L<<0,key_hook, params);
	mlx_hook(params->mlx->win_ptr, 3, 1L<<1,key_hook, params);
	mlx_hook(params->mlx->win_ptr, 17, 0, exit_and_clear, params->mlx->mlx_ptr);
	mlx_hook(params->mlx->win_ptr, 6, 1L<<6, mouse_move, params);
	mlx_loop_hook(params->mlx->mlx_ptr, move_loop, params);
	mlx_loop(params->mlx->mlx_ptr);
	return (free_params(&params), 0);
}
