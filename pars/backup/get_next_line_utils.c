#include "mini_parser.h"

size_t	ft_strlen_endl(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strendl(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *rmd, char *buffer)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	indx;

	len1 = ft_strlen(rmd);
	len2 = ft_strlen(buffer);
	indx = 0;
	str = (char *)malloc((len1 + len2 + 1) * sizeof(*str));
	if (str == NULL)
	{
		if (rmd)
			free(rmd);
		return (0);
	}
	while (len1--)
	{
		str[indx] = rmd[indx];
		indx++;
	}
	while (len2--)
		str[indx++] = *buffer++;
	str[indx] = '\0';
	free(rmd);
	return (str);
}
