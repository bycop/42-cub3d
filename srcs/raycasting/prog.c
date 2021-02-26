/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournio <sfournio@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:19:43 by sfournio          #+#    #+#             */
/*   Updated: 2021/02/26 15:36:53 by sfournio         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	tex_main(t_global *global, t_tmptex *tmp)
{
	tex_calc(global, tmp);
	if (tmp->side == 0)
		tmp->perpwalldist = (tmp->mapx - global->wind->posx + (1 - tmp->stepx)
							/ 2) / tmp->raydirx;
	else
		tmp->perpwalldist = (tmp->mapy - global->wind->posy + (1 - tmp->stepy)
							/ 2) / tmp->raydiry;
	tmp->lineheight = (int)(global->wind->h / tmp->perpwalldist);
	tmp->drawstart = -tmp->lineheight / 2 + global->wind->h / 2;
	if (tmp->drawstart < 0)
		tmp->drawstart = 0;
	tmp->drawend = tmp->lineheight / 2 + global->wind->h / 2;
	if (tmp->drawend >= global->wind->h)
		tmp->drawend = global->wind->h - 1;
	tmp->texnum = find_textnum(tmp->side, tmp->raydirx, tmp->raydiry);
	if (tmp->side == 0)
		tmp->wallx = global->wind->posy + tmp->perpwalldist * tmp->raydiry;
	else
		tmp->wallx = global->wind->posx + tmp->perpwalldist * tmp->raydirx;
	tmp->wallx -= floor((tmp->wallx));
	tmp->texx = (int)(tmp->wallx * (double)global->img[tmp->texnum].w);
	if (tmp->side == 0 && tmp->raydirx > 0)
		tmp->texx = global->img[tmp->texnum].w - tmp->texx - 1;
	if (tmp->side == 1 && tmp->raydiry < 0)
		tmp->texx = global->img[tmp->texnum].w - tmp->texx - 1;
}

void	prog(t_global *global)
{
	t_tmptex	tmp;
	double		zbuffer[global->size_x];
	int			*spriteorder;
	int			i;

	if (!(spriteorder = malloc(sizeof(int) * global->nbsprites)))
		exit_free(global, -1);
	while (global->wind->x < global->wind->w)
	{
		tex_main(global, &tmp);
		tmp.step = 1.0 * global->img[tmp.texnum].h / tmp.lineheight;
		tmp.texpos = (tmp.drawstart - global->wind->h / 2 + tmp.lineheight / 2)
					* tmp.step;
		tex_drawer(global, &tmp, global->wind->x, 0);
		zbuffer[global->wind->x] = tmp.perpwalldist;
		global->wind->x += 1;
	}
	spriteorder = sortsprites(global, spriteorder);
	i = -1;
	while (++i < global->nbsprites)
	{
		sprite_calc(global, &tmp, spriteorder, i);
		sprite_drawer(global, &tmp, zbuffer, tmp.drawstartx - 1);
	}
	free(spriteorder);
}

int		gameloop(t_global *global)
{
	if (global->wind->key_w == 1)
		key_w(global);
	if (global->wind->key_a == 1)
		key_a(global);
	if (global->wind->key_s == 1)
		key_s(global);
	if (global->wind->key_d == 1)
		key_d(global);
	if (global->wind->key_r == 1)
		key_right(global);
	if (global->wind->key_l == 1)
		key_left(global);
	global->wind->x = 0;
	global->wind->img = mlx_new_image(global->wind->mlx, global->size_x,
						global->size_y);
	global->wind->addr = (int*)mlx_get_data_addr(global->wind->img,
						&global->wind->bits_per_pixel,
						&global->wind->line_length, &global->wind->endian);
	prog(global);
	mlx_clear_window(global->wind->mlx, global->wind->win);
	mlx_put_image_to_window(global->wind->mlx, global->wind->win,
		global->wind->img, 0, 0);
	hud_draw(global);
	mlx_destroy_image(global->wind->mlx, global->wind->img);
	return (0);
}

void	img_gen(t_global *global, int i)
{
	if (!(global->img = malloc(sizeof(t_xpm) * 5)))
		exit_free(global, -1);
	global->img[0].img = mlx_xpm_file_to_image(global->wind->mlx,
		global->lol->no, &global->img[0].w, &global->img[0].h);
	global->img[1].img = mlx_xpm_file_to_image(global->wind->mlx,
		global->lol->so, &global->img[1].w, &global->img[1].h);
	global->img[2].img = mlx_xpm_file_to_image(global->wind->mlx,
		global->lol->ea, &global->img[2].w, &global->img[2].h);
	global->img[3].img = mlx_xpm_file_to_image(global->wind->mlx,
		global->lol->we, &global->img[3].w, &global->img[3].h);
	global->img[4].img = mlx_xpm_file_to_image(global->wind->mlx,
		global->lol->s, &global->img[4].w, &global->img[4].h);
	while (++i < 5)
		global->img[i].addr = (int *)mlx_get_data_addr(global->img[i].img,
			&global->img[i].bytes, &global->img[i].sizeline,
				&global->img[i].endian);
}

void	open_window(t_global *global)
{
	t_window	wind;

	global->wind = &wind;
	global->wind->mlx = mlx_init();
	global->wind->win = mlx_new_window(global->wind->mlx, global->size_x,
		global->size_y, "Cub3d");
	img_gen(global, -1);
	init_window(global);
	if (global->save == 1)
	{
		gameloop(global);
		screen(global);
		exit_free(global, -1);
	}
	gameloop(global);
	mlx_hook(global->wind->win, 17, 1L << 1, close_button, global);
	mlx_hook(global->wind->win, 2, 1L << 0, keypress, global);
	mlx_hook(global->wind->win, 3, 1L << 1, cancel, global);
	mlx_loop_hook(global->wind->mlx, gameloop, global);
	mlx_loop(global->wind->mlx);
}
