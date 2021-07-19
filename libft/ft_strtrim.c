/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 23:51:14 by mehtel            #+#    #+#             */
/*   Updated: 2020/11/14 23:52:25 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in(int c, char *set)
{
	while (*set)
	{
		if (c == *set++)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		found;
	char	*trim;

	if (!s1 || !set)
		return (0);
	end = ft_strlen((char *)s1) - 1;
	found = 0;
	start = 0;
	while (!found && start <= end)
		((char_in(s1[start], (char *)set)) && ++start) || ++found;
	found = 0;
	while (!found && end >= start)
		((char_in(s1[end], (char *)set)) && end--) || found++;
	trim = malloc(sizeof(char) * (end - start + 2));
	if (trim)
	{
		found = 0;
		while (start <= end)
			trim[found++] = s1[start++];
		trim[found] = '\0';
	}
	return (trim);
}
