/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 17:47:37 by rameur            #+#    #+#             */
/*   Updated: 2022/01/10 17:17:50 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	to_malloc(long n)
{
	int		i;

	i = 1;
	while (n > 9)
	{
		i++;
		n /= 10;
	}
	return (i);
}

void	itoa_norm(int *neg, long *res_l)
{
	*neg = 1;
	*res_l *= -1;
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		neg;
	long	res_l;

	res_l = (long)n;
	if (res_l < 0)
		itoa_norm(&neg, &res_l);
	else
		neg = 0;
	i = to_malloc(res_l) + neg;
	res = malloc((to_malloc(res_l) + neg + 1) * sizeof(char));
	if (!(res))
		return (NULL);
	res[i] = '\0';
	while (i > neg)
	{
		res[--i] = (res_l % 10) + '0';
		res_l /= 10;
	}
	if (neg == 1)
		res[0] = '-';
	return (res);
}
