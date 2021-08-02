/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:21:53 by reda              #+#    #+#             */
/*   Updated: 2021/07/26 23:01:47 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_get_env(char **env, t_struct *cfg)
{
	int i;

	i = 0;
	while(env[i] != NULL)
	{
		ft_lstadd_back(&cfg->env, ft_lstnew(ft_strdup(env[i])));
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

int	main(int ac, char **av, char **env)
{
	t_struct cfg;
	char *str;

	str = NULL;
	(void)av;
	if (ac == 1)
	{
		ft_get_env(env, &cfg);
		//print_env(&cfg);
		while (1)
		{
			str = readline("minishell>");
			printf("str -> %s\n", str);
			if (ft_strcmp(str, "exit") == 0)
				return (0);
			if (str)
				free (str);
			str = NULL;
		}
	}
	return (0);
}