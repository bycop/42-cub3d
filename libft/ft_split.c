/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:46:32 by bycop          #+#    #+#             */
/*   Updated: 2020/11/25 00:55:24 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	freeall(char **res, int j)
{
	int i;

	i = -1;
	while (++i <= j)
		free(res[i]);
	free(res);
}

static char	*wordcreate(char c, char const *s)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && c != s[i])
		i++;
	if (!(word = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = -1;
	while (s[++i] && c != s[i])
		word[i] = s[i];
	word[i] = '\0';
	return (word);
}

static int	countword(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && c == s[i])
			i++;
		if (s[i] && c != s[i])
			count++;
		while (s[i] && c != s[i])
			i++;
	}
	return (count);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	if (!s || !(res = malloc(sizeof(char *) * (countword(s, c) + 1))))
		return (NULL);
	while (s[i])
	{
		while (s[i] && c == s[i])
			i++;
		if (s[i] && c != s[i])
		{
			if ((res[j++] = wordcreate(c, &s[i])) == NULL)
			{
				freeall(res, j - 1);
				return (NULL);
			}
			while (s[i] && c != s[i])
				i++;
		}
	}
	res[j] = 0;
	return (res);
}
