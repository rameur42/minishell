/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 22:47:03 by rameur            #+#    #+#             */
/*   Updated: 2021/07/26 22:51:29 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char *ft_strdup(char *str)
{
	int i;
	char *res;

	i = 0;
	res = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	res[ft_strlen(str)] = '\0';
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	return (res);
}