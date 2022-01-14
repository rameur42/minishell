/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:27:15 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/14 13:42:25 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	is_file_norm(t_list *tmp, int *is_cmd)
{
	if ((ft_strcmp(tmp->content, "cd") == 0
			|| ft_strcmp(tmp->content, "unset") == 0
			|| ft_strcmp(tmp->content, "export") == 0
			|| ft_strcmp(tmp->content, "exit") == 0)
		&& *is_cmd == 0)
		tmp->type = 13;
	else if (*is_cmd == 0)
		tmp->type = 11;
	else
		tmp->type = 2;
	*is_cmd = 1;
}

void	is_file_norm_2(t_list *tmp, int *is_cmd)
{
	tmp->type = 9;
	*is_cmd = 1;
	if (tmp->prev && (tmp->prev->type == 9
			|| tmp->prev->type == 6))
		tmp->type = 0;
}

void	is_file_norm_3(t_list *tmp, t_struct *cfg)
{
	free(tmp->content);
	tmp->content = ft_strdup_free(ft_itoa(cfg->exit_code));
	tmp->type = 2;
}

void	ft_is_file(t_struct *cfg)
{
	t_list	*tmp;
	int		is_cmd;

	tmp = cfg->arg;
	is_cmd = 0;
	split_path(cfg);
	while (tmp)
	{
		if (tmp->type == 0)
		{
			if (is_built_in(tmp->content) == 1)
				is_file_norm(tmp, &is_cmd);
			else if (is_cmd == 0 && is_file(cfg, tmp->content) == 0)
				is_file_norm_2(tmp, &is_cmd);
			else if (is_cmd == 1)
				tmp->type = 2;
		}
		else if (tmp->type == 1 || tmp->type == 8)
			is_cmd = 0;
		else if (tmp->type == 12)
			is_file_norm_3(tmp, cfg);
		tmp = tmp->next;
	}
}
