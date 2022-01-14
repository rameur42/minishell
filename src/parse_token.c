/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:47:32 by tgresle           #+#    #+#             */
/*   Updated: 2022/01/14 13:13:11 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_is_quotes(t_struct *cfg, char *str, int i, t_tok **lst)
{
	if (str[i] == '\'')
	{
		if (cfg->dq == 1)
			ft_add_back(lst, ft_new(str[i], 0));
		else if (cfg->sq == 0)
			cfg->sq = 1;
		else if (cfg->sq == 1)
			cfg->sq = 0;
	}
	else if (str[i] == '\"')
	{
		if (cfg->sq == 1)
			ft_add_back(lst, ft_new(str[i], 0));
		else if (cfg->dq == 0)
			cfg->dq = 1;
		else if (cfg->dq == 1)
			cfg->dq = 0;
	}
}

int	ft_is_env(t_struct *cfg, char *str, int i, t_tok **lst)
{
	if (str[i] == '$')
	{
		if (str[i + 1] && str[i + 1] == '?')
			ft_add_back(lst, ft_new(str[i], 12));
		else if (cfg->sq == 0)
			ft_add_back(lst, ft_new(str[i], 7));
		else
			ft_add_back(lst, ft_new(str[i], 0));
		cfg->en = 1;
		return (1);
	}
	else if (str[i] == '?' && i != 0 && str[i - 1] && str[i - 1] == '$')
	{
		ft_add_back(lst, ft_new(str[i], 12));
		return (1);
	}
	return (0);
}

int	ft_is_in_quotes(t_struct *cfg, char c, int f, t_tok **lst)
{
	if (c != '\'' && c != '\"' && f == 0
		&& cfg->sq == 1 && cfg->dq == 0)
	{
		ft_add_back(lst, ft_new(c, 0));
		return (1);
	}
	else if (c != '\'' && c != '\"' && f == 0
		&& cfg->sq == 0 && cfg->dq == 1
		&& cfg->en == 0 && c != '$')
	{
		ft_add_back(lst, ft_new(c, 0));
		return (1);
	}
	return (0);
}

int	ft_is_pipe(t_struct *cfg, char *str, int i, t_tok **lst)
{
	if (str[i] == '|')
	{
		ft_add_back(lst, ft_new(str[i], 1));
		cfg->en = 0;
		return (1);
	}
	return (0);
}

int	ft_is_redir(t_struct *cfg, char *str, int i, t_tok **lst)
{
	if (str[i] == '>')
	{
		if (str[i + 1] && str[i + 1] == '>')
			ft_add_back(lst, ft_new(str[i], 4));
		else if (i != 0 && str[i - 1] && str[i - 1] == '>')
			ft_add_back(lst, ft_new(str[i], 4));
		else
			ft_add_back(lst, ft_new(str[i], 3));
		cfg->en = 0;
		return (1);
	}
	else if (str[i] == '<')
	{
		if (str[i + 1] && str[i + 1] == '<')
			ft_add_back(lst, ft_new(str[i], 6));
		else if (str[i - 1] && str[i - 1] == '<')
			ft_add_back(lst, ft_new(str[i], 6));
		else
			ft_add_back(lst, ft_new(str[i], 5));
		cfg->en = 0;
		return (1);
	}
	return (0);
}
