/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 13:44:07 by jsance            #+#    #+#             */
/*   Updated: 2019/09/18 17:36:13 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		word_count(const char *str, char c)
{
	size_t	words;
	size_t	i;

	i = 0;
	words = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (!str[i])
			break ;
		words++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (words);
}

static int			split(char **fresh, size_t words, char const *str, char c)
{
	size_t	i;
	size_t	start;
	size_t	end;

	i = 0;
	start = 0;
	while (i < words && str[start])
	{
		while (str[start] == c)
			start++;
		end = start;
		while (str[end] && str[end] != c)
			end++;
		if (!(fresh[i] = (char*)malloc(sizeof(fresh) * (end - start) + 1)))
		{
			while ((long int)i-- >= 0)
				free(fresh[i]);
			return (1);
		}
		if (!(ft_strcpy(fresh[i], ft_strsub(str, start, end - start))))
			return (1);
		i++;
		start = end + 1;
	}
	return (0);
}

char				**ft_strsplit(char const *s, char c)
{
	size_t	words;
	char	**fresh;

	if (!s)
		return (NULL);
	words = word_count(s, c);
	if (!words)
	{
		if (!(fresh = (char**)malloc(sizeof(*fresh))))
			return (NULL);
		fresh[0] = NULL;
		return (fresh);
	}
	if (!(fresh = (char**)malloc(sizeof(*fresh) * words + 1)))
		return (NULL);
	if (split(fresh, words, s, c))
	{
		free(fresh);
		return (NULL);
	}
	fresh[words] = NULL;
	return (fresh);
}
