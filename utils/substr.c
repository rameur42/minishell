/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 23:06:13 by rameur            #+#    #+#             */
/*   Updated: 2021/12/24 11:46:32 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*ft_substr(char *s, int start, int len)
{
	char	*res;
	int		i;

	i = 0;
	if (!(s) || start >= len)
		return (NULL);
	res = malloc(sizeof(char) * len + 1);
	if (!(res))
		return (NULL);
	if (ft_strlen(s) > start)
	{
		while (s[start] && i < len)
		{
			res[i] = s[start];
			i++;
			start++;
		}
	}
	res[i] = '\0';
	return (res);
}
