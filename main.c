/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:21:53 by reda              #+#    #+#             */
/*   Updated: 2022/01/14 15:19:39 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_init_cfg(t_struct *cfg)
{
	cfg->env = NULL;
	cfg->arg = NULL;
	cfg->exp = NULL;
	cfg->path = NULL;
	cfg->tenv = NULL;
	cfg->tab_env = NULL;
	cfg->pipe = -1;
	cfg->sq = 0;
	cfg->dq = 0;
	cfg->en = 0;
	cfg->exit_code = 0;
}

int	is_invalid(t_struct *cfg)
{
	t_list	*tmp;

	tmp = cfg->arg;
	while (tmp)
	{
		if (tmp->type == 0)
		{
			printf("minishell: %s: command not found\n", tmp->content);
			cfg->exit_code = 127;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_to_exec(char *str, t_struct *cfg)
{
	add_history(str);
	if (ft_parse_line(cfg, str) == 1)
		ft_lstclear(&cfg->arg);
	else
	{
		ft_var_env(cfg);
		if (ft_init_count_pipe(cfg) == 0 && ft_init_redir(cfg) == 0)
		{
			ft_is_file(cfg);
			if (is_invalid(cfg) == 0)
				ft_exec(cfg);
		}
		ft_lstclear(&cfg->arg);
	}
}

int	ft_minishell(t_struct *cfg)
{
	char	*str;

	str = NULL;
	ft_signals();
	str = readline("minishell> ");
	if (str == NULL)
	{
		write(1, "\n", 1);
		ft_d_free(cfg);
		return (1);
	}
	else if (ft_strlen(str) == 0)
	{
		free(str);
		str = NULL;
	}
	else
		ft_to_exec(str, cfg);
	if (str)
		free (str);
	str = NULL;
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_struct	cfg;

	ft_init_cfg(&cfg);
	(void)av;
	if (ac == 1)
	{
		if (ft_get_env(env, &cfg) == 1)
			return (1);
		while (1)
		{
			if (ft_minishell(&cfg) == 1)
				break ;
		}
	}
	return (cfg.exit_code);
}
