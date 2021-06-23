#include "libft.h"

#include <stdio.h>
int ft_str_in_strs(char *needle, char **arr)
{
	while (arr && *arr && needle)
	{
		//printf("\t\t\t%s %s\n", *arr, needle);
		if (!ft_strcmp(*arr, needle))
			return (1);
		arr++;
	}
	return (0);
}
