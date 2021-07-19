#include "libft.h"

int	ft_str_in_strs(char *needle, char **arr)
{
	while (arr && *arr && needle)
	{
		if (!ft_strcmp(*arr, needle))
			return (1);
		arr++;
	}
	return (0);
}
