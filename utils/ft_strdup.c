/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 22:47:03 by rameur            #+#    #+#             */
/*   Updated: 2022/01/13 20:31:06 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strdup_free(char *str)
{
	int		i;
	char	*res;

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
	free(str);
	return (res);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*res;

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

char	*ft_strjoin(char *s1, char *s2, int mode)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	if (!(s1) || !(s2))
		return (NULL);
	res = malloc((ft_strlen(s1)
				+ ft_strlen(s2) + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (s1[i])
		res[j++] = s1[i++];
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	if (mode == 1)
		free(s1);
	return (res);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (to_find == NULL || to_find[0] == '\0' || str == NULL)
		return (str);
	while (str[i + j])
	{
		if (str[i + j] == to_find[i])
			i++;
		else if (!(str[i + j] == to_find[i]))
		{
			j++;
			i = 0;
		}
		if (to_find[i] == '\0')
			return (&str[j]);
	}
	return (NULL);
}
