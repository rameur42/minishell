/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:05:08 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/13 22:11:44 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_is_absolute(char *path)
{
	if (path && path[0] == '/')
		return (1);
	return (0);
}

void	ft_use_absolute(t_struct *cfg, char *path)
{
	struct stat	buff;

	buff.st_mode = 0;
	stat(path, &buff);
	if (buff.st_mode == 16877)
		ft_refresh_pwd(cfg, 1);
	if (chdir(path) != 0)
		printf("minishell: cd: %s: No such file or directory\n", path);
	else
		ft_refresh_pwd(cfg, 2);
}

void	exec_cd_norm(t_list *tmp, t_struct *cfg)
{
	char	*buff;

	buff = NULL;
	while (tmp)
	{
		if (ft_strncmp("HOME", tmp->content, 4) == 0)
		{
			ft_refresh_pwd(cfg, 1);
			buff = ft_substr(tmp->content, 5, ft_strlen(tmp->content));
			chdir(buff);
			ft_refresh_pwd(cfg, 2);
			free(buff);
			return ;
		}
		tmp = tmp->next;
	}
	printf("minishell: cd: HOME not set\n");
}

void	exec_cd_norm2(t_struct *cfg, char **path)
{
	char		*buffer;
	char		*go_to;
	struct stat	buff;

	buffer = NULL;
	buff.st_mode = (unsigned int)0;
	buffer = getcwd(buffer, 1024);
	buffer = ft_strjoin(buffer, "/", 1);
	go_to = ft_strjoin(buffer, path[1], 0);
	stat(go_to, &buff);
	if (buff.st_mode == 16877)
		ft_refresh_pwd(cfg, 1);
	if (chdir(go_to) != 0)
		printf("minishell: cd: %s: No such file or directory\n", path[1]);
	else
		ft_refresh_pwd(cfg, 2);
	free(buffer);
	free(go_to);
}

void	exec_cd(t_struct *cfg, char **path)
{
	int			i;
	t_list		*tmp;

	i = 0;
	tmp = cfg->env;
	while (path[i])
		i++;
	if (i > 2)
		return ;
	else if (i == 1 || (i == 2 && ft_strcmp(path[1], "~") == 0))
		exec_cd_norm(tmp, cfg);
	else if (ft_is_absolute(path[1]))
		ft_use_absolute(cfg, path[1]);
	else
		exec_cd_norm2(cfg, path);
}
