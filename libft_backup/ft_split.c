/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 23:52:42 by mehtel            #+#    #+#             */
/*   Updated: 2020/11/14 23:55:10 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*fill_str(char const *s, long int *start, long int *end)
{
	char		*word;

	if ((*end - *start) && (word = \
				(char*)malloc(sizeof(char) * (*end - *start + 1))))
	{
		word[*end - *start] = '\0';
		while (*start != (*end)--)
		{
			word[*end - *start] = s[*end];
		}
		*start += ft_strlen(word) + 1;
		return (word);
	}
	else
		return (0);
}

static void		free_strs(char **arr, long int i)
{
	while (i)
		free(arr[i]);
	free(arr[i]);
}

static int		fill_arr(char **arr, long int arr_len, char const *s, char c)
{
	long int	start;
	long int	end;
	long int	i;
	char		*word;

	start = 0;
	end = 0;
	i = 0;
	while (i < arr_len)
	{
		while (s[start] == c)
			start++;
		end = start;
		while (!(s[end] == c) && s[end])
			end++;
		if (!(word = fill_str(s, &start, &end)))
		{
			free_strs(arr, i - 1);
			return (0);
		}
		arr[i++] = word;
	}
	return (1);
}

char			**ft_split(char const *s, char c)
{
	int			end;
	long int	arr_len;
	char		**arr;

	end = -1;
	arr_len = 0;
	if (!s)
		return (0);
	while (s[++end])
		(s[end] != c && (s[end + 1] == c || !s[end + 1])) ? \
			arr_len++ : 1;
	if (!(arr = (char**)malloc(sizeof(char**) * (arr_len + 1))))
		return (0);
	arr[arr_len] = 0;
	if (!fill_arr(arr, arr_len, s, c))
	{
		free(arr);
		arr = 0;
	}
	return (arr);
}
