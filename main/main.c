#include "include.h"

int	main(int ac, char **av)
{
	(void)ac;
	if (parse_file(av[1]))
		printf("wrong\n");
	else
		printf("succes\n");
	return (0);
}
