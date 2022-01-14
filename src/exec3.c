/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:45:58 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/14 13:31:21 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_free_str(char *str)
{
	if (str)
		free(str);
	str = NULL;
}

void	ft_incr_shlvl(t_struct *cfg)
{
	int		i;
	int		shlvl;
	char	*buff;

	i = 0;
	shlvl = 0;
	buff = NULL;
	while (cfg->tab_env[i])
	{
		if (strncmp("SHLVL", cfg->tab_env[i], 4) == 0)
		{
			shlvl = ft_atoi(cfg->tab_env[i]);
			shlvl++;
			buff = ft_itoa(shlvl);
			free(cfg->tab_env[i]);
			cfg->tab_env[i] = ft_strjoin("SHLVL=", buff, 0);
			free(buff);
			return ;
		}
		i++;
	}
}

void	ft_get_path(t_struct *cfg, char **cmd)
{
	struct stat	buff;
	int			i;
	int			ret;
	char		*buffer;

	i = 0;
	ret = -1;
	buffer = NULL;
	split_path(cfg);
	if (cfg->path == NULL)
		return ;
	while (cfg->path[i] && ret != 0)
	{
		buffer = ft_strjoin(cfg->path[i], "/", 0);
		buffer = ft_strjoin(buffer, cmd[0], 1);
		ret = stat(buffer, &buff);
		if (ret == -1)
			free(buffer);
		i++;
	}
	if (ret == 0)
	{
		free(cmd[0]);
		cmd[0] = buffer;
	}
}

int	get_nb_cmd(t_struct *cfg)
{
	t_list	*tmp;
	int		res;

	tmp = cfg->arg;
	res = 0;
	while (tmp)
	{
		if (tmp->type == 9 || tmp->type == 0 || tmp->type == 11)
			res++;
		tmp = tmp->next;
	}
	return (res);
}

void	ft_exec_built_in(t_struct *cfg, t_list *tmp)
{
	if (ft_strcmp(tmp->content, "env") == 0)
		print_lst(cfg->env);
	else if (ft_strcmp(tmp->content, "pwd") == 0)
		exec_pwd();
	else if (ft_strcmp(tmp->content, "echo") == 0)
		exec_echo(tmp);
	else if (ft_strcmp(tmp->content, "exit") == 0)
		exec_exit(cfg, tmp);
}
