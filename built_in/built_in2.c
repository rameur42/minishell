/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:22:43 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/14 13:03:54 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	exec_exit(t_struct *cfg, t_list *tmp)
{
	int		dont_exit;
	t_list	*temp;

	dont_exit = 0;
	temp = tmp;
	while (temp->next && dont_exit == 0)
	{
		if (temp->next->type == 1)
			dont_exit = 1;
		temp = temp->next;
	}
	control_exit_return(tmp, &dont_exit);
	if (dont_exit == 0)
	{
		ft_lstclear(&cfg->env);
		ft_lstclear(&cfg->arg);
		if (cfg->exp != NULL)
			ft_lstclear(&cfg->exp);
		if (cfg->path != NULL)
			ft_free_tab(cfg->path);
		printf("exit\n");
		exit (cfg->exit_code);
	}
}

void	exec_echo(t_list *tmp)
{
	int	i;
	int	f;
	int	first;

	i = 1;
	first = 0;
	f = 0;
	tmp = tmp->next;
	if (tmp && ft_strcmp(tmp->content, "-n") == 0)
	{
		f = 1;
		tmp = tmp->next;
	}
	while (tmp && (tmp->type == 2 || tmp->type == 0))
	{
		if (tmp->ps == 1 && first == 1)
			printf(" ");
		first = 1;
		printf("%s", tmp->content);
		tmp = tmp->next;
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

int	ft_modif_pwd_norm(t_list *tmp, char *buff)
{
	if (ft_is_same(tmp->content, "PWD") == 0)
	{
		free(tmp->content);
		buff = getcwd(buff, 1024);
		tmp->content = ft_strjoin("PWD=", buff, 0);
		free(buff);
		return (1);
	}
	return (0);
}

void	ft_modif_pwd(t_list *lst, int mode)
{
	t_list	*tmp;
	char	*buff;

	tmp = lst;
	buff = NULL;
	while (tmp)
	{
		if (mode == 1)
		{
			if (ft_is_same(tmp->content, "OLDPWD") == 0)
			{
				ft_modif_pwd_norm2(tmp, buff);
				return ;
			}
		}
		else if (mode == 2)
			if (ft_modif_pwd_norm(tmp, buff))
				return ;
		tmp = tmp->next;
	}
	if (mode == 1)
		ft_lstadd_back(&lst, ft_lstnew(ft_strjoin("OLDPWD=",
					getcwd(buff, 1024), 0), 0, 0, 0));
}
