/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 07:09:41 by bycop          #+#    #+#             */
/*   Updated: 2021/01/08 11:56:14 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		find(const char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] != c)
		return (-1);
	return (i);
}

int		copy_line(char *str, char **line, int i)
{
	*line = ft_substr(str, 0, i);
	++i;
	ft_memcpy(str, str + i, ft_strlen(str + i) + 1);
	return (1);
}

char	*join_free(char *s1, char *s2)
{
	int		len1;
	int		len2;
	char	*dst;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(dst = (char*)malloc((len1 + len2 + 1) * sizeof(char))))
		return (NULL);
	ft_memcpy(dst, s1, len1);
	free(s1);
	s1 = NULL;
	ft_memcpy(dst + len1, s2, len2);
	dst[len1 + len2] = '\0';
	return (dst);
}

int		get_next_line(int fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	static char		*str = NULL;
	int				ret;
	int				i;

	if (!line || fd < 0 || BUFFER_SIZE < 1 || read(fd, buff, 0) < 0)
		return (-1);
	if (str && (i = find(str, '\n')) != -1)
		return (copy_line(str, line, i));
	while (((ret = read(fd, buff, BUFFER_SIZE)) > 0))
	{
		buff[ret] = '\0';
		str = join_free(str, buff);
		if ((i = find(str, '\n')) != -1)
			return (copy_line(str, line, i));
	}
	if (str)
	{
		*line = ft_strdup(str);
		free(str);
		str = NULL;
		return (1);
	}
	*line = ft_strdup("");
	return (ret);
}
