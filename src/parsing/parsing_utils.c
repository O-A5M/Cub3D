#include "include.h"
#include "libft.h"

void	free_textures(t_textures **tex)
{
	free((*tex)->so);
	free((*tex)->no);
	free((*tex)->ea);
	free((*tex)->we);
	free((*tex));
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	da_free(map->map);
	if (map->textures)
		free_textures(&map->textures);
	free(map);
}

void	init_map(t_map **map)
{
	da_init(&(*map)->map, 1);
	ft_memset((*map)->floore, -1, sizeof((*map)->floore));
	ft_memset((*map)->ceilling, -1, sizeof((*map)->ceilling));
	(*map)->textures = malloc(sizeof(t_textures));
	(*map)->textures->ea = NULL;
	(*map)->textures->no = NULL;
	(*map)->textures->so = NULL;
	(*map)->textures->we = NULL;
}
