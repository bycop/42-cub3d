/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournio <sfournio@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:02:55 by sfournio          #+#    #+#             */
/*   Updated: 2021/02/26 14:35:55 by sfournio         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	header2(t_bmp *header, t_global *global)
{
	header->image_size = (((global->size_x * 32 + 31) / 32) * 4)
						* global->size_y;
	header->file_size = header->image_size + 54;
	header->header_size = 54;
	header->bytes_size = 40;
	header->planes = 1;
	header->bytes_number = 32;
	ft_memmove(header->header, "BM", 2);
	ft_memmove(header->header + 2, &header->file_size, 4);
	ft_memmove(header->header + 10, &header->header_size, 4);
	ft_memmove(header->header + 14, &header->bytes_size, 4);
	ft_memmove(header->header + 18, &global->size_x, 4);
	ft_memmove(header->header + 22, &global->size_y, 4);
	ft_memmove(header->header + 26, &header->planes, 4);
	ft_memmove(header->header + 28, &header->bytes_number, 4);
	ft_memmove(header->header + 34, &header->image_size, 4);
}

void	screen(t_global *global)
{
	int		fd;
	int		i;
	t_bmp	*header;

	if (!(header = ft_calloc(1, sizeof(*header))))
		exit_free(global, -1);
	i = global->size_y -3;
	fd = open("cub3d.bmp", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	header2(header, global);
	write(fd, header->header, 54);
	while (i != 0)
		write(fd, (int *)&global->wind->addr[(i-- *
			global->size_x)], global->size_x * 4);
	close(fd);
	free(header);
}
