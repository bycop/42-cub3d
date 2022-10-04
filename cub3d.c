/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:31:36 by bycop          #+#    #+#             */
/*   Updated: 2021/02/28 13:33:02 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_free(t_global *global, int i)
{
	free(global->lol->no);
	free(global->lol->so);
	free(global->lol->ea);
	free(global->lol->we);
	free(global->lol->s);
	while (++i <= global->map_y)
		free(global->map[i]);
	free(global->map);
	free(global->img);
	free(global->sprites);
	free(global);
	exit(EXIT_SUCCESS);
}

int		error_log(int type)
{
	if (type == 0)
		write(1, "ERROR\nYou need to verify the launch arguments.\n", 47);
	if (type == 1)
		write(1, "ERROR\nMap not valid.\n", 21);
	if (type == 2)
		write(1, "ERROR\nNo wall around the map.\n", 30);
	if (type == 3)
		write(1, "ERROR\nNo only one spawn position found.\n", 40);
	if (type == 4)
		write(1, "ERROR\nOne or more information not found.\n", 41);
	if (type == 5)
		write(1, "ERROR\nOne or more .xpm textures not found.\n", 43);
	if (type == 6)
		write(1, "ERROR\nSpace on the game zone.\n", 30);
	if (type == 7)
		write(1, "ERROR\nRGB colors need to be between 0 and 255.\n", 47);
	if (type == 8)
		write(1, "ERROR\nInput Error.\n", 19);
	return (-1);
}

int		main(int argc, char **argv)
{
	t_global	*global;
	t_texture	texture;
	void		*mlx;
	int			fd;

	mlx = NULL;
	if (!(global = malloc(sizeof(t_global))))
		exit(EXIT_SUCCESS);
	global->lol = &texture;
	ft_init(mlx, global);
	if ((fd = args_verif(global, argv, argc)) < 0)
		exit_free(global, -1);
	if (ft_parser(fd, global, 0) == -1 || struct_verif(global) == -1)
		exit_free(global, -1);
	sprites_found(global);
	open_window(global);
	exit_free(global, -1);
}
