/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_int_color_from_base16.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:47:58 by imasayos          #+#    #+#             */
/*   Updated: 2023/07/23 22:43:10 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include "fdf.h"

static int	ft_isspace(int c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

static int trans_alpha_to_num(char *c)
{
	if ('0' <= *c && *c <= '9')
		return (*c - '0');
	else if ('A' <= *c && *c <= 'F')
		return (*c - 'A' + 10);
	else if ('a' <= *c && *c <= 'f')
		return (*c - 'a' + 10);
	else
		exit(1);
}

int	get_int_color_from_base16(char *nptr)
{
	int num;

	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '0')
		nptr++;
	else
		exit(1);
	if (*nptr == 'x')
		nptr++;
	else
		exit(1);
	num = 0;
	while (('0' <= *nptr && *nptr <= '9') || ('A' <= *nptr && *nptr <= 'F') || ('a' <= *nptr && *nptr <= 'f'))
	{
		num = num * 16 + trans_alpha_to_num(nptr);
		nptr++;
	}
	return (num);
}

// int main(void)
// {
// 	//0x00FF0000
// 	int num;
// 	num = ft_atoi_base16("0x00FF0000");
// 	printf("%d\n", num);
// 	return 0;
// }
