#include "main.h"

void    exec_exit(t_struct *cfg)
{
	ft_lstclear(&cfg->env);
	if (cfg->exp != NULL)
		ft_lstclear(&cfg->exp);
	printf("exit\n");
	exit (0);
}

void    exec_echo(t_list *tmp)
{
	int i;
	int	f;
	int	first;

	i = 1;
	first = 0;
	tmp = tmp->next;
	if (tmp && ft_strcmp(tmp->content, "-n") == 0)
	{
		f = 1;
		tmp = tmp->next;
	}
	while (tmp && (tmp->type == 2 || tmp->type == 0))
	{
		if (tmp->ps == 1 && first == 1)
			printf(" ");
		first = 1;
		printf("%s", tmp->content);
		tmp = tmp->next;
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

void	ft_modif_pwd(t_list *lst, int mode)
{
	t_list *tmp;
	char *buff;

	tmp = lst;
	buff = NULL;
	while (tmp)
	{
		if (mode == 1)
		{
			if (ft_is_same(tmp->content, "OLDPWD") == 0)
			{
				free(tmp->content);
				tmp->content = ft_strjoin("OLDPWD=", getcwd(buff, 1024), 0);
				free(buff);
				return ;
			}
		}
		else if (mode == 2)
		{
			if (ft_is_same(tmp->content, "PWD") == 0)
			{
				free(tmp->content);
				tmp->content = ft_strjoin("PWD=", getcwd(buff,1024), 0);
				free(buff);
				return ;
			}
		}
		tmp = tmp->next;
	}
	if (mode == 1)
		ft_lstadd_back(&lst, ft_lstnew(ft_strjoin("OLDPWD=", getcwd(buff, 1024), 0), 0, 0));
}

void	ft_refresh_pwd(t_struct *cfg, int mode)
{
	ft_modif_pwd(cfg->env, mode);
	if (cfg->exp != NULL)
		ft_modif_pwd(cfg->exp, mode);
}

void	exec_cd(t_struct *cfg, char **path)
{
    char	*buffer;
	char	*go_to;
	int		i;
	t_list *tmp;
	struct stat buff;

	i = 0;
	tmp = cfg->env;
	go_to = NULL;
	buffer = NULL;
	while (path[i])
		i++;
	if (i > 2)
		return ;
	else if (i == 1 || (i == 2 && ft_strcmp(path[1], "~") == 0))
	{
		while (tmp)
		{
			if (ft_strncmp("HOME", tmp->content, 4) == 0)
			{
				ft_refresh_pwd(cfg, 1);
				chdir(ft_substr(tmp->content, 5, ft_strlen(tmp->content)));
				ft_refresh_pwd(cfg, 2);
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
	stat(go_to, &buff);
	if (buff.st_mode == 16877)
		ft_refresh_pwd(cfg, 1);
	//printf("stat->%d %u\n", stat(go_to, &buff), buff.st_mode);
	if (chdir(go_to) != 0)
		printf("minishell: cd: %s: No such file or directory\n", path[1]);
	else
		ft_refresh_pwd(cfg, 2);
	free(buffer);
	free(go_to);
}
