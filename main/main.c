#include "include.h"

int	main(int ac, char **av)
{
	t_params	*param;

	param = params_holder();
	params_init(&param);
	if (ac == 2)
	{
		if (parse_args(av[1]) == -1)
			printf("error\n");
	}
	else
		return (1);
	return (0);
}
