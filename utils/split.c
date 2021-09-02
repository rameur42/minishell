/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 22:56:04 by rameur            #+#    #+#             */
/*   Updated: 2021/08/24 22:56:14 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	ft_check(const char to_check, char c)
{
	if (to_check == c || to_check == '\0')
		return (1);
	else
		return (0);
}

static int	is_word(const char *str, char c, int i)
{
	if (i == 0 && ft_check(str[i], c) == 0)
		return (1);
	else if (ft_check(str[i], c) == 0 && (ft_check(str[i - 1], c) == 1))
		return (1);
	else
		return (0);
}

static int	ft_cmp_w(const char *str, char c)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (is_word(str, c, i))
			res++;
		i++;
	}
	return (res);
}

static int	ft_compteur_l(const char *str, char c, int i)
{
	int	res;

	res = 0;
	while (ft_check(str[i], c) == 0 && str[i] != '\0')
	{
		i++;
		res++;
	}
	return (res);
}

char	**ft_split(const char *s, char c)
{
	int		i[3];
	char	**res;

	i[0] = 0;
	i[1] = 0;
	res = (char **)malloc((ft_cmp_w(s, c) + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	while (s[i[0]])
	{
		if (is_word(s, c, i[0]) == 1)
		{
			i[2] = 0;
			res[i[1]] = malloc((ft_compteur_l(s, c, i[0]) + 1));
			if (res[i[1]] == NULL)
				return (ft_free_s(res, i[1]));
			while (ft_check(s[i[0]], c) == 0)
				res[i[1]][i[2]++] = s[i[0]++];
			res[i[1]++][i[2]] = '\0';
		}
		else
			i[0]++;
	}
	res[i[1]] = NULL;
	return (res);
}
