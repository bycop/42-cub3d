/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_rle.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 11:42:43 by bycop          #+#    #+#             */
/*   Updated: 2021/02/24 13:50:23 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		close_button(t_global *global)
{
	mlx_destroy_window(global->wind->mlx, global->wind->win);
	printf("Close button...\n");
	exit_free(global, -1);
	return (0);
}

int		key_right(t_global *global)
{
	double olddirx;
	double oldplanex;

	oldplanex = global->wind->planex;
	olddirx = global->wind->dirx;
	global->wind->dirx = global->wind->dirx * cos(-ROT_SPEED)
	- global->wind->diry * sin(-ROT_SPEED);
	global->wind->diry = olddirx * sin(-ROT_SPEED)
	+ global->wind->diry * cos(-ROT_SPEED);
	global->wind->planex = global->wind->planex * cos(-ROT_SPEED)
	- global->wind->planey * sin(-ROT_SPEED);
	global->wind->planey = oldplanex * sin(-ROT_SPEED)
	+ global->wind->planey * cos(-ROT_SPEED);
	return (0);
}

int		key_left(t_global *global)
{
	double olddirx;
	double oldplanex;

	oldplanex = global->wind->planex;
	olddirx = global->wind->dirx;
	global->wind->dirx = global->wind->dirx * cos(ROT_SPEED)
	- global->wind->diry * sin(ROT_SPEED);
	global->wind->diry = olddirx * sin(ROT_SPEED)
	+ global->wind->diry * cos(ROT_SPEED);
	global->wind->planex = global->wind->planex * cos(ROT_SPEED)
	- global->wind->planey * sin(ROT_SPEED);
	global->wind->planey = oldplanex * sin(ROT_SPEED)
	+ global->wind->planey * cos(ROT_SPEED);
	return (0);
}

int		key_escape(t_global *global)
{
	mlx_destroy_window(global->wind->mlx, global->wind->win);
	printf("Close button...\n");
	exit_free(global, -1);
	return (0);
}

int		keypress(int keycode, t_global *global)
{
	if (keycode == KEY_W)
		global->wind->key_w = 1;
	if (keycode == KEY_D)
		global->wind->key_d = 1;
	if (keycode == KEY_A)
		global->wind->key_a = 1;
	if (keycode == KEY_S)
		global->wind->key_s = 1;
	if (keycode == KEY_RIGHT)
		global->wind->key_r = 1;
	if (keycode == KEY_LEFT)
		global->wind->key_l = 1;
	if (keycode == KEY_SHIFT)
		global->wind->key_shift = 1;
	if (keycode == KEY_ESCAPE)
		key_escape(global);
	return (0);
}
