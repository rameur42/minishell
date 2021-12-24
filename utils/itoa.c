/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 17:47:37 by rameur            #+#    #+#             */
/*   Updated: 2021/12/24 11:45:11 by tgresle          ###   ########.fr       */
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

void	ft_itoa_norm(long *res_l, int *neg)
{
	if ((*res_l) < 0)
	{
		(*neg) = 1;
		(*res_l) *= -1;
	}
	else
		(*neg) = 0;
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		neg;
	long	res_l;

	res_l = (long)n;
	ft_itoa_norm(&res_l, &neg);
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
