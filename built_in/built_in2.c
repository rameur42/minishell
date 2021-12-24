/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:54:38 by tgresle           #+#    #+#             */
/*   Updated: 2021/12/24 11:21:52 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	exec_exit(t_struct *cfg)
{
	ft_lstclear(&cfg->env);
	if (cfg->exp != NULL)
		ft_lstclear(&cfg->exp);
	printf("exit\n");
	exit (0);
}

void	exec_echo(char **cmd)
{
	int	i;
	int	f;

	i = 1;
	if (cmd[1] && ft_strcmp(cmd[1], "-n") == 0)
	{
		f = 1;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (f != 1)
		printf("\n");
}

void	exec_pwd(void)
{
	char	*loc;

	loc = NULL;
	loc = getcwd(loc, 1024);
	if (loc != NULL)
		printf("%s\n", loc);
	else
		printf("Error\n");
	free(loc);
}

void	ft_refresh_pwd(t_struct *cfg, int mode)
{
	ft_modif_pwd(cfg->env, mode);
	if (cfg->exp != NULL)
		ft_modif_pwd(cfg->exp, mode);
}
