/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_wasd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 11:42:47 by bycop          #+#    #+#             */
/*   Updated: 2021/02/23 13:17:47 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_w(t_global *global)
{
	double	move_speed;

	move_speed = MOV_SPEED;
	if (global->wind->key_shift == 1)
		move_speed *= 2;
	if (global->wind->key_a == 1 || global->wind->key_d == 1)
		move_speed /= 2;
	if (global->map[(int)(global->wind->posx
		+ global->wind->dirx * move_speed)][(int)(global->wind->posy)] == '0')
		global->wind->posx += global->wind->dirx * move_speed;
	if (global->map[(int)(global->wind->posx)]
		[(int)(global->wind->posy + global->wind->diry * move_speed)] == '0')
		global->wind->posy += global->wind->diry * move_speed;
	return (0);
}

int		key_s(t_global *global)
{
	double	move_speed;

	move_speed = MOV_SPEED;
	if (global->wind->key_shift == 1)
		move_speed *= 2;
	if (global->wind->key_a == 1 || global->wind->key_d == 1)
		move_speed /= 2;
	if (global->map[(int)(global->wind->posx
		- global->wind->dirx * move_speed)][(int)(global->wind->posy)] == '0')
		global->wind->posx -= global->wind->dirx * move_speed;
	if (global->map[(int)(global->wind->posx)]
		[(int)(global->wind->posy - global->wind->diry * move_speed)] == '0')
		global->wind->posy -= global->wind->diry * move_speed;
	return (0);
}

int		key_d(t_global *global)
{
	double	move_speed;

	move_speed = MOV_SPEED;
	if (global->wind->key_shift == 1)
		move_speed *= 2;
	if (global->wind->key_w == 1 || global->wind->key_s == 1)
		move_speed /= 2;
	if (global->map[(int)(global->wind->posx)]
		[(int)(global->wind->posy - global->wind->dirx * move_speed)] == '0')
		global->wind->posy -= global->wind->dirx * move_speed;
	if (global->map[(int)(global->wind->posx +
		global->wind->diry * move_speed)][(int)(global->wind->posy)] == '0')
		global->wind->posx += global->wind->diry * move_speed;
	return (0);
}

int		key_a(t_global *global)
{
	double	move_speed;

	move_speed = MOV_SPEED;
	if (global->wind->key_shift == 1)
		move_speed *= 2;
	if (global->wind->key_w == 1 || global->wind->key_s == 1)
		move_speed /= 2;
	if (global->map[(int)(global->wind->posx)]
		[(int)(global->wind->posy + global->wind->dirx * move_speed)] == '0')
		global->wind->posy += global->wind->dirx * move_speed;
	if (global->map[(int)(global->wind->posx
		- global->wind->diry * move_speed)][(int)(global->wind->posy)] == '0')
		global->wind->posx -= global->wind->diry * move_speed;
	return (0);
}
