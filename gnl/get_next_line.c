/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 12:58:17 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/19 04:09:10 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*split_buf(char *buf, char *n_pos, char *rst, char *new_buf)
{
	char	*rtn;

	free(new_buf);
	rtn = malloc(n_pos - buf + 2);
	if (rtn == NULL)
	{
		if (buf != NULL)
			free(buf);
		return (NULL);
	}
	ft_strlcpy_gnl(rtn, buf, n_pos - buf + 2);
	ft_strlcpy_gnl(rst, n_pos + 1, ft_strlen_gnl(n_pos + 1) + 1);
	if (buf != NULL)
		free(buf);
	return (rtn);
}

char	*free_buf(char *buf, char *new_buf)
{
	if (buf != NULL)
		free(buf);
	if (new_buf != NULL)
		free(new_buf);
	return (NULL);
}

char	*loop(int fd, char *rst, char *buf)
{
	ssize_t	sc;
	char	*n_pos;
	char	*new_buf;

	while (buf != NULL)
	{
		new_buf = malloc(BUFFER_SIZE + (size_t)1);
		if (new_buf == NULL)
			return (free_buf(buf, new_buf));
		n_pos = ft_strchr_gnl(buf, '\n');
		if (n_pos != NULL)
			return (split_buf(buf, n_pos, rst, new_buf));
		sc = read(fd, new_buf, BUFFER_SIZE);
		if (sc < 0 || (sc == 0 && *buf == '\0'))
			return (free_buf(buf, new_buf));
		if (sc == 0)
		{
			free(new_buf);
			return (buf);
		}
		new_buf[sc] = '\0';
		buf = ft_strjoin_gnl(buf, new_buf);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	rst[OPEN_MAX + (size_t)1][BUFFER_SIZE + (size_t)1];
	char		*buf;

	if (BUFFER_SIZE < 0 || INT_MAX < BUFFER_SIZE || fd < 0 || OPEN_MAX < fd)
		return (NULL);
	buf = malloc(BUFFER_SIZE + (size_t)1);
	if (buf == NULL)
		return (NULL);
	ft_strlcpy_gnl(buf, &rst[fd][0], ft_strlen_gnl(&rst[fd][0]) + 1);
	rst[fd][0] = '\0';
	return (loop(fd, &rst[fd][0], buf));
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q gnl.a");
// }

// #include <fcntl.h>
// #include <stdio.h>

// int	main(int argc, char const *argv[])
// {
// 	ssize_t	fd;
// 	char	*gnl;

// 	(void)argc;
// 	fd = open(argv[1], O_RDONLY);
// 	for (int i = 0; i < 15; i++)
// 	{
// 		gnl = get_next_line(fd);
// 		if (gnl != NULL)
// 		{
// 			write(1, gnl, ft_strlen(gnl));
// 			free(gnl);
// 		}
// 	}
// 	// write(1, "\n", 1);
// 	close(fd);
// 	return (0);
// }
