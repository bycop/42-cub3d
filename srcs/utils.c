/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 16:55:16 by bycop          #+#    #+#             */
/*   Updated: 2021/02/24 13:52:52 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_spaces(char *str, int *index, int type)
{
	while (str[*index] == ' ')
		*index += 1;
	if (type == 1)
		*index -= 1;
}

int		spaces_count(char *str)
{
	int i;
	int count;

	count = 0;
	i = -1;
	while (str[++i])
		if (str[i] == ' ')
			count++;
	return (count);
}

int		digit_max(char *str, int i)
{
	int j;

	j = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		i++;
		j++;
	}
	return (j);
}

int		path_max(char *str, int i)
{
	int j;

	i++;
	j = 0;
	while (str[i] != '\0' && str[i] != ' ')
	{
		i++;
		j++;
	}
	return (j);
}

int		is_map_char(char c)
{
	if (c != '1' && c != '0' && c != '2' && c != 'E' && c != 'N' && c !=
		'S' && c != 'W' && c != ' ')
		return (0);
	return (1);
}
