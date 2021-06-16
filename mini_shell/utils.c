#include "mini_parser.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	d;

	i = 0;
	d = 0;
	if (!s)
		return (0);
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (0);
	while (s[d])
	{
		if (d == start && i < len)
		{
			sub[i] = s[d];
			i++;
			start++;
		}
		d++;
	}
	sub[i] = 0;
	return (sub);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dup;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	if (!(dup = (char *)malloc(i + 1 * sizeof(*s))))
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int		space_skip(const char *nptr, int *index)
{
	while ((nptr[*index] == ' ') || (nptr[*index] == '\n')
		|| (nptr[*index] == '\f') || (nptr[*index] == '\v')
		|| (nptr[*index] == '\r') || (nptr[*index] == '\t'))
		(*index)++;
	return (1);
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (i < n - 1 && s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
	|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}
