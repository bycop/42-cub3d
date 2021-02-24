/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournio <sfournio@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:31:08 by sfournio          #+#    #+#             */
/*   Updated: 2021/02/24 14:06:22 by sfournio         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx_mms_20200219/mlx.h"
# define KEY_W 13
# define KEY_A 0
# define KEY_D 2
# define KEY_S 1
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_ESCAPE 53
# define KEY_SHIFT 257
# define MOV_SPEED 0.07
# define ROT_SPEED 0.05

typedef struct	s_texture
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	int			c[3];
	int			f[3];
	int			neg;
	int			dno;
	int			dso;
	int			dwe;
	int			dea;
	int			ds;
	int			dc;
	int			df;
	int			dr;
	int			clamap;
}				t_texture;

typedef struct	s_sprites
{
	double		x;
	double		y;
	int			dist;
	int			order;
}				t_sprites;

typedef struct	s_bmp
{
	int			file_size;
	int			header_size;
	int			bytes_size;
	int			image_size;
	int			planes;
	int			bytes_number;
	char		header[54];
}				t_bmp;

typedef struct	s_xpm
{
	void	*img;
	int		*addr;
	int		w;
	int		h;
	int		endian;
	int		bytes;
	int		sizeline;
}				t_xpm;

typedef struct	s_window {
	void		*mlx;
	void		*win;
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			x;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		w;
	double		h;
	int			key_r;
	int			key_l;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_shift;
}				t_window;

typedef struct	s_tmptex
{
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	double		step;
	double		texpos;
	int			texx;
	int			texnum;
	double		wallx;
	int			lineheight;
	int			drawstart;
	int			drawend;
	double		perpwalldist;
	double		spritex;
	double		spritey;
	double		invdet;
	double		transformx;
	double		transformy;
	int			spritescreenx;
	int			spriteheight;
	int			spritewidth;
	int			drawstartx;
	int			drawstarty;
	int			drawendx;
	int			drawendy;
	int			t;
}				t_tmptex;

typedef struct	s_global
{
	int			size_x;
	int			size_y;
	int			max_x;
	int			max_y;
	int			spawn_x;
	int			spawn_y;
	int			save;
	char		spawn;
	char		**map;
	int			*mapint;
	int			sizeint;
	int			map_y;
	int			map_x;
	int			nbsprites;
	int			intmax;
	t_window	*wind;
	t_texture	*lol;
	t_sprites	*sprites;
	t_xpm		*img;
}				t_global;
/*
**	Mlx + Algo
*/
void			open_window(t_global *global);
void			init_window(t_global *global);
void			found_dir(t_global *global);
int				gameloop(t_global *global);
void			prog(t_global *global);
int				find_textnum(int side, double raydirx, double raydiry);
int				*sortsprites(t_global *global, int *spriteorder);
void			screen(t_global *global);
void			header2(t_bmp *header, t_global *global);
void			found_step(t_global *global, t_tmptex *tmp);
void			tex_calc(t_global *global, t_tmptex *tmp);
void			tex_drawer(t_global *global, t_tmptex *tmp, int t, int y);
void			sprite_calc(t_global *global, t_tmptex *tmp, int *spriteorder,
				int i);
void			sprite_drawer(t_global *global, t_tmptex *tmp, double *zbuffer,
				int s);

/*
**	Keypress + Hooks
*/
int				keypress(int keycode, t_global *global);
int				cancel(int keycode, t_global *global);
int				key_w(t_global *global);
int				key_s(t_global *global);
int				key_a(t_global *global);
int				key_d(t_global *global);
int				key_left(t_global *global);
int				key_right(t_global *global);
int				key_escape(t_global *global);
int				close_button(t_global *global);

/*
**	Init and close
*/
void			ft_init(void *mlx, t_global *global);
void			exit_free(t_global *global, int i);

/*
**	UTILS
*/
void			skip_spaces(char *str, int *index, int type);
int				digit_max(char *str, int i);
int				path_max(char *str, int i);
int				spaces_count(char *str);
int				is_map_char(char c);
char			**ft_strsjoin(char **s1, char *s2);

/*
**	PARSING
*/
int				ft_parser(int fd, t_global *global, int ret);
int				ft_parser2(t_global *global, char *str, int ret);
int				case_no(char *str, t_global *global);
int				case_so(char *str, t_global *global);
int				case_ea(char *str, t_global *global);
int				case_we(char *str, t_global *global);
int				case_s(char *str, t_global *global);
int				case_r(char *str, t_global *global, int i, long res);
int				case_f(char *str, t_global *global, int j, int res);
int				case_c(char *str, t_global *global, int j, int res);
int				case_map(char *str, t_global *global);
int				sprites_found(t_global *global);
void			spawn_map(int j, t_global *global, char *str);

/*
**	ERRORS
*/
int				error_log(int type);
int				struct_verif(t_global *global);
int				map_verif(t_global *global, int i, int j);
int				texture_verif(t_global *global);
int				args_verif(t_global *global, char **argv, int argc);

#endif
