/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 21:14:23 by rameur            #+#    #+#             */
/*   Updated: 2022/01/11 20:07:19 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_len_env(char *s, int mode)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (mode == 1)
		if (s[i] == '=')
			i++;
	return (i);
}

void	ft_rm_one(t_list *tmp)
{
	if (tmp->prev != NULL)
		tmp->prev->next = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = tmp->prev;
	free(tmp->content);
	free(tmp);
}

int	set_var_norm(t_list *to_check, char *buff)
{
	if (ft_strlen(to_check->content) == 1)
	{
		to_check->type = 0;
		return (1);
	}
	else
	{
		buff = ft_substr(to_check->content, 1, ft_strlen(to_check->content));
		free(to_check->content);
		to_check->content = ft_strdup(buff);
		free(buff);
	}
	return (0);
}

void	set_var(t_struct *cfg, t_list *to_check)
{
	t_list	*tmp;
	char	*buff;

	tmp = cfg->env;
	buff = NULL;
	if (set_var_norm(to_check, buff))
		return ;
	while (tmp)
	{
		if (ft_is_same(tmp->content, to_check->content) == 0)
		{
			buff = ft_substr(tmp->content,
					ft_len_env(tmp->content, 1), ft_strlen(tmp->content));
			ft_tokenize_env(cfg, buff);
			//free(to_check->content);
			//free(to_check);
			
			/*free(to_check->content);
			to_check->content = ft_strdup(buff);
			free(buff);
			to_check->type = 0;*/
			printf("ICI\n");
			return ;
		}
		tmp = tmp->next;
	}
	ft_rm_one(to_check);
}

void	ft_f_arg(t_struct *cfg)
{
	t_list *tmp;
	t_list *buff;

	tmp = cfg->arg;
	buff = NULL;
	while (tmp->next)
	{
		if (tmp->next)
		{
			if (tmp->type == 0 && tmp->next->type == 0)
			{
				tmp->content = ft_strjoin(tmp->content, tmp->next->content, 1);
				buff = tmp->next;
				tmp->next = tmp->next->next;
				printf("WTF\n");
				if (tmp->next)
					tmp->next->prev = tmp;
				free(buff->content);
				free(buff);
			}
		}
		if (tmp->next)
			tmp = tmp->next;
	}
	printf("\n\n");
	print_lst(cfg->arg);
}

void	ft_var_env(t_struct *cfg)
{
	t_list	*tmp;

	tmp = cfg->arg;
	while (tmp)
	{
		if (tmp->type == 7)
		{
			set_var(cfg, tmp);
			printf("tmp->content=%s %s\n", tmp->content, tmp->prev->content);
			if (tmp->prev)
				tmp->prev->next = cfg->tenv;
			while (cfg->tenv->next)
				cfg->tenv = cfg->tenv->next;
			printf("cfg->tenv->%s\n", cfg->tenv->content);
			if (tmp->next)
			{
				tmp->next->prev = cfg->tenv;			
				cfg->tenv->next = tmp->next;
			}
			free(tmp->content);
			free(tmp);
			tmp = cfg->tenv;
			printf("||tenv->\n");
			print_lst(cfg->tenv);
			printf("||arg->\n");
			print_lst(cfg->arg);
			printf("||\n");
			ft_f_arg(cfg);
			cfg->tenv = NULL;
		}
		tmp = tmp->next;
	}
}
