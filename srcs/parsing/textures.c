/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournio <sfournio@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:58:12 by sfournio          #+#    #+#             */
/*   Updated: 2021/01/22 13:54:16 by sfournio         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		case_no(char *str, t_global *global)
{
	int		i;
	int		j;
	char	*str2;

	if (global->lol->dno == 1)
		return (-1);
	global->lol->dno = 1;
	i = 2;
	skip_spaces(str, &i, 1);
	if (!(str2 = ft_calloc(path_max(str, i) + 1, sizeof(char))))
		return (-1);
	j = 0;
	while (str[++i] != '\0' && str[i] != '\n')
		str2[j++] = str[i];
	str2[j] = '\0';
	free(global->lol->no);
	global->lol->no = str2;
	return (0);
}

int		case_so(char *str, t_global *global)
{
	int		i;
	int		j;
	char	*str2;

	if (global->lol->dso == 1)
		return (-1);
	global->lol->dso = 1;
	i = 2;
	skip_spaces(str, &i, 1);
	if (!(str2 = ft_calloc(path_max(str, i) + 1, sizeof(char))))
		return (-1);
	j = 0;
	while (str[++i] != '\0' && str[i] != '\n')
		str2[j++] = str[i];
	str2[j] = '\0';
	free(global->lol->so);
	global->lol->so = str2;
	return (0);
}

int		case_ea(char *str, t_global *global)
{
	int		i;
	int		j;
	char	*str2;

	if (global->lol->dea == 1)
		return (-1);
	global->lol->dea = 1;
	i = 2;
	skip_spaces(str, &i, 1);
	if (!(str2 = ft_calloc(path_max(str, i) + 1, sizeof(char))))
		return (-1);
	j = 0;
	while (str[++i] != '\0' && str[i] != '\n')
		str2[j++] = str[i];
	free(global->lol->ea);
	global->lol->ea = str2;
	str2[j] = '\0';
	return (0);
}

int		case_we(char *str, t_global *global)
{
	int		i;
	int		j;
	char	*str2;

	if (global->lol->dwe == 1)
		return (-1);
	global->lol->dwe = 1;
	i = 2;
	skip_spaces(str, &i, 1);
	if (!(str2 = ft_calloc(path_max(str, i) + 1, sizeof(char))))
		return (-1);
	j = 0;
	while (str[++i] != '\0' && str[i] != '\n')
		str2[j++] = str[i];
	str2[j] = '\0';
	free(global->lol->we);
	global->lol->we = str2;
	return (0);
}

int		case_s(char *str, t_global *global)
{
	int		i;
	int		j;
	char	*str2;

	global->lol->ds = 1;
	i = 1;
	skip_spaces(str, &i, 1);
	if (!(str2 = ft_calloc(path_max(str, i) + 1, sizeof(char))))
		return (-1);
	j = 0;
	while (str[++i] != '\0' && str[i] != '\n')
		str2[j++] = str[i];
	str2[j] = '\0';
	global->lol->s = str2;
	return (0);
}
