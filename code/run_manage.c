#include "minishell.h"

int	run_redir(char **params, t_list *envp)
{
	int	fd;
	(void) envp;

	if (params[0][0] == '<')
		fd = open(params[1], O_CREAT, O_RDONLY);
	else if (params[0][0] == '=')
		heredoc(params[1]);
	else if (params[0][0] == '>')
		fd = open(params[1], O_CREAT, O_WRONLY);
	else if (params[0][0] == '?')
		fd = open(params[1], O_APPEND, O_WRONLY);
	if (fd == -1)
		error_exit(strerror(errno));
	if (params[0][0] == '<')
		dup2(fd, STDIN_FILENO);
	else if ((params[0][0] == '>') || (params[0][0] == '?'))
		dup2(fd, STDOUT_FILENO);
	else
		dup2(STDIN_FILENO, STDIN_FILENO);
	if (params[0][0] != '=')
		return (free2d(params), close(fd), 0);
	return (free2d(params), 1);
}

int	run_env(char **params, t_list *envp)
{
	t_list	*temp;

	temp = envp;
	while (temp != NULL)
	{
		printf("%s=%s\n", temp->key, temp->val);
		temp = temp->next;
	}
	free2d(params);
	return (0);
}

int	run_exec(char **params, t_list *envp)
{
	t_list	*temp;
	char	**arr_envp;
	char	*line;
	int		len;

	len = 0;
	temp = envp;
	while (temp != NULL)
		len++;
	printf("Hi\n");
	arr_envp = ft_calloc(len + 1, sizeof(char *));
	arr_envp[len] = NULL;
	temp = envp;
	printf("Hi\n");
	while (strlist_len(arr_envp) < len)
	{
		line = ft_strjoin(temp->key, "=");
		arr_envp[strlist_len(arr_envp)] = ft_strjoin(line, temp->val);
		temp = temp->next;
	}
	printf("Hi\n");
	if (execve(params[0], params, arr_envp) < 0)
		error_exit(strerror(errno));
	return (0);
}

int	legitnum(char *argv)
{
	if (!argv || !*argv)
		return (0);
	if (argv[0] == '-' || argv[0] == '+')
		argv++;
	if (!*argv)
		return (0);
	while (*argv)
	{
		if (!ft_isdigit(*argv))
			return (0);
		argv++;
	}
	return (1);
}

int	run_exit(char **params, t_list *envp)
{
	long long	exit_status;
	(void)		envp;

	if (strlist_len(params) == 1)
		exit(0);
	if (strlist_len(params) >= 2 && legitnum(params[1]))
	{
		exit_status = ft_atoll(params[1]);
		if (strlist_len(params) > 2)
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (0);
		}
		exit((unsigned char)exit_status);
	}
	else
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(params[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	return (0);
}
