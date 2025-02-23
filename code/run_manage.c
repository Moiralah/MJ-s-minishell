#include "minishell.h"

int	run_redir(char **params, t_list *envp)
{
	int	fd;

	if (params[0][0] == '<')
		fd = open(params[1], O_CREAT, O_RDONLY);
	else if (params[0][0] == '=')
		heredoc(params[1]);
	else if (params[0][0] == '>')
		fd = open(params[1], O_CREAT, O_WRONLY);
	else if (params[0][0] == '?')
		fd = open(params[1], O_APPEND, O_WRONLY);
	free (params[1]);
	if (fd == -1)
		error_exit(errno);
	if (params[0][0] == '<')
		dup2(fd, stdin);
	else if ((params[0][0] == '>') || (params[0][0] == '?'))
		dup2(fd, stdout);
	else
		dup2(stdin, stdin);
	if (params[0][0] != '=')
		return (close(fd), 0);
	return (1);
}

int	run_env(char **params, t_list *envp)
{
	t_list	*temp;

	run_export(params + 1, envp);
	temp = envp;
	while (temp != NULL)
	{
		printf("%s=%s\n", temp->key, temp->val);
		temp = temp->next;
	}
	run_unset(params + 1, envp);
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
	arr_envp = ft_calloc(len + 1, sizeof(char *));
	arr_envp[len] = NULL;
	temp = envp;
	while (strlist_len(arr_envp) < len)
	{
		line = ft_strjoin(temp->key, "=");
		arr_envp[strlist_len(arr_envp)] = ft_strjoin(line, temp->val);
		temp = temp->next;
	}
	if (execve(com_flags[0], params, arr_envp) < 0)
		error_exit(errno);
	return (0);
}

int	run_exit(char **params, t_list *envp)
{
	int	isnum;

	isnum = 0;
	if (strlist_len(params) == 1)
		exit(0);
	if ((params[1][0] == '-') || (params[1][0] == '+'))
		params[1]++;
	else if ((strlist_len(params) == 2) && ft_isdigit(params[1]))
		exit(ft_atoi(params[1]));
	else if ((strlist_len(params) >= 2) && ft_isdigit(params[1]))
		return (printf("bash: exit: too many arguments\n"), 0);
	else
	{
		printf("bash: exit: %s: numeric argument required", params[1]);
		exit(2);
	}
	return (0);
}
