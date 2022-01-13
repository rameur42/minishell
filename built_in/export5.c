/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:55:49 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/13 22:17:56 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_print_export_error(char *s, int i)
{
	if (i == 0)
		printf("minishell: export: `%s': not a valid identifier\n", s);
}

int	ft_check_export(char *s)
{
	int	i;

	i = 0;
	if (s && s[0] && (s[0] == '=' || s[0] == '+'))
		return (0);
	while (s && s[i] && s[i] != '=')
	{
		if ((s[0] && s[0] != '_' && (!(s[0] < 91 && s[0] > 64)
					&& !(s[0] < 123 && s[0] > 96)))
			|| (!(s[i] < 123 && s[i] > 96) && !(s[i] < 91 && s[i] > 64)
				&& !(s[i] < 58 && s[i] > 47) && s[i] != '_'
				&& s[i] != '=' && !(s[i] && s[i + 1]
					&& s[i] == '+' && s[i + 1] == '=')))
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_already_in(char *s, t_list *lst)
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

void	join_norm_2(char *s2, int *j, int *k)
{
	while (s2 && s2[(*j)] && s2[(*j)] != '=')
		(*j)++;
	(*j)++;
	while (s2 && s2[(*j)])
	{
		(*j)++;
		(*k)++;
	}
}

char	*ft_strjoin_export(char *s1, char *s2)
{
	int		i;
	int		j;
	int		k;
	int		check;
	char	*str;

	i = 0;
	j = 0;
	k = 0;
	check = 0;
	str = 0;
	while (s1 && s1[i] && s1[i])
	{
		if (s1[i] == '=')
			check = 1;
		i++;
		k++;
	}
	join_norm_2(s2, &j, &k);
	if (check == 0)
		k++;
	str = ft_strjoin_export2(s1, s2, k);
	free(s1);
	return (str);
}
