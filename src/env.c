/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:19:58 by rameur            #+#    #+#             */
/*   Updated: 2022/01/13 21:23:37 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_no_env(t_struct *cfg)
{
	char	*buff;
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 1024);
	buff = ft_strjoin("PWD=", pwd, 0);
	ft_lstadd_back(&cfg->env, ft_lstnew(ft_strdup(buff), 0, 0, 0));
	ft_lstadd_back(&cfg->env, ft_lstnew(ft_strdup("SHLVL=1"), 0, 0, 0));
	free(pwd);
	free(buff);
	return (0);
}

int	ft_get_env(char **env, t_struct *cfg)
{
	int		i;

	i = 0;
	if ((*env) == NULL)
		return (ft_no_env(cfg));
	while (env && env[i] != NULL)
	{
		ft_lstadd_back(&cfg->env, ft_lstnew(ft_strdup(env[i]), 0, 0, 0));
		i++;
	}
	if (cfg->path == NULL)
		return (0);
	cfg->path[0] = ft_rm_p(cfg->path[0]);
	i = 0;
	while (cfg->path[i])
	{
		cfg->path[i] = ft_strjoin(cfg->path[i], "/", 1);
		i++;
	}
	return (0);
}

void	ft_d_free(t_struct *cfg)
{
	if (cfg->tab_env != NULL)
		ft_free_tab(cfg->tab_env);
	if (cfg->exp != NULL)
		ft_lstclear(&cfg->exp);
	if (cfg->path != NULL)
		ft_free_tab(cfg->path);
	if (cfg->arg != NULL)
		ft_lstclear(&cfg->arg);
	ft_lstclear(&cfg->env);
}
