#include "minishell.h"

int	run_cd(char **params, t_list *envp)
{
	char	*new_path;
	char	*home;

	home = ft_getenv("HOME", envp);
	if (!params[1] || !ft_strncmp(params[1], home, ft_strlen(params[1])))
		new_path = home;
	else if (params[1] && (params[1][0] == '-'))
		new_path = ft_strdup(ft_getenv("OLDPWD", envp));
	else
		new_path = params[1];
	ft_setenv(envp, "OLDPWD", getcwd(NULL, 0), 1);
	if (chdir(new_path) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", new_path);
		error_exit(NULL);
	}
	ft_setenv(node, "PWD", getcwd(NULL, 0), 1);
	if (params[1] && (params[1][0] == '-'))
		free(new_path);
	return (free2d(params), 0);
}

int	run_echo(char **params, t_list *envp)
{
	int	i;

	i = 1;
	while (argv[i] && (ft_strncmp(argv[i], "-n", 2) == 0))
		i++;
	while (argv[i + 1])
	{
		printf("%s ", argv[i]);
		i++;
	}
	printf("%s", argv[i]);
	if (ft_strncmp(argv[1], "-n", 2) != 0)
		printf("\n");
	return (0);
}

int	run_pwd(char **params, t_list *envp)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		error_exit(errno);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	run_export(char **params, t_list *envp)
{
	char	*key;
	char	*val;
	int		q;
	int		i;

	i = 0;
	while (params[++i])
	{
		if (!ft_strchr(params[i], '='))
			continue ;
		q = ft_strchr(params[i], '=') - params[i];
		if (q == 0)
			error_exit(NULL);
		key = ft_substr(params[i], 0, q);
		val = ft_substr(params[i], q + 1, ft_strlen(params[i]) - q - 1);
		ft_setenv(node, key, val, 1);
	}
	free2d(params);
	return (0);
}

int	run_unset(char **params, t_list *envp)
{
	t_list	*list[2];
	char	*str[2];
	int		q;
	int		i;

	i = 0;
	list[0] = envp;
	while (params[++i] != "\0")
	{
		while (list[0] != NULL)
		{
			q = ft_strchr(params[i], '=') - params[i];
			if (q < 0)
				q = ft_strlen(params[i]);
			str[0] = ft_substr(params[i], 0, q);
			str[1] = ft_substr(params[i], q + 1, ft_strlen(params[i]) - q - 1);
			if (ft_strncmp(temp->key, str[0], ft_strlen(str[0])))
				continue ;
			if ((str[1]) && (ft_strncmp(temp->val, str[1], ft_strlen(str[1]))))
				continue ;
			remove_link(envp, list[0], list[1]);
			break ;
		}
	}
	return (free2d(params), 0);
}
