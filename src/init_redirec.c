/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:48:04 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/13 11:22:02 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_print_red_error(char *s, int exit)
{
	printf("syntax error near unexpected token `%s'\n", s);
	return (exit);
}

int	ft_init_3(t_list *tmp)
{
	if (tmp->prev && (tmp->prev->type != 0 && tmp->prev->type != 9
			&& tmp->prev->type != 11 && tmp->prev->type != 2))
		return (ft_print_red_error(tmp->prev->content, 1));
	if (tmp->next && (tmp->next->type == 0 || tmp->next->type == 9
			|| tmp->next->type == 11 || tmp->next->type == 2))
	{
		tmp->fd = open(tmp->next->content, O_TRUNC | O_WRONLY
				| O_CREAT, 0644);
		tmp->next->type = 2;
		return (0);
	}
	else if (tmp->next)
		return (ft_print_red_error(tmp->next->content, 1));
	else
		return (ft_print_red_error("newline", 1));
	return (0);
}

int	ft_init_4(t_list *tmp)
{
	if (tmp->prev && (tmp->prev->type != 0 && tmp->prev->type != 9
			&& tmp->prev->type != 11 && tmp->prev->type != 2))
		return (ft_print_red_error(tmp->prev->content, 1));
	if (tmp->next && (tmp->next->type == 0 || tmp->next->type == 9
			|| tmp->next->type == 11 || tmp->next->type == 2))
	{
		tmp->fd = open(tmp->next->content, O_RDWR | O_CREAT | O_APPEND, 0644);
		tmp->next->type = 2;
		return (0);
	}
	else if (tmp->next)
		return (ft_print_red_error(tmp->next->content, 1));
	else
		return (ft_print_red_error("newline", 1));
}

int	ft_init_5(t_list *tmp)
{
	if (tmp->prev && (tmp->prev->type != 0 && tmp->prev->type != 9
			&& tmp->prev->type != 11 && tmp->prev->type != 2))
		return (ft_print_red_error(tmp->prev->content, 1));
	if (tmp->next)
	{
		tmp->fd = open(tmp->next->content, O_RDONLY);
		tmp->next->type = 2;
	}
	else if (tmp->next)
		return (ft_print_red_error(tmp->next->content, 1));
	else
		return (ft_print_red_error("newline", 1));
	return (0);
}

int	ft_init_6(t_list *tmp)
{
	if (tmp->prev && (tmp->prev->type != 0 && tmp->prev->type != 9
			&& tmp->prev->type != 11 && tmp->prev->type != 2))
		return (ft_print_red_error(tmp->prev->content, 1));
	if (!tmp->prev && tmp->next && (tmp->next->type == 0
			|| tmp->next->type == 9 || tmp->next->type == 11
			|| tmp->next->type == 2))
	{
		f_d_in(tmp->next->content);
		tmp->next->type = 2;
	}
	if (tmp->next && (tmp->next->type != 0 && tmp->next->type != 9
			&& tmp->next->type != 11 && tmp->next->type != 2))
		return (ft_print_red_error(tmp->next->content, 1));
	else if (tmp->next)
		tmp->next->type = 2;
	return (0);
}
