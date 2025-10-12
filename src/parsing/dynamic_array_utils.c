#include "include.h"
#include "libft.h"

int	da_init(t_dynamic_array *da)
{
	da->size = sizeof(char *);
	da->count = 2;
	da->array = malloc(da->size * da->size);
	if (!da->array)
		return (1);
	ft_memset(da->array, 0, da->count * da->size);
	return (0);
}

int	da_append(t_dynamic_array *da, char *s)
{
	t_dynamic_array	tmp;
	int				index;

	index = 0;
	if (da && da->count == 2)
	{
		if (!da->array[0])
			da->array[0] = s;
		else
		{
			da_init(&tmp);
			tmp.array[0] = da->array[0];
			free(da->array[0]);
			free(da->array[1]);
			da->count++;
			da->array = malloc(da->count * da->size);
			if (!da->array)
			{
				da_free(&tmp);
				return (1);
			}
			while (da->array[index])
			{
				da->array[index] = tmp.array[index];
				index++;
			}
			da->array[index] = NULL;
			da_free(&tmp);
		}
	}
	return (0);
}
