/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 12:58:27 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/19 04:09:38 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	cnt;

	cnt = 0;
	while (*s++ != '\0')
		cnt++;
	return (cnt);
}

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	cnt;

	if (src == NULL)
		return (0);
	cnt = ft_strlen_gnl(src);
	if (size == 0)
		return (cnt);
	i = 0;
	while (i < size - 1 && i < cnt)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (cnt);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*ptr;
	size_t	i;
	size_t	j;

	if (s1 == NULL)
		return (NULL);
	len_s1 = ft_strlen_gnl(s1);
	len_s2 = ft_strlen_gnl(s2);
	ptr = malloc(len_s1 + len_s2 + 1);
	if (ptr == NULL)
		return (free_buf(s1, s2));
	i = -1;
	j = 0;
	while (++i < len_s1)
		ptr[i] = s1[i];
	while (i < len_s1 + len_s2)
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	free_buf(s1, s2);
	return (ptr);
}
