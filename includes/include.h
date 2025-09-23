#ifndef INCLUDE_H
# define INCLUDE_H
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "mlx.h"
#include "libft.h"

// Parsing functions

char	**read_file(int fd, size_t len);
size_t	file_len(int fd);
int		chech_file_name(char *file_name);
int		open_file(char *file_name);
int		parse_file(char *file_name);

#endif
