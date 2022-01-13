/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:32:37 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/13 17:57:18 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_refresh_pwd(t_struct *cfg, int mode)
{
	ft_modif_pwd(cfg->env, mode);
	if (cfg->exp != NULL)
		ft_modif_pwd(cfg->exp, mode);
}

int	check_exit(char *s)
{
	int	i;

	i = 0;
	if (s && s[i] && (s[i] == '-' || s[i] == '+'))
		i++;
	while (s && s[i])
	{
		if (s[i] < 48 || s[i] > 57)
		{
			printf("minishell: exit: %s: numeric argument required\n", s);
			return (1);
		}
		i++;
	}
	return (0);
}

void	control_exit_return(t_list *tmp, int *dont_exit)
{
	if (tmp->next && (tmp->next->type == 0 || tmp->next->type == 2
			|| tmp->next->type == 9 || tmp->next->type == 11))
	{
		tmp = tmp->next;
		if (check_exit(tmp->content) == 0)
		{
			if (tmp->next && (tmp->next->type == 0 || tmp->next->type == 2
					|| tmp->next->type == 9 || tmp->next->type == 11))
			{
				printf("minishell: exit: too many arguments\n");
				*dont_exit = 1;
			}
		}
	}
}

void	ft_modif_pwd_norm2(t_list *tmp, char *buff)
{
	free(tmp->content);
	buff = getcwd(buff, 1024);
	tmp->content = ft_strjoin("OLDPWD=", buff, 0);
	free(buff);
}
