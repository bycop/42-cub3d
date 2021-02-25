/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_verif.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournio <sfournio@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:46:45 by sfournio          #+#    #+#             */
/*   Updated: 2021/02/25 13:36:55 by sfournio         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		xpm_verif(t_global *global)
{
	if (global->lol->no == NULL ||
		ft_strncmp(&global->lol->no[ft_strlen(global->lol->no) - 4],
		".xpm", 5) != 0 || global->lol->so == NULL ||
		ft_strncmp(&global->lol->so[ft_strlen(global->lol->so) - 4],
		".xpm", 5) != 0 || global->lol->ea == NULL ||
		ft_strncmp(&global->lol->ea[ft_strlen(global->lol->ea) - 4],
		".xpm", 5) != 0 || global->lol->we == NULL ||
		ft_strncmp(&global->lol->we[ft_strlen(global->lol->we) - 4],
		".xpm", 5) != 0 || global->lol->s == NULL ||
		ft_strncmp(&global->lol->s[ft_strlen(global->lol->s) - 4],
		".xpm", 5) != 0)
		return (-1);
	else
		return (0);
}

int		texture_verif(t_global *global)
{
	int fd;

	if (xpm_verif(global) == -1)
		return (error_log(5));
	if ((fd = open(global->lol->ea, O_RDWR)) < 0)
		return (error_log(5));
	close(fd);
	if ((fd = open(global->lol->no, O_RDWR)) < 0)
		return (error_log(5));
	close(fd);
	if ((fd = open(global->lol->so, O_RDWR)) < 0)
		return (error_log(5));
	close(fd);
	if ((fd = open(global->lol->we, O_RDWR)) < 0)
		return (error_log(5));
	close(fd);
	if ((fd = open(global->lol->s, O_RDWR)) < 0)
		return (error_log(5));
	close(fd);
	return (0);
}

int		color_verif(t_global *global)
{
	if (global->lol->f[0] >= 0 && global->lol->f[0] <= 255 &&
		global->lol->f[1] >= 0 && global->lol->f[1] <= 255 &&
		global->lol->f[2] >= 0 && global->lol->f[2] <= 255 &&
		global->lol->c[0] >= 0 && global->lol->c[0] <= 255 &&
		global->lol->c[1] >= 0 && global->lol->c[1] <= 255 &&
		global->lol->c[2] >= 0 && global->lol->c[2] <= 255 &&
		global->lol->neg == 0)
		return (0);
	else
		return (-1);
}

void	res_verif(t_global *global, int savem, int savep)
{
	while ((global->size_x - savem) % 64 != 0)
		savem++;
	savem = global->size_x - savem;
	while ((global->size_x + savep) % 64 != 0)
		savep++;
	savep = global->size_x + savep;
	if (savep - global->size_x > global->size_x - savem)
		global->size_x = savem;
	else
		global->size_x = savep;
	savem = 0;
	savep = 0;
	while ((global->size_y - savem) % 64 != 0)
		savem++;
	savem = global->size_y - savem;
	while ((global->size_y + savep) % 64 != 0)
		savep++;
	savep = global->size_y + savep;
	if (savep - global->size_y > global->size_y - savem)
		global->size_y = savem;
	else
		global->size_y = savep;
}

int		struct_verif(t_global *global)
{
	int i;

	if (global->size_x > global->max_x)
		global->size_x = global->max_x;
	if (global->size_y > global->max_y)
		global->size_y = global->max_y;
	if (global->size_x < 128)
		global->size_x = 128;
	if (global->size_y < 128)
		global->size_y = 128;
	if (global->intmax == 1)
		return (error_log(8));
	res_verif(global, 0, 0);
	i = 0;
	if ((global->lol->f[0] == -1 && global->lol->f[1] == -1
		&& global->lol->f[2] == -1) || (global->lol->c[0] == -1
		&& global->lol->c[1] == -1 && global->lol->c[2] == -1))
		return (error_log(4));
	if (color_verif(global) == -1)
		return (error_log(7));
	if (global->spawn == '0' || global->spawn == '\0')
		return (error_log(3));
	if (texture_verif(global) == -1 || map_verif(global, 0, -1) == -1)
		return (-1);
	return (0);
}
