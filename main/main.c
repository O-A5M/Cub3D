#include "include.h"

int	main(int ac, char **av)
{
	(void)ac;
	if (ac == 2)
	{
		if (parse_file(av[1]))
			printf("wrong\n");
		else
			printf("succes\n");
	}
	else
	{
		printf("Please enter a valide file\n");
		return (1);
	}
	return (0);
}
