/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournio <sfournio@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 13:50:08 by sfournio          #+#    #+#             */
/*   Updated: 2021/02/24 13:40:29 by sfournio         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	found_dir(t_global *global)
{
	double	s_x;
	double	var;

	if (global->spawn == 'E')
		var = -3.14 / 2;
	else if (global->spawn == 'W')
		var = 3.14 / 2;
	else if (global->spawn == 'S')
		var = 3.14;
	else
		return ;
	s_x = global->wind->dirx;
	global->wind->dirx = global->wind->dirx * cos(var) - global->wind->diry
						* sin(var) + 0.00001;
	global->wind->diry = s_x * sin(var) + global->wind->diry * cos(var);
	s_x = global->wind->planex + 0.00001;
	global->wind->planex = global->wind->planex * cos(var) -
	global->wind->planey * sin(var);
	global->wind->planey = s_x * sin(var) + global->wind->planey * cos(var);
}

int		*sortsprites(t_global *global, int *spriteorder)
{
	int			i;
	int			j;
	t_sprites	tmp;

	j = -1;
	while (++j < global->nbsprites)
	{
		spriteorder[j] = j;
		global->sprites[j].dist = ((global->wind->posx - global->sprites[j].x)
		* (global->wind->posx - global->sprites[j].x) + (global->wind->posy
		- global->sprites[j].y) * (global->wind->posy - global->sprites[j].y));
	}
	i = 0;
	while (i + 1 < global->nbsprites)
	{
		if (global->sprites[i].dist < global->sprites[i + 1].dist)
		{
			tmp = global->sprites[i];
			global->sprites[i] = global->sprites[i + 1];
			global->sprites[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	return (spriteorder);
}

int		find_textnum(int side, double raydirx, double raydiry)
{
	if (side == 0 && raydirx > 0)
		return (1);
	if (side == 0 && raydirx < 0)
		return (0);
	if (side == 1 && raydiry < 0)
		return (3);
	if (side == 1 && raydiry > 0)
		return (2);
	return (0);
}

void	init_window(t_global *global)
{
	global->wind->key_r = 0;
	global->wind->key_l = 0;
	global->wind->key_w = 0;
	global->wind->key_s = 0;
	global->wind->key_a = 0;
	global->wind->key_d = 0;
	global->wind->posy = global->spawn_x + 0.5;
	global->wind->posx = global->spawn_y + 0.5;
	global->wind->dirx = -1.0 + 0.00001;
	global->wind->diry = 0.00 + 0.00001;
	global->wind->planex = 0;
	global->wind->planey = 0.66;
	found_dir(global);
	global->wind->w = global->size_x;
	global->wind->h = global->size_y;
}

int		cancel(int keycode, t_global *global)
{
	if (keycode == KEY_RIGHT)
		global->wind->key_r = 0;
	if (keycode == KEY_LEFT)
		global->wind->key_l = 0;
	if (keycode == KEY_W)
		global->wind->key_w = 0;
	if (keycode == KEY_A)
		global->wind->key_a = 0;
	if (keycode == KEY_S)
		global->wind->key_s = 0;
	if (keycode == KEY_D)
		global->wind->key_d = 0;
	if (keycode == KEY_SHIFT)
		global->wind->key_shift = 0;
	return (0);
}
