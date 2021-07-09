
#include "../minishell.h"

int		space_skip(const char *nptr, int index)
{
	while ((nptr[index] == ' ') || (nptr[index] == '\n')
		|| (nptr[index] == '\f') || (nptr[index] == '\v')
		|| (nptr[index] == '\r') || (nptr[index] == '\t'))
		index++;
	return (index);
}

void	ft_putendl(char *s, int endl)
{
	size_t	i;

	i = -1;
	if (s)
	{
		while (s[++i])
			write(1, &s[i], 1);
	}
	if (endl == 1)
		write(1, "\n", 1);
}

size_t	ft_strlen2(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*token_strjoin(char *rmd, char *buffer)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	indx;

	len1 = ft_strlen2(rmd);
	len2 = ft_strlen2(buffer);
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
