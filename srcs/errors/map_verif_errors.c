/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verif_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournio <sfournio@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:13:29 by sfournio          #+#    #+#             */
/*   Updated: 2021/02/24 13:59:26 by sfournio         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		args_verif(t_global *global, char **argv, int argc)
{
	int fd;

	fd = 0;
	if (argc >= 2 && argc <= 3)
	{
		if (argv[1][ft_strlen(argv[1]) - 1] != 'b' ||
			argv[1][ft_strlen(argv[1]) - 2] != 'u' ||
			argv[1][ft_strlen(argv[1]) - 3] != 'c' ||
			argv[1][ft_strlen(argv[1]) - 4] != '.')
			return (error_log(0));
		if (argc == 3 && ft_strncmp(argv[2], "--save", 7) != 0)
			return (error_log(0));
	}
	else
		return (error_log(0));
	fd = open(argv[1], O_RDWR);
	if (fd < 0)
		return (error_log(0));
	if (argc == 3)
		global->save = 1;
	return (fd);
}

void	wall_verif(t_global *glob, int found, int y, int x)
{
	if (y > glob->map_y || y == -1 || x == -1 || x >= (int)
		ft_strlen(glob->map[y]))
	{
		error_log(2);
		exit_free(glob, -1);
	}
	else if (glob->map[y][x] == ' ')
	{
		error_log(6);
		exit_free(glob, -1);
	}
	else if (glob->map[y][x] != '1' && glob->map[y][x] != 'c' &&
		glob->map[y][x] != 'd')
	{
		if (glob->map[y][x] == '2')
			glob->map[y][x] = 'd';
		else
			glob->map[y][x] = 'c';
		wall_verif(glob, found, y - 1, x);
		wall_verif(glob, found, y + 1, x);
		wall_verif(glob, found, y, x + 1);
		wall_verif(glob, found, y, x - 1);
	}
}

void	ctozero(t_global *global)
{
	int i;
	int j;

	i = -1;
	while (++i < global->map_y)
	{
		j = -1;
		while (global->map[i][++j])
			if (global->map[i][j] == 'c')
				global->map[i][j] = '0';
			else if (global->map[i][j] == 'd')
				global->map[i][j] = '2';
	}
}

void	height_width(t_global *global)
{
	int max;
	int i;
	int j;

	i = -1;
	max = 0;
	while (++i < global->map_y)
	{
		j = -1;
		while (global->map[i][++j])
			;
		if (j > max)
			max = j;
	}
	global->map_x = max;
}

int		map_verif(t_global *global, int i, int j)
{
	while (i <= global->map_y)
	{
		j = -1;
		while (global->map[i][++j])
			if (!is_map_char(global->map[i][j]))
				return (error_log(1));
			else if (global->map[i][j] != '1' && global->map[i][j] != '0'
					&& global->map[i][j] != '2' && global->map[i][j] != ' ')
			{
				global->spawn_x = j;
				global->spawn_y = i;
				global->spawn = global->map[i][j];
			}
			else if (global->map[i][j] == '2')
				global->nbsprites += 1;
		i++;
	}
	wall_verif(global, 0, global->spawn_y, global->spawn_x);
	ctozero(global);
	height_width(global);
	return (0);
}
