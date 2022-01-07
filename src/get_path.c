/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 22:53:33 by rameur            #+#    #+#             */
/*   Updated: 2021/12/23 18:14:44 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*ft_rm_p(char *line)
{
	int		i;
	int		j;
	char	*res;

	j = 0;
	i = ft_strlen(line);
	if (i < 5)
		return (NULL);
	i -= 3;
	res = malloc(i + 1 * sizeof(char));
	if (res == NULL)
		return (NULL);
	res[i] = '\0';
	i = 5;
	while (line[i])
	{
		res[j] = line[i];
		i++;
		j++;
	}
	free(line);
	return (res);
}

/*char	**split_path(char **env)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	while (env[i] != NULL)
	{
		if (env[i] && env[i][0] == 'P' && env[i][1] == 'A'
			&& env[i][2] == 'T')
			path = ft_split(env[i], ':');
		i++;
	}
	return (path);
}*/

void	split_path(t_struct *cfg)
{
	t_list *tmp;

	tmp = cfg->env;
	if (cfg->path != NULL)
		ft_free_tab(cfg->path);
	cfg->path = NULL;
	while (tmp)
	{
		if (ft_strncmp("PATH", tmp->content, 4) == 0)
		{
			cfg->path = ft_split(tmp->content, ':');
			cfg->path[0] = ft_rm_p(cfg->path[0]);
			return ;
		}
		tmp = tmp->next;
	}
}
