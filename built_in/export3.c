/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:44:31 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/13 22:18:14 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_is_already(char *s, t_list *lst)
{
	int		i;
	t_list	*tmp;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		i = 0;
		if (s[i] == tmp->content[i])
		{
			while (s[i] && tmp->content[i] && s[i] == tmp->content[i]
				&& tmp->content[i] != '=' && s[i] != '+' && s[i] != '=')
				i++;
			if ((!(s[i]) && (!(tmp->content[i]) || tmp->content[i] == '='))
				|| (s[i] && s[i] == '=' && (!(tmp->content[i])
						|| tmp->content[i] == '=')) || (s[i]
					&& tmp->content[i - 1] && s[i - 1]
					&& tmp->content[i - 1] == s[i - 1] && s[i] == '+'
					&& s[i + 1] && s[i + 1] == '='
					&& (!(tmp->content[i]) || tmp->content[i] == '=')))
				return (1);
		}
		tmp = tmp->next;
	}
	return (-1);
}

int	ft_is_same(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (ft_len_env(s2, 0) == ft_len_env(s1, 0))
		return (0);
	return (1);
}

int	ft_is_to_add(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '+')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] && s1[i] == '+' && s1[i + 1] && s1[i + 1] == '=')
		return (1);
	return (0);
}

void	ft_join_norm(char *str, char *s1, int *i, int *check)
{
	while (s1 && s1[(*i)])
	{
		str[(*i)] = s1[(*i)];
		if (s1[(*i)] == '=')
			*check = 1;
		(*i)++;
	}
	if (*check == 0)
	{
		str[(*i)] = '=';
		(*i)++;
	}
}

char	*ft_strjoin_export2(char *s1, char *s2, int k)
{
	int		i;
	int		j;
	int		check;
	char	*str;

	i = 0;
	j = 0;
	check = 0;
	str = 0;
	str = malloc(sizeof(char) * k + 1);
	if (!(str))
		return (0);
	ft_join_norm(str, s1, &i, &check);
	while (s2 && s2[j] && s2[j] != '=')
		j++;
	j++;
	while (s2 && s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
