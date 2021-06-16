#include "mini_parser.h"

static int	ft_clear(char *buffer, char *rmd)
{
	if (rmd)
		free(rmd);
	if (buffer)
		free(buffer);
	return (-1);
}

char	*ft_join_line(char *rmd)
{
	char	*new;
	size_t	len;
	size_t	indx;

	if (!rmd)
		return (0);
	len = ft_strlen_endl(rmd);
	indx = 0;
	new = (char *)malloc((len + 1) * sizeof(char));
	if (new == NULL)
		return (0);
	while (len--)
	{
		new[indx] = *rmd++;
		indx++;
	}
	new[indx] = '\0';
	return (new);
}

char	*ft_rewrite_rmd(char *rmd)
{
	char	*new;
	size_t	len;
	size_t	indx;

	indx = 0;
	len = ft_strlen_endl(rmd);
	if (rmd[len++] == '\0')
	{
		free(rmd);
		return (0);
	}
	new = (char *)malloc(((ft_strlen(rmd) - len) + 1) * sizeof(char));
	if (new == NULL)
	{
		free(rmd);
		return (0);
	}
	while (rmd[len + indx])
	{
		new[indx] = rmd[len + indx];
		indx++;
	}
	new[indx] = '\0';
	free(rmd);
	return (new);
}

int	get_next_line(int fd, char **line)
{
	static char	*rmd;
	char		*buffer;
	int			rd;

	if (fd < 0 || BUFFER_SIZE < 1 || !line
		|| !(buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	rd = 1;
	while (rd && !(ft_strendl(rmd)))
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1)
			return (ft_clear(buffer, rmd));
		buffer[rd] = '\0';
		rmd = ft_strjoin(rmd, buffer);
	}
	*line = ft_join_line(rmd);
	rmd = ft_rewrite_rmd(rmd);
	free(buffer);
	if (rd)
		return (1);
	return (0);
}
