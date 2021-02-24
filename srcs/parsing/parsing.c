/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournio <sfournio@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 15:45:42 by sfournio          #+#    #+#             */
/*   Updated: 2021/02/24 14:03:36 by sfournio         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		verif_r(char *str)
{
	int i;
	int count;

	count = 0;
	i = 1;
	skip_spaces(str, &i, 1);
	while (str[++i])
	{
		if (str[i] != ' ' && (str[i] < '0' || str[i] > '9'))
			return (-1);
		if (str[i] == ' ')
		{
			skip_spaces(str, &i, 0);
			if (str[i])
				count++;
		}
	}
	if (count != 1)
		return (-1);
	return (0);
}

int		case_r(char *str, t_global *global)
{
	int	i;
	int	res;

	global->lol->dr = 1;
	i = 1;
	res = 0;
	skip_spaces(str, &i, 2);
	if (verif_r(str) == -1)
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	global->size_x = res;
	res = 0;
	skip_spaces(str, &i, 2);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	global->size_y = res;
	return (0);
}

int		case_f(char *str, t_global *global, int j, int res)
{
	int	i;

	global->lol->df = 1;
	i = 2;
	skip_spaces(str, &i, 1);
	while (str[++i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = res * 10 + (str[i] - '0');
		if (str[i] == ',' || str[i] == '\n' || str[i + 1] == '\0')
		{
			if ((str[i] == str[i + 1]) || (str[i] == ',' &&
				(!str[i + 1] || str[i - 1] == ' ')))
				return (-1);
			global->lol->f[j++] = res;
			res = 0;
		}
		else if (str[i] == '-')
			global->lol->neg = 1;
		else if (str[i] > '9' || str[i] < '0')
			return (-1);
	}
	if (j != 3)
		return (-1);
	return (0);
}

int		case_c(char *str, t_global *global, int j, int res)
{
	int	i;

	global->lol->dc = 1;
	i = 2;
	skip_spaces(str, &i, 1);
	while (str[++i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = res * 10 + (str[i] - '0');
		if (str[i] == ',' || str[i] == '\n' || str[i + 1] == '\0')
		{
			if ((str[i] == str[i + 1]) || (str[i] == ',' &&
				(!str[i + 1] || str[i - 1] == ' ')))
				return (-1);
			global->lol->c[j++] = res;
			res = 0;
		}
		else if (str[i] == '-')
			global->lol->neg = 1;
		else if (str[i] > '9' || str[i] < '0')
			return (-1);
	}
	if (j != 3)
		return (-1);
	return (0);
}

int		case_map(char *str, t_global *global)
{
	int		j;
	int		i;
	char	*s;

	global->lol->clamap = 1;
	if (!(s = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		exit_free(global, -1);
	i = -1;
	j = -1;
	while (str[++j])
	{
		spawn_map(j, global, str);
		if (str[j])
			s[++i] = str[j];
	}
	if (ft_strlen(str) == 1)
		return (-1);
	s[++i] = '\0';
	global->map = ft_strsjoin(global->map, s);
	if (global->map == NULL)
		exit_free(global, -1);
	global->map_y += 1;
	return (0);
}
