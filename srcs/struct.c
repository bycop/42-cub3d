/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 16:31:50 by bycop          #+#    #+#             */
/*   Updated: 2021/03/01 13:54:53 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init2(t_global *global)
{
	global->map_y = -1;
	global->map_x = -1;
	global->lol->f[0] = -1;
	global->lol->f[1] = -1;
	global->lol->f[2] = -1;
	global->lol->c[0] = -1;
	global->lol->c[1] = -1;
	global->lol->c[2] = -1;
	global->lol->neg = 0;
	global->spawn = '\0';
	global->sprites = NULL;
	global->map = NULL;
	global->lol->ea = NULL;
	global->lol->we = NULL;
	global->lol->so = NULL;
	global->lol->no = NULL;
	global->lol->s = NULL;
	global->img = NULL;
	global->intmax = 0;
}

void	ft_init(void *mlx, t_global *global)
{
	int x;
	int y;

	mlx_get_screen_size(mlx, &x, &y);
	global->lol->clamap = 0;
	global->lol->dno = 0;
	global->lol->dso = 0;
	global->lol->dwe = 0;
	global->lol->dea = 0;
	global->lol->ds = 0;
	global->lol->dc = 0;
	global->lol->df = 0;
	global->lol->dr = 0;
	global->size_x = 0;
	global->size_y = 0;
	global->spawn_x = 0;
	global->spawn_y = 0;
	global->save = 0;
	global->sizeint = 0;
	global->nbsprites = 0;
	global->max_x = x;
	global->max_y = y;
	ft_init2(global);
}
