#include "include.h"

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		if (parse_args(av[1]) == -1)
			printf("error\n");
	}
	else
		return (1);
	return (0);
}
