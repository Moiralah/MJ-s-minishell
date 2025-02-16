#include "minishell.h"

void	run_redir(char **params)
{
	int	fd;

	if (params[0][0] == '<')
		fd = open(params[1], O_CREAT, O_RDONLY);
	else if (params[0][0] == '=')
		fd = 1;
	else if (params[0][0] == '>')
		fd = open(params[1], O_CREAT, O_WRONLY);
	else if (params[0][0] == '?')
		fd = open(params[1], O_APPEND, O_WRONLY);
	free (params[1]);
	if (fd == -1)
		error_exit(errno);
	if (params[0][0] == '<')
		dup2(((int *)params[2])[0], fd);
	else if ((params[0][0] == '>') && (params[0][0] == '?'))
		dup2(((int *)params[2])[1], fd);
	free(params[1]);
}

void	run_env(char **params)
{
	int	i;

	i = -1;
	while (params[++i] != "\0")
		printf("%s\n", params[i]);
}

void	run_exec(char **params)
{
	char	**com_flags;
	int		i;

	i = strlist_len(params);
	com_flags = malloc(sizeof(char *) * (i + 1));
	com_flags[i] = "\0";
	while (--i >= 0)
		com_flags[i] = params[i];
	i = execve(com_flags[0], com_flags, params + strlist_len(params) < 0);
	free (params);
	free (com_flags);
	if (i == -1)
		error_exit(errno);
}

void	run_exit(char **params)
{
	exit(1);
}
