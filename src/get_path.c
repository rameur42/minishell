/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 22:53:33 by rameur            #+#    #+#             */
/*   Updated: 2021/08/26 01:50:22 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*ft_rm_p(char *line)
{
	int i;
	int j;
	char *res;

	j = 0;
	i = ft_strlen(line);
	if (i < 5)
		return (NULL);
	i -= 4;
	res = malloc(i * sizeof(char));
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

char	**split_path(char **env)
{
	int		i;
	char	**path;

	i = 0;
	while (env[i] != NULL)
	{
		if (env[i][0] == 'P' && env[i][1] == 'A'
			&& env[i][2] == 'T')
			path = ft_split(env[i], ':');
		i++;
	}
	return (path);
}