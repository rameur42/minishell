/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:21:53 by reda              #+#    #+#             */
/*   Updated: 2022/01/10 15:20:19 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_get_env(char **env, t_struct *cfg)
{
	int	i;
	char *buff;
	char *pwd;

	i = 0;
	pwd = NULL;
	if ((*env) == NULL)
	{	
		pwd = getcwd(pwd, 1024);
		buff = ft_strjoin("PWD=", pwd, 0);
		ft_lstadd_back(&cfg->env, ft_lstnew(ft_strdup(buff), 0, 0));
		ft_lstadd_back(&cfg->env, ft_lstnew(ft_strdup("SHLVL=1"), 0, 0));
		free(pwd);
		free(buff);
		return (0);
	}
	while (env && env[i] != NULL)
	{
		ft_lstadd_back(&cfg->env, ft_lstnew(ft_strdup(env[i]), 0, 0));
		i++;
	}
	//cfg->path = split_path(env);
	if (cfg->path == NULL)
		return (0);
	cfg->path[0] = ft_rm_p(cfg->path[0]);
	i = 0;
	while (cfg->path[i])
	{
		cfg->path[i] = ft_strjoin(cfg->path[i], "/", 1);
		//printf("path->%s\n", cfg->path[i]);
		i++;
	}
	return (0);
}

void	print_lst(t_list *tmp)
{
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

int	is_redir(int type)
{
	if (type >= 3 && type <= 6)
		return (1);
	return (0);
}

void	f_d_in(char *str)
{
	char *buff;

	while (1)
	{
		buff = readline(">");
		if (ft_strcmp(buff, str) == 0)
		{
			free(buff);
			return ;
		}
		free(buff);
	}
}

int	ft_set_redir(t_list *tmp)
{
	if (tmp->type == 3)
	{
		if (tmp->prev && (tmp->prev->type != 0 && tmp->prev->type != 9 &&
				tmp->prev->type != 11 && tmp->prev->type != 2))
		{
			printf("syntax error near unexpected token '%s'\n", tmp->prev->content);
			return (1);
		}
		if (tmp->next && (tmp->next->type == 0 || tmp->next->type == 9 ||
				tmp->next->type == 11 || tmp->next->type == 2))
		{
			tmp->fd = open(tmp->next->content, O_TRUNC | O_WRONLY
					| O_CREAT, 0644);
			tmp->next->type = 2;
		}
		else if (tmp->next)
		{
			printf("syntax error near unexpected token '%s'\n", tmp->next->content);
			return (1);
		}
		else
		{
			printf("syntax error near unexpected token `newline'\n");
			return (1);
		}
	}
	else if (tmp->type == 4)
	{
		if (tmp->prev && (tmp->prev->type != 0 && tmp->prev->type != 9 &&
			tmp->prev->type != 11 && tmp->prev->type != 2))
		{
			printf("syntax error near unexpected token '%s'\n", tmp->prev->content);
			return (1);
		}
		if (tmp->next && (tmp->next->type == 0 || tmp->next->type == 9 ||
				tmp->next->type == 11 || tmp->next->type == 2))
		{
			tmp->fd = open(tmp->next->content, O_RDWR | O_CREAT | O_APPEND);
			tmp->next->type = 2;
		}
		else if (tmp->next)
		{
			printf("syntax error near unexpected token '%s'\n", tmp->next->content);
			return (1);
		}
		else
		{
			printf("syntax error near unexpected token `newline'\n");
			return (1);
		}
	}
	else if (tmp->type == 5)
	{
		if (tmp->prev && (tmp->prev->type != 0 && tmp->prev->type != 9 &&
			tmp->prev->type != 11 && tmp->prev->type != 2))
		{
			printf("syntax error near unexpected token '%s'\n", tmp->prev->content);
			return (1);
		}
		if (tmp->next && (tmp->next->type == 0 || tmp->next->type == 9 ||
				tmp->next->type == 11 || tmp->next->type == 2))
		{
			tmp->fd = open(tmp->next->content, O_RDONLY);
			tmp->next->type = 2;
		}
		else if (tmp->next)
		{
			printf("syntax error near unexpected token '%s'\n", tmp->next->content);
			return (1);
		}
		else
		{
			printf("syntax error near unexpected token `newline'\n");
			return (1);
		}
	}
	else if (tmp->type == 6)
	{
		if (tmp->prev && (tmp->prev->type != 0 && tmp->prev->type != 9 &&
			tmp->prev->type != 11 && tmp->prev->type != 2))
		{
			printf("syntax error near unexpected token '%s'\n", tmp->prev->content);
			return (1);
		}
		if (!tmp->prev && tmp->next && (tmp->next->type == 0 || tmp->next->type == 9 ||
				tmp->next->type == 11 || tmp->next->type == 2))
		{
			f_d_in(tmp->next->content);
			tmp->next->type = 2;
		}
		if (tmp->next && (tmp->next->type != 0 && tmp->next->type != 9 &&
				tmp->next->type != 11 && tmp->next->type != 2))
		{
			printf("syntax error near unexpected token '%s'\n", tmp->next->content);
			return (1);
		}
		else if (tmp->next)
			tmp->next->type = 2;
	}
	return (0);
}

int	ft_init_redir(t_struct *cfg)
{
	t_list *tmp;

	tmp = cfg->arg;
	while (tmp)
	{
		if (is_redir(tmp->type) == 1)
			if (ft_set_redir(tmp) == 1)
				return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_struct	cfg;
	char		*str;

	str = NULL;
	cfg.env = NULL;
	cfg.arg = NULL;
	cfg.exp = NULL;
	cfg.path = NULL;
	cfg.pipe = -1;
	cfg.sq = 0;
	cfg.dq = 0;
	cfg.en = 0;
	cfg.exit_code = 0;
	(void)av;
	//ft_display_tab(env);
	if (ac == 1)
	{
		if (ft_get_env(env, &cfg) == 1)
			return (1);
		//print_env(&cfg);
		while (1)
		{
			ft_signals();
			str = readline("minishell> ");
			if (str == NULL)
			{
				write(1, "\n", 1);
				break ;
			}
			else if (ft_strlen(str) == 0)
			{
				free(str);
				str = NULL;
			}
			/*else if (ft_strcmp(str, "exit") == 0)
			{
				if (str)
					free (str);
				exec_exit(&cfg);
			}*/
			else
			{
				add_history(str);
				if (ft_parse_line(&cfg, str) == 1)
					ft_lstclear(&cfg.arg);
				else
				{
					if (str)
						free (str);
					str = NULL;
					ft_var_env(&cfg);
					if (ft_init_count_pipe(&cfg) == 0 && ft_init_redir(&cfg) == 0)
					{
						ft_is_file(&cfg);
						ft_print_lst(&cfg);
						ft_exec(&cfg);
					}
					ft_lstclear(&cfg.arg);
				}
			}
			if (str)
				free (str);
			str = NULL;
		}
	}
	return (0);
}
