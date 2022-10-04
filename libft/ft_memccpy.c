/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:46:01 by bycop          #+#    #+#             */
/*   Updated: 2020/11/23 02:13:21 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int ch, size_t size)
{
	size_t i;

	i = -1;
	while (++i < size)
		if ((((unsigned char *)dest)[i] = ((unsigned const char *)src)[i])
			== (unsigned char)ch)
			return (dest + i + 1);
	return (NULL);
}
