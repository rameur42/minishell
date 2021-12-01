/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:21:53 by reda              #+#    #+#             */
/*   Updated: 2021/12/01 06:11:07 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_get_env(char **env, t_struct *cfg)
{
	int i;

	i = 0;
	//printf("hello there\n");
	while(env[i] != NULL)
	{
		ft_lstadd_back(&cfg->env, ft_lstnew(ft_strdup(env[i]), 0, 0, 0));
		i++;
	}
	cfg->path = split_path(env);
	cfg->path[0] = ft_rm_p(cfg->path[0]);
	i = 0;
	while (cfg->path[i])
	{
		cfg->path[i] = ft_strjoin(cfg->path[i], "/", 1);
		//printf("path->%s\n", cfg->path[i]);
		i++;
	}
}

void	print_env(t_struct *cfg)
{
	t_list *tmp;

	tmp = cfg->env;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

void	ft_handler(int sign)
{
	//printf("\nsignal-->%d\n", sign);
	if (sign == 2)
	{
		printf("\nminishell> ");
	}
	else if (sign == 3)
		printf("\b\b");
}

/*void	ft_signals()
{
	struct sigaction sig;

	sig.sa_handler = &ft_handler;
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, 0);
	sigaction(SIGQUIT, &sig, 0);
}*/

int	main(int ac, char **av, char **env)
{
	t_struct cfg;
	char *str;

	str = NULL;
	cfg.env = NULL;
	cfg.arg = NULL;
	cfg.pipe = -1;
	(void)av;
	//ft_signals();
	if (ac == 1)
	{
		ft_get_env(env, &cfg);
		//print_env(&cfg);
		while (1)
		{
			str = readline("minishell> ");
			add_history(str);
			if (ft_parse_line(&cfg, str) == 1)
				ft_lstclear(&cfg.arg);
			if (ft_init_count_pipe(&cfg) == 1)
				return (0);
			ft_is_file(&cfg);
			//ft_print_lst(&cfg);
			ft_exec(&cfg);
			if (ft_strcmp(str, "exit") == 0)
				return (0);
			ft_lstclear(&cfg.arg);
			if (str)
				free (str);
			str = NULL;
		}
	}
	return (0);
}