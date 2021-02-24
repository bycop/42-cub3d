/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournio <sfournio@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 17:37:28 by sfournio          #+#    #+#             */
/*   Updated: 2020/11/23 02:14:31 by sfournio         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *res;

	if (!s)
		return (NULL);
	if (start > ft_strlen((char *)s))
		return ((char *)ft_calloc(1, '\0'));
	if (!(res = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_memcpy(res, s + start, len);
	res[len] = '\0';
	return (res);
}
