/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 12:58:27 by imasayos          #+#    #+#             */
/*   Updated: 2023/05/03 22:46:53 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	while (*s++ != '\0')
		cnt++;
	return (cnt);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	cnt;

	if (src == NULL)
		return (0);
	cnt = ft_strlen(src);
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

char	*ft_strchr(const char *s, int c)
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

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*ptr;
	size_t	i;
	size_t	j;

	if (s1 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
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
