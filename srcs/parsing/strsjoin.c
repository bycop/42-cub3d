/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournio <sfournio@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:35:06 by sfournio          #+#    #+#             */
/*   Updated: 2021/02/24 13:45:03 by sfournio         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_strslen(char **strs)
{
	int i;

	i = 0;
	if (!strs)
		return (0);
	while (strs[i] != NULL)
		i++;
	return (i);
}

void	free_all(char **strs, int j)
{
	int i;

	i = 0;
	while (i != j)
		free(strs[i++]);
	free(strs);
}

char	**ft_strsjoin(char **s1, char *s2)
{
	char	**strs;
	int		i;

	i = 0;
	if (!(strs = malloc(sizeof(char*) * (ft_strslen(s1) + 2))))
		return (NULL);
	if (s1)
		while (s1[i])
		{
			strs[i] = ft_strdup(s1[i]);
			i++;
		}
	strs[i++] = ft_strdup(s2);
	strs[i] = NULL;
	free_all(s1, ft_strslen(s1));
	free(s2);
	return (strs);
}
