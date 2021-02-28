/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_drawer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournio <sfournio@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:07:31 by sfournio          #+#    #+#             */
/*   Updated: 2021/02/28 12:05:18 by sfournio         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**		Step + Distance avec le mur
*/

void	found_step(t_global *global, t_tmptex *tmp)
{
	tmp->hit = 0;
	if (tmp->raydirx < 0)
	{
		tmp->stepx = -1;
		tmp->sidedistx = (global->wind->posx - tmp->mapx) * tmp->deltadistx;
	}
	else
	{
		tmp->stepx = 1;
		tmp->sidedistx = (tmp->mapx + 1.0 - global->wind->posx)
						* tmp->deltadistx;
	}
	if (tmp->raydiry < 0)
	{
		tmp->stepy = -1;
		tmp->sidedisty = (global->wind->posy - tmp->mapy) * tmp->deltadisty;
	}
	else
	{
		tmp->stepy = 1;
		tmp->sidedisty = (tmp->mapy + 1.0 - global->wind->posy)
						* tmp->deltadisty;
	}
}

/*
**		Draw texture vertical line
*/

void	tex_drawer(t_global *global, t_tmptex *tmp, int t, int y)
{
	unsigned int	color;
	int				texy;

	while (y++ < tmp->drawstart)
	{
		global->wind->addr[t] = global->lol->c[0] * 16 * 16 * 16 * 16 +
								global->lol->c[1] * 16 * 16 + global->lol->c[2];
		t += global->size_x;
	}
	while (y++ <= tmp->drawend)
	{
		texy = (int)tmp->texpos & (global->img[tmp->texnum].h - 1);
		tmp->texpos += tmp->step;
		color = global->img[tmp->texnum].addr[global->img[tmp->texnum].h *
					texy + tmp->texx];
		global->wind->addr[t] = color;
		t += global->size_x;
	}
	while (y++ <= global->size_y)
	{
		global->wind->addr[t] = global->lol->f[0] * 16 * 16 * 16 * 16 +
								global->lol->f[1] * 16 * 16 + global->lol->f[2];
		t += global->size_x;
	}
}

/*
**		Init texture structure + detection mur / side
*/

void	tex_calc(t_global *global, t_tmptex *tmp)
{
	tmp->camerax = 2 * global->wind->x / (double)global->wind->w - 1;
	tmp->raydirx = global->wind->dirx + global->wind->planex * tmp->camerax;
	tmp->raydiry = global->wind->diry + global->wind->planey * tmp->camerax;
	tmp->mapx = (int)global->wind->posx;
	tmp->mapy = (int)global->wind->posy;
	tmp->deltadistx = fabs(1 / tmp->raydirx);
	tmp->deltadisty = fabs(1 / tmp->raydiry);
	found_step(global, tmp);
	while (tmp->hit == 0)
	{
		if (tmp->sidedistx < tmp->sidedisty)
		{
			tmp->sidedistx += tmp->deltadistx;
			tmp->mapx += tmp->stepx;
			tmp->side = 0;
		}
		else
		{
			tmp->sidedisty += tmp->deltadisty;
			tmp->mapy += tmp->stepy;
			tmp->side = 1;
		}
		if (global->map[tmp->mapx][tmp->mapy] == '1')
			tmp->hit = 1;
	}
}

/*
**		Draw sprite vertical line
*/

void	sprite_drawer(t_global *global, t_tmptex *tmp, double *zbuffer, int s)
{
	int				texx;
	int				texy;
	int				y;
	unsigned int	color;

	while (++s < tmp->drawendx)
	{
		texx = (int)(256 * (s - (-tmp->spritewidth / 2 + tmp->spritescreenx))
			* global->img[4].w / tmp->spritewidth) / 256;
		tmp->t = s + (tmp->drawstarty * global->size_x);
		if (tmp->transformy > 0 && s > 0 && s < global->wind->w &&
			tmp->transformy < zbuffer[s])
		{
			y = tmp->drawstarty - 1;
			while (++y < tmp->drawendy)
			{
				texy = (((y * 256 - global->wind->h * 128 + tmp->spriteheight
						* 128) * global->img[4].h) / tmp->spriteheight) / 256;
				color = global->img[4].addr[global->img[4].w * texy + texx];
				if (color != 0x00980088)
					global->wind->addr[tmp->t] = color;
				tmp->t += global->size_x;
			}
		}
	}
}

/*
**		Calcul des distances avec les sprites, des tailles ainsi que des
**		intervales de draw (start / end)
*/

void	sprite_calc(t_global *global, t_tmptex *tmp, int *spriteorder, int i)
{
	tmp->spritex = global->sprites[spriteorder[i]].x - global->wind->posx;
	tmp->spritey = global->sprites[spriteorder[i]].y - global->wind->posy;
	tmp->invdet = 1.0 / (global->wind->planex * global->wind->diry -
		global->wind->dirx * global->wind->planey);
	tmp->transformx = tmp->invdet * (global->wind->diry * tmp->spritex -
		global->wind->dirx * tmp->spritey);
	tmp->transformy = tmp->invdet * (-global->wind->planey * tmp->spritex +
		global->wind->planex * tmp->spritey);
	tmp->spritescreenx = (int)((global->wind->w / 2) * (1 + tmp->transformx /
		tmp->transformy));
	tmp->spriteheight = abs((int)(global->wind->h / (tmp->transformy)));
	tmp->drawstarty = -tmp->spriteheight / 2 + global->wind->h / 2;
	if (tmp->drawstarty < 0)
		tmp->drawstarty = 0;
	tmp->drawendy = tmp->spriteheight / 2 + global->wind->h / 2;
	if (tmp->drawendy >= global->wind->h)
		tmp->drawendy = global->wind->h - 1;
	tmp->spritewidth = abs((int)(global->wind->h / (tmp->transformy)));
	tmp->drawstartx = -tmp->spritewidth / 2 + tmp->spritescreenx;
	if (tmp->drawstartx < 0)
		tmp->drawstartx = 0;
	tmp->drawendx = tmp->spritewidth / 2 + tmp->spritescreenx;
	if (tmp->drawendx >= global->wind->w)
		tmp->drawendx = global->wind->w - 1;
}
