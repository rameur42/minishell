/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgresle <tgresle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:54:35 by tgresle           #+#    #+#             */
/*   Updated: 2021/12/23 19:07:39 by tgresle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_modif_pwd(t_list *lst, int mode)
{
	t_list *tmp;
	char *buff;

	tmp = lst;
	buff = NULL;
	while (tmp)
	{
		if (mode == 1)
		{
			if (ft_is_same(tmp->content, "OLDPWD") == 0)
			{
				free(tmp->content);
				tmp->content = ft_strjoin("OLDPWD=", getcwd(buff, 1024), 0);
				free(buff);
				return ;
			}
		}
		else if (mode == 2)
		{
			if (ft_is_same(tmp->content, "PWD") == 0)
			{
				free(tmp->content);
				tmp->content = ft_strjoin("PWD=", getcwd(buff, 1024), 0);
				free(buff);
				return ;
			}
		}
		tmp = tmp->next;
	}
	if (mode == 1)
		ft_lstadd_back(&lst, ft_lstnew(ft_strjoin("OLDPWD=", getcwd(buff, 1024), 0), 0, 0, 0));
}

void	ft_refresh_pwd(t_struct *cfg, int mode)
{
	ft_modif_pwd(cfg->env, mode);
	if (cfg->exp != NULL)
		ft_modif_pwd(cfg->exp, mode);
}

void	exec_cd(t_struct *cfg, char **path)
{
    char	*buffer;
	char	*go_to;
	int		i;
	t_list *tmp;
	struct stat buff;

	i = 0;
	tmp = cfg->env;
	go_to = NULL;
	buffer = NULL;
	while (path[i])
		i++;
	if (i > 2)
		return ;
	else if (i == 1 || (i == 2 && ft_strcmp(path[1], "~") == 0))
	{
		while (tmp)
		{
			if (ft_strncmp("HOME", tmp->content, 4) == 0)
			{
				ft_refresh_pwd(cfg, 1);
				chdir(ft_substr(tmp->content, 5, ft_strlen(tmp->content)));
				ft_refresh_pwd(cfg, 2);
				return ;
			}
			tmp = tmp->next;
		}
		printf("minishell: cd: HOME not set\n");
		return ;
	}
	if (ft_strncmp("/mnt", path[1], 4) == 0)
	{
		chdir(path[1]);
		return ;
	}
	buffer = getcwd(buffer, 1024);
	buffer = ft_strjoin(buffer, "/", 1);
	go_to = ft_strjoin(buffer, path[1], 0);
	stat(go_to, &buff);
	if (buff.st_mode == 16877)
		ft_refresh_pwd(cfg, 1);
	//printf("stat->%d %u\n", stat(go_to, &buff), buff.st_mode);
	if (chdir(go_to) != 0)
		printf("minishell: cd: %s: No such file or directory\n", path[1]);
	else
		ft_refresh_pwd(cfg, 2);
	free(buffer);
	free(go_to);
}
