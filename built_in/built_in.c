#include "main.h"

void    exec_exit(t_struct *cfg)
{
	ft_lstclear(&cfg->env);
	ft_lstclear(&cfg->exp);
	printf("exit\n");
	exit (0);
}

void    exec_echo(char **cmd)
{
	int i;
	int	f;

	i = 1;
	if (cmd[1] && ft_strcmp(cmd[1], "-n") == 0)
	{
		f = 1;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (f != 1)
		printf("\n");
}

void    exec_pwd(void)
{
    char *loc;

    loc = NULL;
	loc = getcwd(loc, 1024);
	if (loc != NULL)
	    printf("%s\n", loc);
	else
	    printf("Error\n");
	free(loc);
}

void	exec_cd(t_struct *cfg, char **path)
{
    char	*buffer;
	char	*go_to;
	int		i;
	t_list *tmp;

	i = 0;
	tmp = cfg->env;
	go_to = NULL;
	buffer = NULL;
	while (path[i])
		i++;
	if (i > 2)
		return ;
	else if (i == 1)
	{
		while (tmp)
		{
			if (ft_strncmp("HOME", tmp->content, 4) == 0)
			{
				chdir(ft_substr(tmp->content, 5, ft_strlen(tmp->content)));
				return ;
			}
			tmp = tmp->next;
		}
		printf("minishell: cd: HOME not set\n");
		return ;
	}
	if (ft_strncmp("/mnt", path[1], 4) == 0)
	{
		chdir(path[1]);
		return ;
	}
	buffer = getcwd(buffer, 1024);
	buffer = ft_strjoin(buffer, "/", 1);
	go_to = ft_strjoin(buffer, path[1], 0);
	if (chdir(go_to) != 0)
		printf("minishell: cd: %s: No such file or directory\n", path[1]);
	free(buffer);
	free(go_to);
}
