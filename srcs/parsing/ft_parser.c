/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournio <sfournio@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:44:44 by sfournio          #+#    #+#             */
/*   Updated: 2021/02/24 13:53:00 by sfournio         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	spawn_map(int j, t_global *global, char *str)
{
	if (str[j] == 'N' || str[j] == 'E' || str[j] == 'S' || str[j] == 'W')
	{
		if (global->spawn == '\0')
			global->spawn = str[j];
		else
			global->spawn = '0';
	}
}

int		sprites_found(t_global *global)
{
	int i;
	int j;
	int k;

	k = 0;
	i = 0;
	if (!(global->sprites = malloc(sizeof(t_sprites) * global->nbsprites)))
		exit_free(global, -1);
	while (i <= global->map_y)
	{
		j = -1;
		while (global->map[i][++j])
			if (global->map[i][j] == '2')
			{
				global->sprites[k].x = i + 0.5;
				global->sprites[k++].y = j + 0.5;
			}
		i++;
	}
	return (0);
}

int		ft_parser2(t_global *global, char *str, int ret)
{
	ret = global->lol->clamap;
	if (str[0] == 'R' && str[1] == ' ' && !ret && !global->lol->dr)
		ret = case_r(str, global, 1, 0);
	else if (str[0] == 'N' && str[1] == 'O' && str[2] == ' ' && !ret)
		ret = case_no(str, global);
	else if (str[0] == 'S' && str[1] == 'O' && str[2] == ' ' && !ret)
		ret = case_so(str, global);
	else if (str[0] == 'E' && str[1] == 'A' && str[2] == ' ' && !ret)
		ret = case_ea(str, global);
	else if (str[0] == 'W' && str[1] == 'E' && str[2] == ' ' && !ret)
		ret = case_we(str, global);
	else if (str[0] == 'S' && str[1] == ' ' && !ret && !global->lol->ds)
		ret = case_s(str, global);
	else if (str[0] == 'F' && str[1] == ' ' && !ret && !global->lol->df)
		ret = case_f(str, global, 0, 0);
	else if (str[0] == 'C' && str[1] == ' ' && !ret && !global->lol->dc)
		ret = case_c(str, global, 0, 0);
	else if (!str[0] && !ret)
		ret = 0;
	else if (!is_map_char(str[0]))
		ret = -1;
	else
		ret = case_map(str, global);
	return (ret);
}

int		ft_parser(int fd, t_global *global, int ret)
{
	char	*str;

	while (get_next_line(fd, &str) == 1)
	{
		ret = ft_parser2(global, str, 0);
		free(str);
		if (ret == -1)
			return (error_log(8));
	}
	free(str);
	close(fd);
	return (0);
}
