
#include "libft.h"

char		*ft_strjoind(char const *s1, char const *s2, char const *delim)
{
	char	*str;
	char	*tmp;

	str = 0;
	if (s1 && s2 && delim && (str = malloc(sizeof(char) * \
		(ft_strlen((char*)s1) + ft_strlen((char*)s2) + ft_strlen((char*)delim) + 1))))
	{
		tmp = str;
		while (*s1)
			*tmp++ = *s1++;
		while (*delim)
			*tmp++ = *delim++;
		while (*s2)
			*tmp++ = *s2++;
		*tmp = '\0';
	}
	return (str);
}
